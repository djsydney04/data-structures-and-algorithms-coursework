#!/usr/bin/env python3
"""
Black-box tests for CPSC 350 PA6.

The runner compiles the assignment source files, executes the program on each
test input, and validates the reported MST cost and adjacency matrix.
"""

from __future__ import annotations

import argparse
import math
import os
import pathlib
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass


ROOT = pathlib.Path(__file__).resolve().parents[1]
INPUT_DIR = ROOT / "tests" / "inputs"


@dataclass(frozen=True)
class TestCase:
    name: str
    filename: str
    expected_cost: float
    expected_matrix: tuple[tuple[float, ...], ...] | None = None


TEST_CASES = [
    TestCase(
        name="assignment_sample",
        filename="assignment_sample.txt",
        expected_cost=8.0,
        expected_matrix=(
            (0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0),
            (1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0),
            (0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0),
            (1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
            (0.0, 0.0, 1.0, 0.0, 0.0, 2.0, 2.0),
            (0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0),
            (0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0),
        ),
    ),
    TestCase(
        name="decimal_weights",
        filename="decimal_weights.txt",
        expected_cost=4.5,
        expected_matrix=(
            (0.0, 1.5, 0.0, 0.0),
            (1.5, 0.0, 2.25, 0.0),
            (0.0, 2.25, 0.0, 0.75),
            (0.0, 0.0, 0.75, 0.0),
        ),
    ),
    TestCase(
        name="tie_allows_multiple_msts",
        filename="tie_allows_multiple_msts.txt",
        expected_cost=5.0,
    ),
    TestCase(
        name="dense_graph",
        filename="dense_graph.txt",
        expected_cost=11.0,
    ),
    TestCase(
        name="single_vertex",
        filename="single_vertex.txt",
        expected_cost=0.0,
        expected_matrix=((0.0,),),
    ),
]


NUMBER_RE = re.compile(r"[-+]?(?:\d+(?:\.\d*)?|\.\d+)")


def compile_program(cxx: str, keep_build: bool) -> tuple[pathlib.Path, tempfile.TemporaryDirectory[str] | None]:
    source_files = sorted(ROOT.glob("*.cpp"))
    if not source_files:
        raise AssertionError("No .cpp source files found in the assignment root.")

    if keep_build:
        build_dir = ROOT / "tests" / ".build"
        build_dir.mkdir(exist_ok=True)
        temp_dir = None
    else:
        temp_dir = tempfile.TemporaryDirectory(prefix="pa6-tests-")
        build_dir = pathlib.Path(temp_dir.name)

    exe = build_dir / "pa6_program"
    command = [
        cxx,
        "-std=c++17",
        "-Wall",
        "-Wextra",
        "-pedantic",
        *[str(path) for path in source_files],
        "-o",
        str(exe),
    ]
    result = subprocess.run(command, cwd=ROOT, text=True, capture_output=True)
    if result.returncode != 0:
        joined = " ".join(command)
        raise AssertionError(
            "Compilation failed.\n"
            f"Command: {joined}\n\n"
            f"stdout:\n{result.stdout}\n\n"
            f"stderr:\n{result.stderr}"
        )
    return exe, temp_dir


def read_input_matrix(input_path: pathlib.Path) -> list[list[float]]:
    lines = input_path.read_text(encoding="utf-8").splitlines()
    n = int(lines[0].strip())
    matrix: list[list[float]] = []
    for row in lines[1 : 1 + n]:
        values = [float(token) for token in row.split()]
        if len(values) != n:
            raise AssertionError(f"{input_path.name} has a row with {len(values)} values, expected {n}.")
        matrix.append(values)
    return matrix


def run_program(exe: pathlib.Path, input_path: pathlib.Path) -> str:
    result = subprocess.run([str(exe), str(input_path)], cwd=ROOT, text=True, capture_output=True)
    if result.returncode != 0:
        raise AssertionError(
            f"Program exited with status {result.returncode} for {input_path.name}.\n"
            f"stdout:\n{result.stdout}\n\n"
            f"stderr:\n{result.stderr}"
        )
    return result.stdout


def parse_output(output: str, n: int) -> tuple[float, list[list[float]]]:
    cost = None
    for line in output.splitlines():
        if "cost" in line.lower():
            numbers = NUMBER_RE.findall(line)
            if numbers:
                cost = float(numbers[-1])
                break
    if cost is None:
        raise AssertionError("Could not find an MST cost line in the program output.")

    numeric_rows: list[list[float]] = []
    for line in output.splitlines():
        values = NUMBER_RE.findall(line)
        if len(values) == n and not re.search(r"[A-Za-z]", line):
            numeric_rows.append([float(value) for value in values])

    if len(numeric_rows) < n:
        raise AssertionError(
            f"Could not find {n} adjacency-matrix rows in output. Found {len(numeric_rows)} numeric rows."
        )

    return cost, numeric_rows[-n:]


def assert_close(actual: float, expected: float, label: str) -> None:
    if not math.isclose(actual, expected, rel_tol=1e-9, abs_tol=1e-9):
        raise AssertionError(f"{label}: expected {expected}, got {actual}.")


def validate_mst_matrix(
    original: list[list[float]],
    mst: list[list[float]],
    reported_cost: float,
    expected_cost: float,
    expected_matrix: tuple[tuple[float, ...], ...] | None,
) -> None:
    n = len(original)
    if len(mst) != n or any(len(row) != n for row in mst):
        raise AssertionError(f"MST matrix must be {n}x{n}.")

    for i in range(n):
        assert_close(mst[i][i], 0.0, f"matrix[{i}][{i}]")
        for j in range(n):
            assert_close(mst[i][j], mst[j][i], f"matrix symmetry at [{i}][{j}]")
            if mst[i][j] != 0.0 and original[i][j] == 0.0:
                raise AssertionError(f"MST uses edge {i}-{j}, but that edge is not in the input graph.")
            if mst[i][j] != 0.0:
                assert_close(mst[i][j], original[i][j], f"weight for edge {i}-{j}")

    edge_count = 0
    calculated_cost = 0.0
    parent = list(range(n))

    def find(node: int) -> int:
        while parent[node] != node:
            parent[node] = parent[parent[node]]
            node = parent[node]
        return node

    def union(left: int, right: int) -> bool:
        root_left = find(left)
        root_right = find(right)
        if root_left == root_right:
            return False
        parent[root_right] = root_left
        return True

    for i in range(n):
        for j in range(i + 1, n):
            if mst[i][j] != 0.0:
                edge_count += 1
                calculated_cost += mst[i][j]
                if not union(i, j):
                    raise AssertionError(f"MST matrix contains a cycle involving edge {i}-{j}.")

    expected_edges = max(0, n - 1)
    if edge_count != expected_edges:
        raise AssertionError(f"MST should contain {expected_edges} edges, got {edge_count}.")

    if n > 0:
        root = find(0)
        for vertex in range(n):
            if find(vertex) != root:
                raise AssertionError("MST matrix does not connect all vertices.")

    assert_close(calculated_cost, expected_cost, "calculated MST matrix cost")
    assert_close(reported_cost, expected_cost, "reported MST cost")

    if expected_matrix is not None:
        for i, expected_row in enumerate(expected_matrix):
            for j, expected_value in enumerate(expected_row):
                assert_close(mst[i][j], expected_value, f"exact matrix value [{i}][{j}]")


def run_tests(cxx: str, keep_build: bool) -> int:
    exe, temp_dir = compile_program(cxx, keep_build)
    failures: list[str] = []

    try:
        for case in TEST_CASES:
            input_path = INPUT_DIR / case.filename
            original = read_input_matrix(input_path)
            try:
                output = run_program(exe, input_path)
                cost, mst = parse_output(output, len(original))
                validate_mst_matrix(original, mst, cost, case.expected_cost, case.expected_matrix)
                print(f"PASS {case.name}")
            except AssertionError as error:
                failures.append(f"FAIL {case.name}\n{error}")
                print(f"FAIL {case.name}")
    finally:
        if temp_dir is not None:
            temp_dir.cleanup()

    if failures:
        print("\n" + "\n\n".join(failures), file=sys.stderr)
        return 1

    print(f"\nAll {len(TEST_CASES)} PA6 tests passed.")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser(description="Compile and test the PA6 MST program.")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"), help="C++ compiler to use.")
    parser.add_argument("--keep-build", action="store_true", help="Keep tests/.build/pa6_program after running.")
    args = parser.parse_args()
    try:
        return run_tests(args.cxx, args.keep_build)
    except AssertionError as error:
        print(f"ERROR\n{error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
