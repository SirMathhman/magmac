import re
from pathlib import Path

INT_TYPES = {
    "U8": "uint8_t",
    "U16": "uint16_t",
    "U32": "uint32_t",
    "U64": "uint64_t",
    "I8": "int8_t",
    "I16": "int16_t",
    "I32": "int32_t",
    "I64": "int64_t",
}


def _translate_function(
    name: str, body: str, params: list[tuple[str, str]] | None = None
) -> str:
    """Return the C code for a single function declaration."""
    if params:
        parts = [f"{INT_TYPES[p_type]} {p_name}" for p_name, p_type in params]
        param_decl = ", ".join(parts)
    else:
        param_decl = "void"

    if body.startswith("{"):
        return f"void {name}({param_decl}) {{\n}}\n"
    if body in {"true", "false"}:
        value = "1" if body == "true" else "0"
        return f"int {name}({param_decl}) {{\n    return {value};\n}}\n"
    c_type = INT_TYPES[body]
    return f"{c_type} {name}({param_decl}) {{\n    return 0;\n}}\n"


def compile_source(source: str) -> str:
    """Compile a Magma source string to C code."""
    pattern = re.compile(
        r"fn\s+(\w+)\s*\(\s*([^)]*)\)\s*=>\s*(true|false|\{\s*\}|[UI](?:8|16|32|64))"
    )
    param_pattern = re.compile(r"(\w+)\s*:\s*([UI](?:8|16|32|64))")
    output_lines = []

    for name, param_text, body in pattern.findall(source):
        params = param_pattern.findall(param_text)
        params_list = [tuple(p) for p in params] if params else None
        output_lines.append(_translate_function(name, body, params_list))

    return "".join(output_lines)


def compile_file(input_path: Path, output_path: Path) -> None:
    """Compile a file containing Magma code into a C file."""
    src = input_path.read_text()
    c_code = compile_source(src)
    output_path.write_text(c_code)
