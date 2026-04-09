# PA-4 Blockchain Ledger

- `block/block.h`, `block/block.cpp`: `Block` implementation
- `blockchain/blockchain.h`, `blockchain/blockchain.cpp`: `Blockchain` implementation
- `tests/block_test.cpp`: `Block` unit test
- `tests/blockchain_test.cpp`: `Blockchain` unit test

Compile and run the tests from the assignment root:

```bash
g++ -std=c++17 -Wall -Wextra tests/block_test.cpp block/block.cpp -o block_test
./block_test

g++ -std=c++17 -Wall -Wextra tests/blockchain_test.cpp block/block.cpp blockchain/blockchain.cpp -o blockchain_test
./blockchain_test
```

See [tests/README.md](tests/README.md) for test coverage details.
