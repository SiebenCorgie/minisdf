use ahash::AHashMap;
use minisdf_ast::{BinOpTy, PrimTy, UnOpTy};
use minisdf_common::Span;
use rvsdg::{
    builder::RegionBuilder,
    edge::{InputType, OutportLocation, OutputType},
    nodes::StructuralNode,
};

use crate::edge::OptEdge;

use super::{emit_walker::LambdaLookupKey, LLOp, LLOpTy};

pub fn build_lambda_prims<R: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, R>,
    lambda_lt: &mut AHashMap<LambdaLookupKey, OutportLocation>,
) {
    build_lambda_sphere(region, lambda_lt);
}

pub fn build_lambda_sphere<R: StructuralNode>(
    region: &mut RegionBuilder<LLOp, OptEdge, R>,
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
