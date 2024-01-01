use ahash::AHashMap;
use minisdf_ast::Ty;
use minisdf_optimizer::{
    rvsdg::{
        attrib::AttribLocation,
        edge::{OutportLocation, OutputType},
        SmallColl,
    },
    LLGraph,
};
pub use rspirv;
use rspirv::{
    dr::Operand,
    spirv::{self, Decoration, FunctionControl, LinkageType, Word},
};
mod err;
pub use err::LoweringError;
mod lltraversal;

pub trait SpirvBackend {
    fn lower(&self) -> Result<rspirv::dr::Module, LoweringError>;
}

impl SpirvBackend for LLGraph {
    fn lower(&self) -> Result<rspirv::dr::Module, LoweringError> {
        //NOTE: This is a really simple lowering strategy for the LLGraph.
        //
        // We exploit the fact, that all instructions are in the top-level region, and
        // that everything _should_ be inlined by now.
        // We first add a module _harness_ that lets us build a function. We then define the function based on all imports
        // to the top-level and exports from the top-level.
        // Finally we start that function, iterate the reachable graph in reverse.
        //      For each node, we emit the node and safe it in the _seen_nodes_ table.
        //      This will allow us to reference any arguments used later in the SPIR-V
        //      module by SPIR-V id.

        let (builder, glsl_ext_inst) = module_harness();

        LoweringCtx {
            graph: self,
            builder,
            known_types: AHashMap::default(),
            port_mapping: AHashMap::default(),
            glsl_ext_inst,
        }
        .lower()
    }
}

pub struct LoweringCtx<'a> {
    graph: &'a LLGraph,
    builder: rspirv::dr::Builder,

    known_types: AHashMap<Ty, Word>,
    ///Maps a portlocation to the SSE value, if it exists.
    port_mapping: AHashMap<OutportLocation, Word>,
    glsl_ext_inst: Word,
}

impl<'a> LoweringCtx<'a> {
    fn get_type_id(&mut self, ty: Ty) -> Word {
        if let Some(known) = self.known_types.get(&ty) {
            *known
        } else {
            let tid = match ty {
                Ty::Error => panic!("Type \"Error\" cannot be registered!"),
                Ty::Sdf => panic!("Found type \"SDF\" in backend, which is unexpected"),
                Ty::Float => self.builder.type_float(32),
                Ty::Int => self.builder.type_int(32, 1),
                Ty::Vec2 => {
                    let fid = self.get_type_id(Ty::Float);
                    self.builder.type_vector(fid, 2)
                }
                Ty::Vec3 => {
                    let fid = self.get_type_id(Ty::Float);
                    self.builder.type_vector(fid, 3)
                }
                Ty::Vec4 => {
                    let fid = self.get_type_id(Ty::Float);
                    self.builder.type_vector(fid, 4)
                }
            };

            self.known_types.insert(ty, tid);
            tid
        }
    }

    ///Moves the builder into the function representing the ω-Node's region.
    ///
    /// Returns the function id
    fn begin_function(&mut self) -> Result<u32, LoweringError> {
        //TODO: collect all arguments and build function type, then register outports
        // for arguments and go

        //First of all, build the function type based on the imported types as well as the f32-output type

        let argument_types = {
            let omg = self
                .graph
                .graph
                .node(self.graph.graph.entry_node())
                .node_type
                .unwrap_omega_ref();
            let mut imports = SmallColl::new();
            let mut import_idx = 0;
            while let Some(_import_port) = omg.get_import(import_idx) {
                println!("Port on {}", import_idx);
                let port_location = OutportLocation {
                    node: self.graph.graph.entry_node(),
                    output: OutputType::Argument(import_idx),
                };
                if let Some(tyinfo) = self
                    .graph
                    .type_table
                    .attrib(&AttribLocation::OutPort(port_location))
                {
                    imports.push(self.get_type_id(tyinfo[0].clone()));
                } else {
                    panic!("Argument port {} has no type information!", import_idx);
                }

                import_idx += 1;
            }

            imports
        };

        assert!(
            argument_types[0] == self.get_type_id(Ty::Vec3),
            "First type should be vec3 representing the eval location!"
        );

        let tyf32 = self.get_type_id(Ty::Float);
        let f32_function = self.builder.type_function(tyf32, argument_types.clone());

        let fun = self.builder.begin_function(
            tyf32,
            None,
            FunctionControl::DONT_INLINE | FunctionControl::PURE,
            f32_function,
        )?;

        //Decorate function wit export and the name given to this graph
        self.builder.decorate(
            fun,
            Decoration::LinkageAttributes,
            [
                Operand::LiteralString(self.graph.name.clone()),
                Operand::LinkageType(LinkageType::Export),
            ],
        );

        for (arg_idx, arg_ty) in argument_types.into_iter().enumerate() {
            let arg_id = self.builder.function_parameter(arg_ty)?;
            //register port as id
            let pm = self.port_mapping.insert(
                OutportLocation {
                    node: self.graph.graph.entry_node(),
                    output: OutputType::Argument(arg_idx),
                },
                arg_id,
            );

            assert!(pm.is_none());
        }

        //setup the basic block
        let _bbid = self.builder.begin_block(None).unwrap();

        Ok(fun)
    }

    //Ends the sdf function creation by by hooking up the `sdf_id` to the return value, and ending the function.
    fn finish_function(&mut self, sdf_id: u32) -> Result<(), LoweringError> {
        self.builder.ret_value(sdf_id)?;
        self.builder.end_function()?;
        Ok(())
    }

    fn lower(mut self) -> Result<rspirv::dr::Module, LoweringError> {
        //Create the export function
        self.begin_function()?;

        //now traverse the LLGraph recursively and emit all instructions.
        let sdf_id = self.traverse_tree()?;

        //Finally end the function by hooking up the sdf_id to the return value, and end the function.
        self.finish_function(sdf_id)?;

        let finished_module = self.builder.module();
        Ok(finished_module)
    }
}

fn module_harness() -> (rspirv::dr::Builder, Word) {
    let mut b = rspirv::dr::Builder::new();
    b.memory_model(spirv::AddressingModel::Logical, spirv::MemoryModel::GLSL450);
    b.capability(spirv::Capability::Shader);
    b.capability(spirv::Capability::Linkage);
    b.set_version(1, 5);
    //always register extended instructionset
    let extinst = b.ext_inst_import("GLSL.std.450");
    (b, extinst)
}
