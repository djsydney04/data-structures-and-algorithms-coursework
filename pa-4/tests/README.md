# Blockchain tests

This folder contains lightweight C++ tests for the assignment classes:

- `block_test.cpp`
- `blockchain_test.cpp`

`block_test.cpp` checks that:

- the constructor stores the index, data, and previous hash correctly
- the timestamp is not empty
- the block hash matches the expected value from the assignment rules

`blockchain_test.cpp` checks that:

- the constructor creates the required genesis block
- `addBlock()` appends blocks with the correct index and previous hash
- `validateChain()` accepts a valid chain
- `displayChain()` prints blocks in order
- `saveToFile()` writes the required `index|timestamp|data|previousHash|currentHash` format
- `loadFromFile()` reconstructs a saved blockchain
- `validateChain()` rejects tampered current hashes and broken previous-hash links

## Compile and run

From the `pa-4` directory:

```bash
g++ -std=c++17 -Wall -Wextra tests/block_test.cpp block/block.cpp -o block_test
./block_test

g++ -std=c++17 -Wall -Wextra tests/blockchain_test.cpp block/block.cpp blockchain/blockchain.cpp -o blockchain_test
./blockchain_test
```

From the `pa-4/tests` directory:

```bash
cd tests
g++ -std=c++17 -Wall -Wextra block_test.cpp ../block/block.cpp -o block_test
./block_test

g++ -std=c++17 -Wall -Wextra blockchain_test.cpp ../block/block.cpp ../blockchain/blockchain.cpp -o blockchain_test
./blockchain_test
```

## What passing looks like

Each test prints `[PASS]` or `[FAIL]` messages.

- On success, the program ends with `All Block tests passed.` or `All Blockchain tests passed.`
- On failure, it exits with code `1`.

## Clean up binaries

```bash
rm -f block_test blockchain_test
```
