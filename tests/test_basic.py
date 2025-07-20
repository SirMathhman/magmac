import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from magmac.__main__ import main


def test_main_output(capsys):
    main([])
    captured = capsys.readouterr()
    assert "Hello from Magmac!" in captured.out


def test_compile_empty_function(tmp_path):
    input_file = tmp_path / "in.mg"
    input_file.write_text("fn empty() => {}")
    output_file = tmp_path / "out.c"
    main(["-i", str(input_file), "-o", str(output_file)])
    assert output_file.read_text() == "void empty(void) {\n}\n"
