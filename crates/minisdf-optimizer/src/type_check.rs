use minisdf_ast::{BinOpTy, PrimTy, UnOpTy};
use rvsdg::{
    nodes::{Node, NodeType},
    Rvsdg,
};

use crate::{
    edge::OptEdge,
    highlevel::{report_error, HLError, HLOp, HLOpTy},
    HLGraph,
};

impl HLOp {
    fn check_is_subtree(
        &self,
        graph: &Rvsdg<HLOp, OptEdge>,
        input_index: usize,
    ) -> Result<(), HLError> {
        //we expect both arguments to be sub trees
        if let Some(left) = self.inputs.get(input_index) {
            //assert that "left" is connected.
            if let Some(connection) = left.edge {
                //check that the connected node is a simple node as well
                let src = graph.edge(connection).src.node;
                if let NodeType::Simple(_) = graph.node(src).node_type {
                    Ok(())
                } else {
                    Err(HLError::SubtreeExpected(input_index))
                }
            } else {
                Err(HLError::InputConnectionExpected(input_index))
            }
        } else {
            Err(HLError::InputExpected(0))
        }
    }

    fn type_check(&self, graph: &Rvsdg<HLOp, OptEdge>) -> Result<(), HLError> {
        match &self.ty {
            HLOpTy::BinaryOp(bop) => match bop {
                BinOpTy::Error => Err(HLError::HLError),
                //Signature is the same for all BinOps
                BinOpTy::Intersection | BinOpTy::Subtraction | BinOpTy::Union => {
                    self.check_is_subtree(graph, 0)?;
                    self.check_is_subtree(graph, 1)?;
                    if self.inputs.len() > 2 {
                        Err(HLError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
            },
            HLOpTy::TyConst(ty) => {
                todo!("check that the constructor has the right amount of inputs, and that the inputs have the correct type");
            }
            HLOpTy::UnaryOp(uop) => match uop {
                UnOpTy::Error => Err(HLError::HLError),
                UnOpTy::Repeat => {
                    todo!("Check that we have 3 floats, or a single vec3");
                }
                UnOpTy::Smooth => {
                    todo!("one float and subtree")
                }
                UnOpTy::Translate => {
                    todo!("one vec3 or 3 floats + subtree")
                }
            },
            HLOpTy::Prim(t) => match t {
                PrimTy::Error => Err(HLError::HLError),
                PrimTy::Box => {
                    todo!("single vec3 or 3 floats")
                }
                PrimTy::Plane => {
                    todo!("vec3 + float")
                }
                PrimTy::Sphere => {
                    todo!("single float")
                }
                PrimTy::Torus => {
                    todo!("two floats")
                }
            },
            HLOpTy::ConstFloat(_) | HLOpTy::ConstInt(_) => {
                todo!("no inputs!")
            }
            HLOpTy::Error => Err(HLError::HLError),
        }
    }
}

impl HLGraph {
    ///Type checks the graph against the node specifications.
    ///
    /// Returns true if the whole graph passed type checks.
    pub fn type_check(&self) -> bool {
        let mut passed = true;
        for node in self.graph.walk_reachable() {
            if let NodeType::Simple(n) = &self.graph.node(node).node_type {
                if let Err(e) = n.type_check(&self.graph) {
                    passed = false;
                    report_error(e, n.span.clone())
                }
            }
        }

        passed
    }
}
