use ahash::AHashMap;
use rvsdg::{
    edge::{InportLocation, InputType, OutportLocation, OutputType},
    nodes::{NodeType, StructuralNode},
    region::RegionLocation,
    NodeRef, SmallColl,
};

use super::LLGraph;

impl LLGraph {
    ///Copies the whole `src_region` content into `dst_region`, maps argument `a` to `argument_mapping[a]` and result `r` to `result_mapping[r]`.
    fn copy_region_into_region(
        &mut self,
        src_region: RegionLocation,
        dst_region: RegionLocation,
        argument_mapping: &[OutportLocation],
        result_mapping: &[Vec<InportLocation>],
    ) {
        //explore the reachables of `src_region`. For any node, connect
        let mut rr_mapping: AHashMap<NodeRef, NodeRef> = AHashMap::default();

        //We copy by first collecting all nodes of the `src_region` and copying them into the `dst_region`.
        // We then iterate again, but this time we copy all edges in the `src_region` to the `dst_region` by using rr_mapping.
        // Whenever we find an edge that is connected to a result or argument, we use the argument_mapping/result_mapping instead.

        let all_src_nodes = self
            .graph
            .region(&src_region)
            .unwrap()
            .nodes
            .iter()
            .map(|node| node.clone())
            .collect::<Vec<_>>();
        for node in all_src_nodes {
            if let NodeType::Simple(s) = self.graph.node(node).node_type.clone() {
                //reset the nodes inputs and outputs
                let new_node = self
                    .graph
                    .on_region(&dst_region, |reg| reg.insert_node(s.shallow_copy()))
                    .unwrap();
                rr_mapping.insert(node, new_node);
            } else {
                println!("Warning, found non-simple node in λ-Node region");
            }
        }

        //Now iterate over all edges in the region, and either build the same connection in the dst graph, or rewire to the arg/result mappings if needed
        let all_src_edges = self
            .graph
            .region(&src_region)
            .unwrap()
            .edges
            .iter()
            .cloned()
            .collect::<Vec<_>>();
        for src_edge in all_src_edges {
            let (src_reg_src, src_reg_dst, edge_type) = {
                let edge = self.graph.edge(src_edge);
                (edge.src.clone(), edge.dst.clone(), edge.ty)
            };

            //map the src portion to the dst region
            let dst_reg_src = if src_reg_src.output.is_argument() {
                //is argument, therefore map into the argument_mapping
                match src_reg_src.output {
                    OutputType::Argument(i) => argument_mapping[i].clone(),
                    _ => panic!("Inliner: Unknown argument mapping type"),
                }
            } else {
                //can map directly
                let dst_reg_src_node = rr_mapping.get(&src_reg_src.node).unwrap();
                OutportLocation {
                    node: *dst_reg_src_node,
                    output: src_reg_src.output,
                }
            };

            //Map the dst_reg_dst similarly
            let dst_reg_dst: SmallColl<InportLocation> = if src_reg_dst.input.is_result() {
                match src_reg_dst.input {
                    InputType::Result(i) => {
                        //If we map to result, we might have to connect to several "outside-λ" nodes
                        // as part of the mapping.
                        result_mapping[i].iter().map(|loc| *loc).collect()
                    }
                    _ => panic!("Inliner: Unknown result mapping type"),
                }
            } else {
                let dst_reg_dst_node = rr_mapping.get(&src_reg_dst.node).unwrap();
                rvsdg::smallvec::smallvec![InportLocation {
                    node: *dst_reg_dst_node,
                    input: src_reg_dst.input
                }]
            };

            //Now issue connection for all (dst_reg_src, [dst_reg_dst]) pairs.
            for dst in dst_reg_dst {
                self.graph
                    .connect(dst_reg_src, dst, edge_type)
                    .expect("Could not connect ");
            }
        }
    }

    fn inline_apply_node(&mut self, apply_node: NodeRef) {
        //Per definition the first arg is the callable, which must be a lambda decleration, and all following inputs are the
        // call_args.
        //
        // Similar we have a set of results, depending on the apply node.
        let (callable, args, results, parent_region) =
            if let NodeType::Apply(an) = &self.graph.node(apply_node).node_type {
                let callable = self
                    .graph
                    .edge(an.get_callabel_decl().edge.unwrap())
                    .src
                    .clone();
                let mut argidx = 0;
                let mut args = Vec::new();
                while let Some(arg_port) = an.argument_input(argidx) {
                    argidx += 1;
                    args.push(self.graph.edge(arg_port.edge.unwrap()).src.clone());
                }

                let mut resultidx = 0;
                let mut results = Vec::new();
                while let Some(res_port) = an.return_value(resultidx) {
                    resultidx += 1;
                    let mut recv = Vec::new();
                    for receiver in res_port.edges.iter() {
                        recv.push(self.graph.edge(*receiver).dst.clone());
                    }
                    results.push(recv);
                }

                (
                    callable,
                    args,
                    results,
                    self.graph.node(apply_node).parent.clone().unwrap(),
                )
            } else {
                println!("Cannot inline non-apply nodes");
                return;
            };

        let lambda_region = if let NodeType::Lambda(l) = &self.graph.node(callable.node).node_type {
            assert!(l.regions().len() == 1);
            RegionLocation {
                node: callable.node,
                region_index: 0,
            }
        } else {
            println!("Callable was no LambdaNode");
            return;
        };

        //Before connecting to the new nodes, disconnect the applynode fully
        self.graph
            .remove_node(apply_node)
            .expect("Failed to disconnect the apply node!");

        //since we now know all participants in this apply node,
        //copy the content of the callable to this position, and
        self.copy_region_into_region(lambda_region, parent_region, &args, results.as_slice())
    }

    ///Searches for apply nodes and inlines them if possible.
    pub fn inline(&mut self) {
        let mut apply_nodes = Vec::new();
        for node in self.graph.walk_reachable() {
            if let NodeType::Apply(_) = self.graph.node(node).node_type {
                apply_nodes.push(node);
            }
        }

        for an in apply_nodes {
            self.inline_apply_node(an);
        }
    }
}
