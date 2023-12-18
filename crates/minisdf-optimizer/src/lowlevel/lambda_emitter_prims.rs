use ahash::AHashMap;
use minisdf_ast::{BinOpTy, PrimTy, Ty, UnOpTy};
use minisdf_common::Span;
use rvsdg::{
    builder::RegionBuilder,
    edge::{InputType, OutportLocation, OutputType},
    nodes::StructuralNode,
};

use crate::edge::OptEdge;

use super::{emit_walker::LambdaLookupKey, LLOp, LLOpTy};

pub fn build_lambda_prims(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    build_lambda_sphere(region, lambda_lt);
    build_lambda_box(region, lambda_lt);
    build_lambda_torus(region, lambda_lt);
    build_lambda_plane(region, lambda_lt);
}

pub fn build_lambda_sphere(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    let (lambda_sphere, _) = region.new_function(|lmd| {
        //as defined by the sphere type check, the first argument is the sphere's
        // radius, the last (in this case second) arg is the @ value we evaluate at.
        //
        // In case of a sphere the SDF is pretty easy,  just the lenght(@) - radius
        let radius = lmd.add_argument();
        let at_val = lmd.add_argument();
        let _return_sdf = lmd.add_result();

        lmd.on_region(|reg| {
            let (at_length, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Length, Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[at_val],
                )
                .expect("Could not add length call for at in sphere");
            //now sub the radius
            let (subbed, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[at_length.as_outport_location(OutputType::Output(0)), radius],
                )
                .expect("Could not sub the radius in sphere");

            let _ = reg
                .connect_to_result(
                    subbed.as_outport_location(OutputType::Output(0)),
                    InputType::Result(0),
                )
                .expect("Could not route sphere SDF to output");
        })
    });

    lambda_lt.insert(
        LambdaLookupKey::Prim {
            prim: PrimTy::Sphere,
        },
        lambda_sphere.as_outport_location(OutputType::LambdaDeclaration),
    );
}

