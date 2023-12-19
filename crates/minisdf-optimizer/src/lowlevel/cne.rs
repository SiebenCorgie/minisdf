use ahash::AHashMap;
use rvsdg::{
    edge::{OutportLocation, OutputType},
    nodes::NodeType,
    smallvec::smallvec,
    NodeRef, SmallColl,
};

use super::{LLGraph, LLOpTy};

///Identifies a certain type of node.
#[derive(Debug, PartialEq, Eq, Hash)]
pub struct HashFields {
    input_src: SmallColl<OutportLocation>,
    ty: LLOpTy,
}

impl HashFields {
    fn for_node(node: NodeRef, graph: &LLGraph) -> Option<Self> {
        let mut input_src = SmallColl::new();

        for pred in graph.graph.walk_predecessors(node) {
            input_src.push(pred);
        }

        let ty = if let NodeType::Simple(n) = &graph.graph.node(node).node_type {
            n.ty.clone()
        } else {
            return None;
        };

        Some(HashFields { input_src, ty })
    }
}

impl LLGraph {
    /// Performs common-node-elimination on the graph. Note that this is only implemented on the
    /// LLOps atm.
    pub fn cne(&mut self) {
        //Explore all nodes in our toplevel region and build a map of the HashFields
        // Meaning iff hash(a) == hash(b) then a congruent b

        //Marking phase. Collects all concurrent nodes
        let mut unify_map: AHashMap<HashFields, SmallColl<NodeRef>> = AHashMap::default();
        for node in self
            .graph
            .region(&self.graph.toplevel_region())
            .unwrap()
            .nodes
            .iter()
        {
            if let Some(hf) = HashFields::for_node(*node, self) {
                if let Some(collection) = unify_map.get_mut(&hf) {
                    collection.push(*node);
                } else {
                    unify_map.insert(hf, smallvec![*node]);
                }
            }
        }

        //iterates all concurrent nodes and diverts the node's outputs from the _old_ node to the unified node.
        for (_config, mut nodes) in unify_map.into_iter() {
            //Nothing to unify
            if nodes.len() <= 1 {
                continue;
            }

            let hero_node = nodes.remove(0);
            let hero_outputs: SmallColl<_> = self
                .graph
                .node(hero_node)
                .outputs()
                .iter()
                .enumerate()
                .map(|(oidx, _)| OutportLocation {
                    node: hero_node,
                    output: OutputType::Output(oidx),
                })
                .collect();
            //Iterate the remaining nodes, for each output-edge `o`, change `src` from the node to `hero_node`
            for node in nodes {
                let outputs: SmallColl<_> = self
                    .graph
                    .node(node)
                    .outputs()
                    .iter()
                    .map(|out| out.clone())
                    .collect();
                for (oidx, o) in outputs.iter().enumerate() {
                    for edge in o.edges.iter() {
                        let (dst, ty) = {
                            let edg = self.graph.edge(*edge);
                            (edg.dst, edg.ty.clone())
                        };
                        //Disconnect old edge
                        self.graph.disconnect(*edge).unwrap();
                        //and rewire dst to the hero node
                        self.graph.connect(hero_outputs[oidx], dst, ty).unwrap();
                    }
                }
            }
        }
    }
}
