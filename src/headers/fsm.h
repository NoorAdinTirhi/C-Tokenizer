#pragma once
#include "fsm_state_enum.h"
#include "tokens.h"
#include "source_ref.h"
using namespace std;
struct parse_info;

struct fsm {
    parser_state current_state;
    source_block* block;

    fsm();
    fsm(source_block *block);
    void transition(parser_state new_state);
    parser_state get_current_state() const;
    vector<token*> parse();

    void start_state(parse_info* info);
    void whitespace_state(parse_info* info);
    void identifier_state(parse_info* info);
    void preprocessor_directive_state(parse_info* info);
};

struct parse_info {
    vector<token*> token_stream;
    char current_char;
    string current_string;
    token* current_token;

    bool string_has_underscore;

    parse_info();
    void reset();
};
