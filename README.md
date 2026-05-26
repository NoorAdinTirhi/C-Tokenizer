# C-Tokenizer
a C++ pet project for fun and learning, reads C source code and converts it to a stream of tokens, this is the first stage of a parser that constructs an abstract syntax tree(which I will probably never get to).

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
run this command:
```bash
$ bin/run
```

this will run the one test case in the test directory test/test.c and output the tokens in JSON format to the test/ref/test.log file.
