use minisdf_ast::Ty;
use rvsdg::{
    attrib::AttribLocation,
    edge::{InportLocation, InputType, OutportLocation},
    NodeRef, SmallColl,
};

use crate::{
    err::{report_error, OptError},
    LLGraph, LLOp, LLOpTy,
};

impl LLGraph {
    fn resolve_node(&mut self, noderef: NodeRef) -> Result<Ty, OptError> {
        let mut arg_tys = SmallColl::new();
        let mut argidx = 0;
        while let Some(arg) = self.graph.node(noderef).input_src(&self.graph, argidx) {
            let aty = if let Some(ty) = self.type_table.attrib(&AttribLocation::from(arg)) {
                ty[0]
            } else {
                //not yet resolved, recurse!
                self.resolve_node(arg.node)?
            };

            arg_tys.push(aty);

            argidx += 1;
        }

        //Now match our node and do the actual resolving
        // TODO:
        // The type resolver does the bare minimum. It works in this context but should be rewritten, as it does not test
        // all edge cases. For instance, Length can only be called on a float and other small details.
        //
        // However, I did not bother to build an actual _good_ type system for now.
        let node = self.graph.node(noderef).node_type.unwrap_simple_ref();
        let ty: Ty = match node.ty {
            LLOpTy::Add | LLOpTy::Sub | LLOpTy::Mul | LLOpTy::Div => {
                assert!(arg_tys.len() == 2);
                if arg_tys[0] != arg_tys[1] {
                    report_error(
                        OptError::LLError(format!("{:?} error", node.ty)),
                        node.span.clone(),
                    );
                    let err = OptError::BinOpTypeMissmatch(
                        arg_tys[0], arg_tys[0], arg_tys[0], arg_tys[1],
                    );
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                //Use that type as result as well
                arg_tys[0]
            }
            LLOpTy::Abs => {
                if arg_tys.len() != 1 {
                    let err = OptError::TooManyInputs(1, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                arg_tys[0]
            }
            LLOpTy::CoordSelect(selection) => {
                //TODO: Check that we are within range. of the vec then extract float type
                if arg_tys.len() != 1 {
                    let err = OptError::TooManyInputs(1, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if !arg_tys[0].is_vec() {
                    let err = OptError::TypeExpected {
                        expect: Ty::Vec2,
                        was: Some(arg_tys[0]),
                    };
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if selection >= arg_tys[0].element_count() {
                    let err = OptError::VectorOOB(arg_tys[0].element_count(), selection);
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                //NOTE: we have no swizzl, we always select a float from a float vector.
                Ty::Float
            }
            LLOpTy::Dot => {
                if arg_tys.len() != 2 {
                    let err = OptError::TooManyInputs(2, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                //Check that both args are floats or vectors
                if !((arg_tys[0].is_vec() || arg_tys[0] == Ty::Float)
                    && (arg_tys[1].is_vec() || arg_tys[1] == Ty::Float))
                {
                    let err = OptError::LLError("Dot expects vectors or floats".to_string());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                //Check that both are the same
                if arg_tys[0] != arg_tys[1] {
                    let err = OptError::BinOpTypeMissmatch(
                        arg_tys[0], arg_tys[0], arg_tys[0], arg_tys[1],
                    );
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                //Dot product always produces a single float
                Ty::Float
            }
            LLOpTy::Error => {
                let err = OptError::LLError("Encountered LLOpTy::Error".to_string());
                report_error(err.clone(), node.span.clone());
                return Err(err);
            }
            LLOpTy::ImmF32(_) => Ty::Float,
            LLOpTy::ImmI32(_) => Ty::Int,
            LLOpTy::Length => {
                if arg_tys.len() != 1 {
                    let err = OptError::TooManyInputs(1, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                Ty::Float
            }
            LLOpTy::Round => {
                if arg_tys.len() != 1 {
                    let err = OptError::TooManyInputs(1, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                arg_tys[0]
            }
            LLOpTy::Max | LLOpTy::Min => {
                if arg_tys.len() != 2 {
                    let err = OptError::TooManyInputs(1, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if arg_tys[0] != arg_tys[1] {
                    let err = OptError::BinOpTypeMissmatch(
                        arg_tys[0], arg_tys[0], arg_tys[0], arg_tys[1],
                    );
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                arg_tys[0]
            }
            LLOpTy::Clamp => {
                if arg_tys.len() != 3 {
                    let err = OptError::TooManyInputs(3, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if arg_tys[0] != arg_tys[1] {
                    let err = OptError::BinOpTypeMissmatch(
                        arg_tys[0], arg_tys[0], arg_tys[0], arg_tys[1],
                    );
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if arg_tys[0] != arg_tys[2] {
                    let err = OptError::BinOpTypeMissmatch(
                        arg_tys[0], arg_tys[0], arg_tys[0], arg_tys[2],
                    );
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                arg_tys[0]
            }
            LLOpTy::Lerp => {
                if arg_tys.len() != 3 {
                    let err = OptError::TooManyInputs(3, arg_tys.len());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if arg_tys[0] != arg_tys[1] {
                    let err = OptError::BinOpTypeMissmatch(
                        arg_tys[0], arg_tys[0], arg_tys[0], arg_tys[1],
                    );
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                if arg_tys[2] != Ty::Float {
                    let err = OptError::TypeExpected {
                        expect: Ty::Float,
                        was: Some(arg_tys[2]),
                    };
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                arg_tys[0]
            }
            LLOpTy::TypeConstruct(ty) => match ty {
                Ty::Error => {
                    let err = OptError::LLError("Encountered Ty::Error".to_string());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                Ty::Float => {
                    if arg_tys.len() != 1 {
                        let err = OptError::TooManyInputs(1, arg_tys.len());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    if arg_tys[0] != Ty::Float {
                        let err =
                            OptError::LLError("float constructor needs float input".to_string());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    Ty::Float
                }
                Ty::Int => {
                    if arg_tys.len() != 1 {
                        let err = OptError::TooManyInputs(1, arg_tys.len());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    if arg_tys[0] != Ty::Int {
                        let err =
                            OptError::LLError("int constructor needs float input".to_string());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    Ty::Int
                }
                Ty::Sdf => {
                    let err = OptError::LLError("Encountered Ty::SDF".to_string());
                    report_error(err.clone(), node.span.clone());
                    return Err(err);
                }
                Ty::Vec2 => {
                    if arg_tys.len() != 2 {
                        let err = OptError::TooManyInputs(2, arg_tys.len());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    if arg_tys[0] != Ty::Float || arg_tys[1] != Ty::Float {
                        let err = OptError::LLError(
                            "Vec2 must be constructed from two floats!".to_string(),
                        );
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    ty
                }
                Ty::Vec3 => {
                    if arg_tys.len() != 3 {
                        let err = OptError::TooManyInputs(3, arg_tys.len());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    if arg_tys[0] != Ty::Float || arg_tys[1] != Ty::Float || arg_tys[2] != Ty::Float
                    {
                        let err = OptError::LLError(
                            "Vec3 must be constructed from two floats!".to_string(),
                        );
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    ty
                }
                Ty::Vec4 => {
                    if arg_tys.len() != 4 {
                        let err = OptError::TooManyInputs(4, arg_tys.len());
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    if arg_tys[0] != Ty::Float
                        || arg_tys[1] != Ty::Float
                        || arg_tys[2] != Ty::Float
                        || arg_tys[3] != Ty::Float
                    {
                        let err = OptError::LLError(
                            "Vec4 must be constructed from two floats!".to_string(),
                        );
                        report_error(err.clone(), node.span.clone());
                        return Err(err);
                    }
                    ty
                }
            },
        };

        //After being done, register this port under the type and return
        self.type_table.push_attrib(
            &AttribLocation::OutPort(OutportLocation {
                node: noderef,
                output: rvsdg::edge::OutputType::Output(0),
            }),
            ty,
        );

        Ok(ty)
    }

    ///Resolves the types of this tree recursively. Might fail if some type can't be resolved
    pub fn type_resolve(&mut self) -> Result<(), OptError> {
        //Before starting, annotate the export port as Float as well, since we always want to output a float.

        self.type_table.push_attrib(
            &AttribLocation::InPort(InportLocation {
                node: self.graph.entry_node(),
                input: InputType::Result(0),
            }),
            Ty::Float,
        );

        let start_node = self.graph.node(self.graph.entry_node()).regions()[0]
            .result_src(&self.graph, 0)
            .unwrap();

        self.resolve_node(start_node.node)?;

        Ok(())
    }
}
