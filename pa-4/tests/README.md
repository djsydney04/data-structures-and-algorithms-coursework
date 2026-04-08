# Block tests

This folder contains a smoke test for the `Block` class:

- `block_test.cpp`

The test checks that:

- the constructor stores the index, data, and previous hash correctly
- the timestamp is not empty
- the block hash matches the expected value (same rules as your assignment: concatenate fields, sum ASCII codes, print sum as hex)

## Compile and run

**From the `pa-4/tests` directory** (paths match the `#include "../block/block.h"` in the test):

```bash
cd tests
g++ -std=c++17 -Wall -Wextra block_test.cpp ../block/block.cpp -o block_test
./block_test
```

**From the `pa-4` directory** (assignment root):

```bash
g++ -std=c++17 -Wall -Wextra tests/block_test.cpp block/block.cpp -o block_test
./block_test
```

Quoted includes like `"../block/block.h"` are resolved relative to the `.cpp` file’s directory (`tests/`), so this works without extra `-I` flags.

## What passing looks like

The test now prints explicit pass/fail messages.

- **Pass:** each check prints a `[PASS]` line, followed by an example `Block` object and `All Block tests passed.`
- **Fail:** the program prints a `[FAIL]` line for the check that did not match expectations and exits with code `1`.

On macOS/Linux you can confirm the exit code:

```bash
./block_test
echo $?
```

`0` means success.

## Clean up the binary (optional)

```bash
rm -f block_test
```