pub fn build_lambda_box(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    //Represents this code:
    // vec3 q = abs(@) - b;
    // return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
    let (lambda_box, _) = region.new_function(|lmd| {
        let extent = lmd.add_argument();
        let at_val = lmd.add_argument();
        let return_sdf = lmd.add_result();

        lmd.on_region(|reg| {
            let (at_abs, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Abs, Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[at_val],
                )
                .unwrap();
            let (def_q, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        at_abs.as_outport_location(OutputType::Output(0)),
                        extent.clone(),
                    ],
                )
                .unwrap();
            let def_q = def_q.as_outport_location(OutputType::Output(0));

            //now build the long string on line two
            // we first extract x,y,z from the extent, then
            // we create the maximum of all of those, and min this against 0.
            //
            // We then do the max(q, 0.0) call. However, we need to build transform
            // the 0.0. to vec3(0.0) by hand here.
            //
            // finally we build the length(_) + min_max_q call and connect that to
            // the result.
            //

            let (def_x, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::CoordSelect(0), Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[def_q.clone()],
                )
                .unwrap();

            let (def_y, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::CoordSelect(1), Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[def_q.clone()],
                )
                .unwrap();
            let (def_z, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::CoordSelect(2), Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[def_q.clone()],
                )
                .unwrap();

            let (def_zero, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::ImmF32(0.0), Span::empty())
                        .with_inputs(0)
                        .with_outputs(1),
                    &[],
                )
                .unwrap();

            let (max_yz, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Max, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_y.as_outport_location(OutputType::Output(0)),
                        def_z.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();
            let (max_xyz, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Max, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_x.as_outport_location(OutputType::Output(0)),
                        max_yz.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();

            let (min_xyz_zero, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Min, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        max_xyz.as_outport_location(OutputType::Output(0)),
                        def_zero.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();

            let (def_vec3_zero, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::TypeConstruct(Ty::Vec3), Span::empty())
                        .with_inputs(3)
                        .with_outputs(1),
                    &[
                        def_zero.as_outport_location(OutputType::Output(0)),
                        def_zero.as_outport_location(OutputType::Output(0)),
                        def_zero.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();

            let (max_q_zero, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Max, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_q.clone(),
                        def_vec3_zero.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();

            let (length, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Length, Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[max_q_zero.as_outport_location(OutputType::Output(0))],
                )
                .unwrap();
            let (added, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Add, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        length.as_outport_location(OutputType::Output(0)),
                        min_xyz_zero.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();

            //finaly connect to output
            reg.ctx_mut()
                .connect(
                    added.as_outport_location(OutputType::Output(0)),
                    return_sdf,
                    OptEdge::Value,
                )
                .unwrap();
        })
    });

    lambda_lt.insert(
        LambdaLookupKey::Prim { prim: PrimTy::Box },
        lambda_box.as_outport_location(OutputType::LambdaDeclaration),
    );
}

pub fn build_lambda_torus(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    let (lambda_torus, _) = region.new_function(|lmd| {
        let radius0 = lmd.add_argument();
        let radius1 = lmd.add_argument();
        let at_val = lmd.add_argument();
        let return_sdf = lmd.add_result();

        lmd.on_region(|reg| {
            //represents this code:
            // vec2 q = vec2(length(p.xz)-t.x,p.y);
            // return length(q)-t.y;

            let (def_x, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::CoordSelect(0), Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[at_val.clone()],
                )
                .unwrap();

            let (def_y, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::CoordSelect(1), Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[at_val.clone()],
                )
                .unwrap();
            let (def_at_xy, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::TypeConstruct(Ty::Vec2), Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_x.as_outport_location(OutputType::Output(0)),
                        def_y.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();
            let (def_at_xy_length, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Length, Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[def_at_xy.as_outport_location(OutputType::Output(0))],
                )
                .unwrap();
            let (def_subbed_radius0, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_at_xy_length.as_outport_location(OutputType::Output(0)),
                        radius0,
                    ],
                )
                .unwrap();

            let (def_q, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::TypeConstruct(Ty::Vec2), Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_subbed_radius0.as_outport_location(OutputType::Output(0)),
                        def_y.as_outport_location(OutputType::Output(0)),
                    ],
                )
                .unwrap();

            let (def_q_length, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Length, Span::empty())
                        .with_inputs(1)
                        .with_outputs(1),
                    &[def_q.as_outport_location(OutputType::Output(0))],
                )
                .unwrap();
            let (def_subbed_radius1, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Sub, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[
                        def_q_length.as_outport_location(OutputType::Output(0)),
                        radius1,
                    ],
                )
                .unwrap();

            reg.ctx_mut()
                .connect(
                    def_subbed_radius1.as_outport_location(OutputType::Output(0)),
                    return_sdf,
                    OptEdge::Value,
                )
                .unwrap();
        })
    });

    lambda_lt.insert(
        LambdaLookupKey::Prim {
            prim: PrimTy::Torus,
        },
        lambda_torus.as_outport_location(OutputType::LambdaDeclaration),
    );
}

pub fn build_lambda_plane(
    region: &mut RegionBuilder<LLOp, OptEdge>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    let (lambda_plane, _) = region.new_function(|lmd| {
        let normal = lmd.add_argument();
        let height = lmd.add_argument();
        let at_val = lmd.add_argument();
        let return_sdf = lmd.add_result();

        lmd.on_region(|reg| {
            let (dotted, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Dot, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[at_val, normal],
                )
                .unwrap();

            let (added, _) = reg
                .connect_node(
                    LLOp::new(LLOpTy::Add, Span::empty())
                        .with_inputs(2)
                        .with_outputs(1),
                    &[dotted.as_outport_location(OutputType::Output(0)), height],
                )
                .unwrap();

            reg.ctx_mut()
                .connect(
                    added.as_outport_location(OutputType::Output(0)),
                    return_sdf,
                    OptEdge::Value,
                )
                .unwrap();
        })
    });

    lambda_lt.insert(
        LambdaLookupKey::Prim {
            prim: PrimTy::Plane,
        },
        lambda_plane.as_outport_location(OutputType::LambdaDeclaration),
    );
}
