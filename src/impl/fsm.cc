#include "fsm.h"
fsm::fsm() {
    this->current_state = parser_state::START;
    this->block = nullptr;
}
fsm::fsm(source_block* block) {
    this->current_state = parser_state::START;
    this->block = block;
}

void fsm::transition(parser_state new_state) {
    this->current_state = new_state;
}

vector<token> fsm::parse() {
    vector<token> token_stream;
    block_iterator it = this->block->get_iterator();
    char curr_char;
    while (it.has_next()){
        curr_char = it.next();

        switch (current_state) {
            case parser_state::START:
                if (curr_char == ' ' || curr_char == '\t' || curr_char == '\n' || curr_char == '\r') {
                    transition(parser_state::IN_WHITESPACE);
                    break;
                }
                break;// remove this later
            case parser_state::IN_WHITESPACE:
                if (isalpha(curr_char) || curr_char == '_') {
                    transition(parser_state::IN_IDENTIFIER);
                }else if (curr_char == '#'){
                    transition(parser_state::IN_PREPROCESSOR_DIRECTIVE);
                }
                break;
            case parser_state::IN_IDENTIFIER:
                //handle in identifier state
                break;
            default:
                break;
        }
    }
    return token_stream;
}