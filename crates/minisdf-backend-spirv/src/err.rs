use thiserror::Error;

#[derive(Debug, Error)]
pub enum LoweringError {
    #[error("SPIR-V Data-Representation error: {0}")]
    DRError(#[from] rspirv::dr::Error),
}
