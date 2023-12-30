use minisdf_ast::Ty;
use minisdf_optimizer::{
    rvsdg::{
        attrib::AttribLocation,
        edge::{OutportLocation, OutputType},
        NodeRef, SmallColl,
    },
    LLOpTy,
};
use rspirv::{dr::Operand, spirv::Word};

use crate::{err::LoweringError, LoweringCtx};

pub enum GlslExtInst {
    //FAbs
    Abs = 4,
    //Round
    Round = 1,
    //Length
    Length = 66,
    //FMax
    Max = 40,
    //FMin
    Min = 37,
}

impl<'a> LoweringCtx<'a> {
    ///gets, possibly builds the `llnode` and returns the result id.
    fn get_port_id(&mut self, llnode: OutportLocation) -> Result<Word, LoweringError> {
        if let Some(id) = self.port_mapping.get(&llnode) {
            return Ok(*id);
        }

        //need to build that node. First, recurse all dependend nodes and add them to the tree, then
        //build this instructions
        let mut args = SmallColl::new();
        let mut argidx = 0;
        while let Some(src) = self
            .graph
            .graph
            .node(llnode.node)
            .input_src(&self.graph.graph, argidx)
        {
            let id = self.get_port_id(src)?;
            args.push(Operand::IdRef(id));
            argidx += 1;
        }

        //not found, build the node
        let node = self
            .graph
            .graph
            .node(llnode.node)
            .node_type
            .unwrap_simple_ref();

        let llnode_ty = self
            .graph
            .type_table
            .attrib(&AttribLocation::OutPort(llnode))
            .expect("Node has no type information")[0]
            .clone();
        let result_ty = self.get_type_id(llnode_ty);

        //NOTE for all extended instructions we use
        // https://registry.khronos.org/SPIR-V/specs/unified1/GLSL.std.450.pdf
        //
        // NOTE:
        // All in all this is a pretty dirty way to generate the code. In a real world implementation we'd
        // analyse some type information of the node first and choose the correct ADD/SUB etc. implementation, reject
        // ops that are not possible etc.
        //
        // However, since this is a proof-of-concept anyways, we do it the _fast_ way for now.
        let opid: Word = match node.ty {
            LLOpTy::Abs => {
                assert!(args.len() == 1, "Abs expects only one operand");
                self.builder.ext_inst(
                    result_ty,
                    None,
                    self.glsl_ext_inst,
                    GlslExtInst::Abs as u32,
                    args,
                )?
            }
            LLOpTy::Add => {
                assert!(args.len() == 2, "Add needs to operands");
                assert!(llnode_ty != Ty::Int, "Add cannot use INT");
                self.builder.f_add(
                    result_ty,
                    None,
                    args[0].unwrap_id_ref(),
                    args[1].unwrap_id_ref(),
                )?
            }
            LLOpTy::Sub => {
                assert!(args.len() == 2, "Sub needs to operands");
                assert!(llnode_ty != Ty::Int, "Sub cannot use INT");
                self.builder.f_sub(
                    result_ty,
                    None,
                    args[0].unwrap_id_ref(),
                    args[1].unwrap_id_ref(),
                )?
            }
            LLOpTy::Mul => {
                assert!(args.len() == 2, "Mul needs to operands");
                assert!(llnode_ty != Ty::Int, "Mul cannot use INT");
                self.builder.f_mul(
                    result_ty,
                    None,
                    args[0].unwrap_id_ref(),
                    args[1].unwrap_id_ref(),
                )?
            }
            LLOpTy::Div => {
                assert!(args.len() == 2, "Div needs to operands");
                assert!(llnode_ty != Ty::Int, "Div cannot use INT");
                self.builder.f_div(
                    result_ty,
                    None,
                    args[0].unwrap_id_ref(),
                    args[1].unwrap_id_ref(),
                )?
            }
            LLOpTy::CoordSelect(selection) => {
                //for coord select, we use the
                // OpCompositeExtract with a the constant `selection` index to extract our vector's
                // element.
                assert!(
                    args.len() == 1,
                    "Coord selection can only select from one vec"
                );

                //emit thae access chain
                //let ty_u32 = self.builder.type_int(32, 0);
                //let element_id = self.builder.constant_u32(ty_u32, selection as u32);
                self.builder.composite_extract(
                    result_ty,
                    None,
                    args[0].unwrap_id_ref(),
                    [selection as u32],
                )?
            }
            LLOpTy::Dot => {
                //use the native dot instruction
                self.builder.dot(
                    result_ty,
                    None,
                    args[0].unwrap_id_ref(),
                    args[1].unwrap_id_ref(),
                )?
            }
            LLOpTy::Error => panic!("Found error op!"),
            LLOpTy::ImmF32(f) => {
                let ty_f32 = self.get_type_id(Ty::Float);
                self.builder.constant_f32(ty_f32, f32::from_bits(f))
            }
            LLOpTy::ImmI32(i) => {
                let ty_i32 = self.get_type_id(Ty::Int);
                self.builder
                    .constant_u32(ty_i32, u32::from_be_bytes(i.to_be_bytes()))
            }
            LLOpTy::Length => {
                assert!(args.len() == 1, "Length expects only one operand");
                self.builder.ext_inst(
                    result_ty,
                    None,
                    self.glsl_ext_inst,
                    GlslExtInst::Length as u32,
                    args,
                )?
            }
            LLOpTy::Max => {
                assert!(args.len() == 2, "Max expects two operands");
                self.builder.ext_inst(
                    result_ty,
                    None,
                    self.glsl_ext_inst,
                    GlslExtInst::Max as u32,
                    args,
                )?
            }
            LLOpTy::Min => {
                assert!(args.len() == 2, "Min expects two operands");
                self.builder.ext_inst(
                    result_ty,
                    None,
                    self.glsl_ext_inst,
                    GlslExtInst::Min as u32,
                    args,
                )?
            }
            LLOpTy::Round => {
                assert!(args.len() == 1, "Round expects one operand");
                self.builder.ext_inst(
                    result_ty,
                    None,
                    self.glsl_ext_inst,
                    GlslExtInst::Round as u32,
                    args,
                )?
            }
            LLOpTy::TypeConstruct(t) => match t {
                Ty::Error => panic!("Cannot construct error type"),
                Ty::Float => {
                    assert!(args.len() == 1, "Type construct of float expects one float");
                    args[0].unwrap_id_ref()
                }
                Ty::Int => {
                    assert!(args.len() == 1, "Type construct of int expects one int");
                    args[0].unwrap_id_ref()
                }
                Ty::Sdf => panic!("Cannot construct SDF value!"),
                Ty::Vec2 => {
                    assert!(args.len() == 2, "Vec2 expects two float arguments");
                    let ty_vec2 = self.get_type_id(Ty::Vec2);
                    assert!(result_ty == ty_vec2);
                    self.builder.composite_construct(
                        ty_vec2,
                        None,
                        [args[0].unwrap_id_ref(), args[1].unwrap_id_ref()],
                    )?
                }
                Ty::Vec3 => {
                    assert!(args.len() == 3, "Vec3 expects three float arguments");
                    let ty_vec3 = self.get_type_id(Ty::Vec3);
                    assert!(result_ty == ty_vec3);
                    self.builder.composite_construct(
                        ty_vec3,
                        None,
                        [
                            args[0].unwrap_id_ref(),
                            args[1].unwrap_id_ref(),
                            args[2].unwrap_id_ref(),
                        ],
                    )?
                }
                Ty::Vec4 => {
                    assert!(args.len() == 4, "Vec4 expects four float arguments");
                    let ty_vec4 = self.get_type_id(Ty::Vec4);
                    assert!(result_ty == ty_vec4);
                    self.builder.composite_construct(
                        ty_vec4,
                        None,
                        [
                            args[0].unwrap_id_ref(),
                            args[1].unwrap_id_ref(),
                            args[2].unwrap_id_ref(),
                            args[3].unwrap_id_ref(),
                        ],
                    )?
                }
            },
        };

        //Finally add to knwon nodes and return
        self.port_mapping.insert(llnode, opid);
        Ok(opid)
    }

    pub(crate) fn traverse_tree(&mut self) -> Result<Word, LoweringError> {
        //Since we are only returning a single float,
        //trace the first node , build the call tree recursively and then emit the root node

        let export_edge = self
            .graph
            .graph
            .node(self.graph.graph.entry_node())
            .node_type
            .unwrap_omega_ref()
            .get_export(0)
            .unwrap()
            .edge
            .unwrap();
        let root_node = self.graph.graph.edge(export_edge).src.clone();
        let export_node = self.get_port_id(root_node)?;

        Ok(export_node)
    }
}
