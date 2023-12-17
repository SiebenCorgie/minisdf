use rvsdg_viewer::View;

use super::{LLOp, LLOpTy};

impl View for LLOp {
    fn color(&self) -> rvsdg_viewer::macroquad::color::Color {
        rvsdg_viewer::macroquad::color::Color::from_rgba(200, 100, 50, 255)
    }
    fn name(&self) -> &str {
        match &self.ty {
            LLOpTy::Abs => "abs",
            LLOpTy::Add => "add",
            LLOpTy::CoordSelect(_) => "coord select",
            LLOpTy::Div => "div",
            LLOpTy::Dot => "dot",
            LLOpTy::Error => "error",
            LLOpTy::Length => "length",
            LLOpTy::Max => "max",
            LLOpTy::Min => "min",
            LLOpTy::Mul => "mul",
            LLOpTy::Round => "round",
            LLOpTy::Sub => "sub",
            LLOpTy::ImmF32(_) => "f32",
            LLOpTy::ImmI32(_) => "i32",
            LLOpTy::TypeConstruct(_) => "type_constructor",
        }
    }
    fn stroke(&self) -> rvsdg_viewer::Stroke {
        rvsdg_viewer::Stroke::Line
    }
}
