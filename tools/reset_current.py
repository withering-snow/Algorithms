from pathlib import Path
from typing import Optional
import shutil
import sys


def find_algorithm_dir(start: Path) -> Optional[Path]:
    start = start.resolve()

    if start.is_file():
        start = start.parent

    for directory in [start, *start.parents]:
        template = directory / "template.cpp"
        current = directory / "current.cpp"

        if template.exists() and current.exists():
            return directory

    return None


def main():
    if len(sys.argv) >= 2:
        start = Path(sys.argv[1])
    else:
        start = Path.cwd()

    algorithm_dir = find_algorithm_dir(start)

    if algorithm_dir is None:
        print("未找到算法目录。")
        print("要求目录中同时存在 template.cpp 和 current.cpp。")
        sys.exit(1)

    template = algorithm_dir / "template.cpp"
    current = algorithm_dir / "current.cpp"

    shutil.copyfile(template, current)

    print(f"已恢复：{current}")
    print(f"模板来源：{template}")


if __name__ == "__main__":
    main()