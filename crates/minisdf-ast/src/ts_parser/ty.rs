use minisdf_common::Span;
use tree_sitter::Node;

use crate::{PrimTy, Tree, Ty};

use super::{err::TSParseError, report_error};

pub fn parse_type(data: &[u8], node: &Node) -> Ty {
    if !TSParseError::check_token(node, "type") {
        return Ty::Error;
    }

    let name = match node.utf8_text(data) {
        Err(_e) => {
            report_error(TSParseError::InvalidIdent, Span::from(node));
            "invalid_ident".to_owned()
        }
        Ok(s) => s.to_owned(),
    };

    match name.as_str() {
        "float" => Ty::Float,
        "vec2" => Ty::Vec2,
        "vec3" => Ty::Vec3,
        "vec4" => Ty::Vec4,
        _ => {
            report_error(TSParseError::UnknownType(name), Span::from(node));
            Ty::Error
        }
    }
}
