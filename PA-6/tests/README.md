# PA6 Test Suite

Run these tests from the assignment root:

```bash
python3 tests/run_tests.py
```

The test runner compiles the submitted root-level `.cpp` files with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic *.cpp -o pa6_program
```

It then runs the program with each file in `tests/inputs/` and checks that:

- the program accepts the input filename as a command-line argument;
- the output includes an MST cost line;
- the output includes an `N x N` adjacency matrix;
- the matrix is symmetric, has a zero diagonal, and only uses edges from the input;
- the matrix has exactly `N - 1` edges and connects all vertices;
- the reported cost equals the cost of the matrix and the expected minimum cost.

Some graphs have multiple valid MSTs, so those tests validate the MST properties
instead of requiring one exact adjacency matrix.
