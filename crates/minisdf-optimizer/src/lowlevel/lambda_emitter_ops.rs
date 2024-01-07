use ahash::AHashMap;
use minisdf_ast::{BinOpTy, Ty, UnOpTy};
use minisdf_common::Span;
use rvsdg::{
    builder::RegionBuilder,
    edge::{InputType, OutportLocation, OutputType},
};

use crate::edge::OptEdge;

use super::{emit_walker::LambdaLookupKey, LLOp, LLOpTy};

pub fn build_lambda_ops(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    //build all lookup definitions on this region
    build_binary_op_ty(region, lambda_lt, BinOpTy::Intersection);
    build_binary_op_ty(region, lambda_lt, BinOpTy::Subtraction);
    build_binary_op_ty(region, lambda_lt, BinOpTy::Union);
    build_binary_op_ty(region, lambda_lt, BinOpTy::SmoothUnion);
    build_smooth_lambda(region, lambda_lt);
    build_repeat_lambda(region, lambda_lt);
    build_translate_lambda(region, lambda_lt);
}

fn build_binary_op_ty(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
    op_ty: BinOpTy,
) {
    //for a binary op we have no "on at" operation, so we only emit a
    // on_sdf type operation

    let (on_sdf, _) = region.new_function(|lmd| {
        //a binary op is defined by operating on two sdf values, and no input in our case
        let left = lmd.add_argument();
        let right = lmd.add_argument();
        let output = lmd.add_result();

        let third_arg = match op_ty {
            BinOpTy::SmoothIntersection | BinOpTy::SmoothUnion | BinOpTy::SmoothSubtraction => {
                Some(lmd.add_argument())
            }
            _ => None,
        };

        lmd.on_region(|reg| {
            //use the inputs to do min/max and possibly negate "right", based on our op_ty
            let result = match op_ty {
                BinOpTy::Error => panic!("BinOpTy was error"),
                BinOpTy::Intersection => {
                    let (result, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Max, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[left, right],
                        )
                        .expect("Could not create intersection's max call");
                    result
                }
                BinOpTy::Union => {
                    let (result, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Min, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[left, right],
                        )
                        .expect("Could not create unions's min call");
                    result
                }
                BinOpTy::Subtraction => {
                    //need to negate "left"
                    let minus_one = reg.insert_node(
                        LLOp::new(LLOpTy::imm_f32(-1.0), Span::empty()).with_outputs(1),
                    );
                    let (negated, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Mul, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[minus_one.as_outport_location(OutputType::Output(0)), right],
                        )
                        .expect("Could not negate the \"right\" value in subtraction call");
                    let (result, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Max, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[negated.as_outport_location(OutputType::Output(0)), left],
                        )
                        .expect("Could not create unions's min call");
                    result
                }
                BinOpTy::SmoothUnion => {
                    //float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
                    //return mix( d2, d1, h ) - k*h*(1.0-h);
                    let radius = third_arg.unwrap();

                    let def_zero_five = reg.insert_node(
                        LLOp::new(LLOpTy::imm_f32(0.5), Span::empty()).with_outputs(1),
                    );
                    let def_zero = reg.insert_node(
                        LLOp::new(LLOpTy::imm_f32(0.0), Span::empty()).with_outputs(1),
                    );
                    let def_one = reg.insert_node(
                        LLOp::new(LLOpTy::imm_f32(1.0), Span::empty()).with_outputs(1),
                    );

                    let (def_d2_minus_d1, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Sub, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[right, left],
                        )
                        .unwrap();
                    let (def_mul_half_d, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Mul, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_d2_minus_d1.as_outport_location(OutputType::Output(0)),
                                def_zero_five.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();
                    let (def_div_k, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Div, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_mul_half_d.as_outport_location(OutputType::Output(0)),
                                radius,
                            ],
                        )
                        .unwrap();
                    let (def_add_zero_five, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Add, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_zero_five.as_outport_location(OutputType::Output(0)),
                                def_div_k.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();

                    let (def_h_clamped, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Clamp, Span::empty())
                                .with_inputs(3)
                                .with_outputs(1),
                            &[
                                def_add_zero_five.as_outport_location(OutputType::Output(0)),
                                def_zero.as_outport_location(OutputType::Output(0)),
                                def_one.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();

                    //build the subtraction part of the mix call
                    let (def_one_minus_h, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Sub, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_one.as_outport_location(OutputType::Output(0)),
                                def_h_clamped.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();

                    let (def_time_h, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Sub, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_one_minus_h.as_outport_location(OutputType::Output(0)),
                                def_h_clamped.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();
                    let (def_time_k, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Sub, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_time_h.as_outport_location(OutputType::Output(0)),
                                radius,
                            ],
                        )
                        .unwrap();

                    let (def_lerped, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Lerp, Span::empty())
                                .with_inputs(3)
                                .with_outputs(1),
                            &[
                                right,
                                left,
                                def_h_clamped.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();

                    let (def_result, _) = reg
                        .connect_node(
                            LLOp::new(LLOpTy::Sub, Span::empty())
                                .with_inputs(2)
                                .with_outputs(1),
                            &[
                                def_lerped.as_outport_location(OutputType::Output(0)),
                                def_time_k.as_outport_location(OutputType::Output(0)),
                            ],
                        )
                        .unwrap();
                    def_result
                }
                _ => todo!(),
            };

            reg.ctx_mut()
                .connect(
                    result.as_outport_location(OutputType::Output(0)),
                    output,
                    OptEdge::Value,
                )
                .unwrap()
        });
    });

    lambda_lt.insert(
        LambdaLookupKey::BinaryOp {
            op: op_ty,
            on_at: false,
        },
        on_sdf.as_outport_location(OutputType::LambdaDeclaration),
    );
}

fn build_translate_lambda(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    //Lambda has only the "on_at" step, by moving the @ paramter in the opposite direction
    let (translate_on_at_lmd, _) = region.new_function(|lmd| {
        let translation_offset = lmd.add_argument();
        let at_input = lmd.add_argument();
        let _at_output = lmd.add_result();

        lmd.on_region(|reg| {
            let (subtracted, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[at_input, translation_offset],
                )
                .expect("Could not subtract in translation");
            let _ = reg
                .connect_to_result(
                    subtracted.as_outport_location(OutputType::Output(0)),
                    InputType::Result(0),
                )
                .expect("Could not set subtraction to result routing");
        });
    });

    lambda_lt.insert(
        LambdaLookupKey::UnaryOp {
            op: UnOpTy::Translate,
            on_at: true,
        },
        translate_on_at_lmd.as_outport_location(OutputType::LambdaDeclaration),
    );
}

fn build_smooth_lambda(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    //The smooth op operates only on the sdf value returned by its child, by just subtracting the smoothness value
    let (smooth_on_sdf_lmd, _) = region.new_function(|lmd| {
        //Defined by the type_check, first roundness, then sdf value
        let roundness_input = lmd.add_argument();
        let sdf_input = lmd.add_argument();
        let sdf_output = lmd.add_result();

        lmd.on_region(|reg| {
            let (subtracted, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[sdf_input, roundness_input],
                )
                .expect("Could not subtract in smooth op");

            reg.ctx_mut()
                .connect(
                    subtracted.as_outport_location(OutputType::Output(0)),
                    sdf_output,
                    OptEdge::Value,
                )
                .unwrap()
        });
    });

    lambda_lt.insert(
        LambdaLookupKey::UnaryOp {
            op: UnOpTy::Smooth,
            on_at: false,
        },
        smooth_on_sdf_lmd.as_outport_location(OutputType::LambdaDeclaration),
    );
}

fn build_repeat_lambda(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    //repetition also "only" has the "on_at" part. It lets us round the @ to an "in interval" representation.
    // about this:
    //
    // vec3 q = @ - s*round(@/s);
    // return q;

    //Lambda has only the "on_at" step, by moving the @ paramter in the opposite direction
    let (repeat_on_at_lmd, _) = region.new_function(|lmd| {
        let _at_output = lmd.add_result();
        let repetition_domain_size_x = lmd.add_argument();
        let repetition_domain_size_y = lmd.add_argument();
        let repetition_domain_size_z = lmd.add_argument();
        let at_input = lmd.add_argument();

        lmd.on_region(|reg| {
            //create the vec3 for domain repetition
            let (domain_rep_vec3, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::TypeConstruct(Ty::Vec3), Span::empty())
                        .with_inputs(3)
                        .with_outputs(1),
                    &[
                        repetition_domain_size_x,
                        repetition_domain_size_y,
                        repetition_domain_size_z,
                    ],
                )
                .expect("Could not create vec3 for domain repetition!");

            let (at_div_s, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Div, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        at_input.clone(),
                        domain_rep_vec3.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .expect("Could not div repetition");

            let (rounded, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Round, Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[at_div_s.as_outport_location(OutputType::Output(0))],
                )
                .expect("Could not round repetition");

            let (times_s, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Mul, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        domain_rep_vec3.as_outport_location(OutputType::Output(0)),
                        rounded.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .expect("Could not multiply interval");

            let (subbed, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[at_input, times_s.as_outport_location(OutputType::Output(0))],
                )
                .expect("Could not sub @ from interval");

            let _ = reg
                .connect_to_result(
                    subbed.as_outport_location(OutputType::Output(0)),
                    InputType::Result(0),
                )
                .expect("Could not set subtraction to result routing");
        });
    });

    lambda_lt.insert(
        LambdaLookupKey::UnaryOp {
            op: UnOpTy::Repeat,
            on_at: true,
        },
        repeat_on_at_lmd.as_outport_location(OutputType::LambdaDeclaration),
    );
}
