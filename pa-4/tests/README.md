# Tests

This folder contains simple tests you can run with `g++`:

- `block_test.cpp`: tests `Block`
- `blockchain_test.cpp`: tests `Blockchain`

## Run from `pa-4/` (recommended)

```bash
# Block test (no output = pass)
g++ -std=c++17 -Wall -Wextra tests/block_test.cpp block/block.cpp -o block_test
./block_test

# Blockchain test (prints [PASS]/[FAIL])
g++ -std=c++17 -Wall -Wextra tests/blockchain_test.cpp block/block.cpp blockchain/blockchain.cpp -o blockchain_test
./blockchain_test
```

## What “pass” looks like

- `block_test`: exits with code `0` and prints nothing.
- `blockchain_test`: prints `[PASS] ...` lines and ends with `All Blockchain tests passed.`
