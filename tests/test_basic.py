import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

from magmac.__main__ import main


def test_main_output(capsys):
    main([])
    captured = capsys.readouterr()
    assert "Hello from Magmac!" in captured.out


def test_create_output_file(tmp_path):
    input_file = tmp_path / "in.txt"
    input_file.write_text("data")
    output_file = tmp_path / "out.txt"
    main(["-i", str(input_file), "-o", str(output_file)])
    assert output_file.exists()
