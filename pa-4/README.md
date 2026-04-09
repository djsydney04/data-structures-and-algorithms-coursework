# PA-4 Blockchain Ledger

## Student Information

- Full Name: Dylan Mitic
- Student ID: 2441836
- Chapman Email: mitic@chapman.edu
- Course Number and Section: CPSC 350-02
- Assignment Number: pa-4

## Source Files Submitted

- `main.cpp`
- `block/block.h`
- `block/block.cpp`
- `blockchain/blockchain.h`
- `blockchain/blockchain.cpp`

## Known Issues / Limitations / Deviations

- None known

## References

- C++ timestamp reference (used for `ctime()` formatting)
- Codex wrote tests inside of `/tests` to help me verify code outputs

### Compile + run the program

```bash
g++ -std=c++17 -Wall -Wextra main.cpp block/block.cpp blockchain/blockchain.cpp -o p4.exe
./p4.exe
```


### Compile + run tests

I've also included tests, in case it is helpful in grading or interesting! 

```bash
# Block test
g++ -std=c++17 -Wall -Wextra tests/block_test.cpp block/block.cpp -o block_test
./block_test

# Blockchain test
g++ -std=c++17 -Wall -Wextra tests/blockchain_test.cpp block/block.cpp blockchain/blockchain.cpp -o blockchain_test
./blockchain_test
```

You can find more details about the tests are in `tests/README.md`.
