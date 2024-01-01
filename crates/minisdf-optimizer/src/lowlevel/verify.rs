use crate::{err::OptError, LLGraph};

impl LLGraph {
    pub fn verify(&self) -> Result<(), OptError> {
        //TODO implement type checking. As sepecially that any
        // CoordSelect operation on a wide enough vector.
        println!("TODO: Implement Lowlevel graph checking");
        Ok(())
    }
}
