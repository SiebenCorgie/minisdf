use rvsdg::edge::LangEdge;
use rvsdg_viewer::View;

pub enum OptEdge {
    State,
    Value,
}

impl LangEdge for OptEdge {
    fn is_state_edge(&self) -> bool {
        if let OptEdge::State = self {
            true
        } else {
            false
        }
    }
    fn is_value_edge(&self) -> bool {
        if let OptEdge::Value = self {
            true
        } else {
            false
        }
    }

    fn state_edge() -> Self {
        Self::State
    }

    fn value_edge() -> Self {
        Self::Value
    }
}

impl View for OptEdge {
    fn color(&self) -> rvsdg_viewer::macroquad::color::Color {
        rvsdg_viewer::macroquad::color::Color::from_rgba(0, 0, 0, 255)
    }
    fn name(&self) -> &str {
        match self {
            OptEdge::State => "state",
            OptEdge::Value => "value",
        }
    }
    fn stroke(&self) -> rvsdg_viewer::Stroke {
        match self {
            OptEdge::State => rvsdg_viewer::Stroke::Dashs,
            OptEdge::Value => rvsdg_viewer::Stroke::Line,
        }
    }
}
