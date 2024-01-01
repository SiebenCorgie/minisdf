use clap::Parser;
use std::{path::PathBuf, process::ExitCode};

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
pub struct Args {
    #[arg(short, long = "input")]
    input: PathBuf,

    #[arg(short, long = "output")]
    output: Option<String>,
}

fn main() -> Result<(), ExitCode> {
    let args = Args::parse();

    let result = match msdfc::compile_file(&args.input) {
        Err(e) => {
            println!("Failed to compile file: {e:?}");
            return Err(ExitCode::FAILURE);
        }
        Ok(k) => k,
    };

    let file_prefix = args.output.unwrap_or("sdf".to_owned());
    for (name, module) in result {
        println!("Generated field {}", name);
        std::fs::write(
            format!("{file_prefix}_{name}.spv"),
            bytemuck::cast_slice(&module),
        )
        .unwrap();
    }

    Ok(())
}
