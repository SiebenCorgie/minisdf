use minisdf_ast::{BinOpTy, PrimTy, Ty, UnOpTy};
use rvsdg::{
    attrib::AttribStore,
    nodes::{Node, NodeType},
    Rvsdg,
};

use crate::{
    edge::OptEdge,
    err::{report_error, OptError},
    highlevel::{HLOp, HLOpTy},
    HLGraph,
};

impl HLOp {
    fn is_subtree(&self) -> bool {
        match self.ty {
            HLOpTy::BinaryOp(_) | HLOpTy::Prim(_) | HLOpTy::UnaryOp(_) => true,
            _ => false,
        }
    }

    fn check_is_subtree(&self, hlg: &HLGraph, input_index: usize) -> Result<(), OptError> {
        //we expect both arguments to be sub trees
        if let Some(left) = self.inputs.get(input_index) {
            //assert that "left" is connected.
            if let Some(connection) = left.edge {
                //check that the connected node is a simple node as well
                let src = hlg.graph.edge(connection).src.node;
                if let NodeType::Simple(n) = &hlg.graph.node(src).node_type {
                    if n.is_subtree() {
                        Ok(())
                    } else {
                        Err(OptError::SubtreeExpected(input_index))
                    }
                } else {
                    Err(OptError::SubtreeExpected(input_index))
                }
            } else {
                Err(OptError::InputConnectionExpected(input_index))
            }
        } else {
            Err(OptError::InputExpected(0))
        }
    }

    fn check_is_node_type(
        &self,
        hlg: &HLGraph,
        input_index: usize,
        ty: Ty,
    ) -> Result<(), OptError> {
        //we expect both arguments to be sub trees
        if let Some(left) = self.inputs.get(input_index) {
            //assert that "left" is connected.
            if let Some(connection) = left.edge {
                //check that the connected node is a simple node as well
                let src = hlg.graph.edge(connection).src.clone();
                if let Some(srcty) = hlg.get_type(src.clone()) {
                    if srcty == ty {
                        Ok(())
                    } else {
                        Err(OptError::TypeExpected {
                            expect: ty,
                            was: Some(srcty),
                        })
                    }
                } else {
                    Err(OptError::NoTypeInfo(src.into()))
                }
            } else {
                Err(OptError::InputConnectionExpected(input_index))
            }
        } else {
            Err(OptError::InputExpected(0))
        }
    }

    fn type_check(&self, hlg: &HLGraph) -> Result<(), OptError> {
        match &self.ty {
            HLOpTy::BinaryOp(bop) => match bop {
                BinOpTy::Error => Err(OptError::HLError),
                //Signature is the same for all BinOps
                BinOpTy::Intersection | BinOpTy::Subtraction | BinOpTy::Union => {
                    self.check_is_subtree(hlg, 0)?;
                    self.check_is_subtree(hlg, 1)?;
                    if self.inputs.len() > 2 {
                        Err(OptError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                BinOpTy::SmoothIntersection | BinOpTy::SmoothSubtraction | BinOpTy::SmoothUnion => {
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_subtree(hlg, 1)?;
                    self.check_is_subtree(hlg, 2)?;
                    if self.inputs.len() > 3 {
                        Err(OptError::TooManyInputs(3, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
            },
            HLOpTy::TyConst(ty) => match ty {
                Ty::Error => Err(OptError::HLError),
                Ty::Float => {
                    //check that its a single argument, which is a float immediate
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    if self.inputs.len() > 1 {
                        Err(OptError::TooManyInputs(1, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                Ty::Vec2 => {
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    if self.inputs.len() > 2 {
                        Err(OptError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                Ty::Vec3 => {
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    self.check_is_node_type(hlg, 2, Ty::Float)?;
                    if self.inputs.len() > 3 {
                        Err(OptError::TooManyInputs(3, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                Ty::Vec4 => {
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    self.check_is_node_type(hlg, 2, Ty::Float)?;
                    self.check_is_node_type(hlg, 3, Ty::Float)?;
                    if self.inputs.len() > 4 {
                        Err(OptError::TooManyInputs(4, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                Ty::Int => {
                    self.check_is_node_type(hlg, 0, Ty::Int)?;
                    if self.inputs.len() > 1 {
                        Err(OptError::TooManyInputs(1, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                Ty::Sdf => {
                    //the SDF type has no arguments (atm)
                    if self.inputs.len() > 0 {
                        Err(OptError::TooManyInputs(0, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
            },
            HLOpTy::UnaryOp(uop) => match uop {
                UnOpTy::Error => Err(OptError::HLError),
                UnOpTy::Repeat => {
                    //3 floats as arguments, then a subtree
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    self.check_is_node_type(hlg, 2, Ty::Float)?;
                    self.check_is_subtree(hlg, 3)?;
                    if self.inputs.len() > 4 {
                        Err(OptError::TooManyInputs(4, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                UnOpTy::RepeatIn => {
                    //3 floats as arguments, then a subtree
                    self.check_is_node_type(hlg, 0, Ty::Vec3)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    self.check_is_subtree(hlg, 2)?;
                    if self.inputs.len() > 3 {
                        Err(OptError::TooManyInputs(3, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                UnOpTy::Smooth => {
                    //one float and subtree
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_subtree(hlg, 1)?;
                    if self.inputs.len() > 2 {
                        Err(OptError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                UnOpTy::Translate => {
                    //one vec3 or 3 floats + subtree
                    self.check_is_node_type(hlg, 0, Ty::Vec3)?;
                    self.check_is_subtree(hlg, 1)?;
                    if self.inputs.len() > 2 {
                        Err(OptError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
            },
            HLOpTy::Prim(t) => match t {
                PrimTy::Error => Err(OptError::HLError),
                PrimTy::Box => {
                    //single vec3
                    self.check_is_node_type(hlg, 0, Ty::Vec3)?;
                    if self.inputs.len() > 1 {
                        Err(OptError::TooManyInputs(1, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                PrimTy::Plane => {
                    //vec3 + float
                    self.check_is_node_type(hlg, 0, Ty::Vec3)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    if self.inputs.len() > 2 {
                        Err(OptError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                PrimTy::Sphere => {
                    //single float
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    if self.inputs.len() > 1 {
                        Err(OptError::TooManyInputs(1, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
                PrimTy::Torus => {
                    //two vec3
                    self.check_is_node_type(hlg, 0, Ty::Float)?;
                    self.check_is_node_type(hlg, 1, Ty::Float)?;
                    if self.inputs.len() > 2 {
                        Err(OptError::TooManyInputs(2, self.inputs.len()))
                    } else {
                        Ok(())
                    }
                }
            },
            HLOpTy::ConstFloat(_) | HLOpTy::ConstInt(_) => {
                if self.inputs.len() > 0 {
                    Err(OptError::TooManyInputs(0, self.inputs.len()))
                } else {
                    Ok(())
                }
            }
            HLOpTy::Error => Err(OptError::HLError),
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
                if let Err(e) = n.type_check(self) {
                    passed = false;
                    report_error(e, n.span.clone())
                }
            }
        }

        passed
    }
}
