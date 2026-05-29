# C-Tokenizer
a C++ pet project for fun and learning, reads C source code and converts it to a stream of tokens, this is the first stage of a parser that constructs an abstract syntax tree(which I will probably never get to).
# Dependencies
- build-essentials
- nlohmann/json for C++
- g++
# how to run
run git clone and cd into the repo:
```bash
$ git clone https://github.com/NoorAdinTirhi/C-Tokenizer
$ cd C-Tokenizer
```
run make:
```bash
$ make
```
run this command to tokenize a C file:
```bash
$ bin/run -i <path to input C file> -o <path to output file>
```

the test directory contains working cases, you can run specific ones using the command above,
you can also run ``` test/reg_script.sh ``` from the base dir to run all the tests.
