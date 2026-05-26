#pragma once
#include <unordered_set>
#include "fsm_state_enum.h"
#include "tokens.h"
#include "source_ref.h"
#include "iostream"
using namespace std;
struct parse_info;

struct fsm {
    parser_state current_state;
    source_block* block;

    static unordered_set<char> whitespace_chars;
    static unordered_set<char> operator_chars;
    static unordered_set<char> punctuation_chars;

    fsm();
    fsm(source_block *block);
    void transition(parser_state new_state);
    parser_state get_current_state() const;
    vector<token*> parse();

    void start_state(parse_info* info);
    void whitespace_state(parse_info* info);
    void identifier_state(parse_info* info);
    void preprocessor_directive_state(parse_info* info);
    void string_literal_state(parse_info* info);
    void numeric_literal_state(parse_info* info);
    void operator_state(parse_info* info);
    void punctuator_state(parse_info* info);
    static void init_sets();
};

struct parse_info {
    vector<token*> token_stream;
    char current_char;
    string current_string;
    token* current_token;

    bool string_has_underscore;
    bool string_literal_for_lib;
    bool last;

    parse_info();
    void reset();
    string to_string() const;
};
