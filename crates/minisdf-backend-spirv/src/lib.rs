use ahash::AHashMap;
use err::LoweringError;
use minisdf_ast::Ty;
use minisdf_optimizer::{rvsdg::edge::OutportLocation, LLGraph};
use rspirv::spirv::{self, Word};
mod err;

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

        let mut builder = module_harness();

        LoweringCtx {
            graph: self,
            builder,
            known_types: AHashMap::default(),
            port_mapping: AHashMap::default(),
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
    fn begin_function(&mut self) -> Result<(), LoweringError> {
        //TODO: collect all arguments and build function type, then register outports
        // for arguments and go
    }
    fn lower(&mut self) -> Result<rspirv::dr::Module, LoweringError> {}
}

fn module_harness() -> rspirv::dr::Builder {
    let mut b = rspirv::dr::Builder::new();
    b.memory_model(spirv::AddressingModel::Logical, spirv::MemoryModel::GLSL450);
    b.capability(spirv::Capability::Shader);
    b.set_version(1, 5);
    b
}
