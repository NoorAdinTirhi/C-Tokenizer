#pragma once
#include "fsm_state_enum.h"
#include "tokens.h"
#include "source_ref.h"
using namespace std;

class fsm {
    parser_state current_state;
    source_block* block;
public:
    fsm();
    fsm(source_block *block);
    void transition(parser_state new_state);
    parser_state get_current_state() const;
    vector<token> parse();
};