import json
import shutil
from argparse import ArgumentParser
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_OUTPUT_DIR = SCRIPT_DIR / "raw_code"


def parse_args():
    parser = ArgumentParser(description="Export generated JSON samples into per-file C sources for static checking.")
    parser.add_argument("--input-json", required=True, help="Path to the generated JSON file.")
    parser.add_argument("--output-dir", default=str(DEFAULT_OUTPUT_DIR), help="Directory to write extracted code files.")
    return parser.parse_args()


def main():
    args = parse_args()
    input_json = Path(args.input_json).resolve()
    output_dir = Path(args.output_dir).resolve()

    if output_dir.exists():
        shutil.rmtree(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    with input_json.open(encoding="utf-8") as f:
        data = json.load(f)

    for index, item in enumerate(data):
        file_name = item.get("file_name", f"sample_{index}.c")
        file_path = output_dir / file_name
        code = item.get("code", item.get("func", ""))
        with file_path.open("w", encoding="utf-8") as f:
            f.write(code)


if __name__ == "__main__":
    main()
