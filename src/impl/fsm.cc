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

vector<token*> fsm::parse() {
    vector<token*> token_stream;
    block_iterator it = this->block->get_iterator();
    char curr_char;
    string curr_string;
    token *curr_token;

    while (it.has_next()){
        curr_char = it.next();

        switch (current_state) {
            case parser_state::START:
                if (curr_char == ' ' || curr_char == '\t' || curr_char == '\n' || curr_char == '\r') {
                    transition(parser_state::IN_WHITESPACE);
                    break;
                }
            case parser_state::IN_WHITESPACE:
                if (isalpha(curr_char) || curr_char == '_') {
                    curr_string += curr_char;
                    transition(parser_state::IN_IDENTIFIER);
                }else if (curr_char == '#'){
                    transition(parser_state::IN_PREPROCESSOR_DIRECTIVE);
                }
                break;
            case parser_state::IN_IDENTIFIER:
                if (isalnum(curr_char) || curr_char == '_') {
                    curr_string += curr_char;
                } else {
                    curr_token = new identifier_token(curr_string, it.current_ref());
                    token_stream.push_back(curr_token);
                    curr_string.clear();
                    if (it.has_prev()) it.prev();
                    transition(parser_state::START);
                }
                break;
            case parser_state::IN_PREPROCESSOR_DIRECTIVE:
                if (isalpha(curr_char)) {
                    curr_string += curr_char;
                }else if (curr_char == '"' || curr_char == '<' || curr_char == '\'' || curr_char == ' ' || curr_char == '\t'){
                    if (preprocessor_directive_token::directive_map.find(curr_string) != preprocessor_directive_token::directive_map.end()) {
                        curr_token = new preprocessor_directive_token(curr_string, it.current_ref());
                        token_stream.push_back(curr_token);
                    } else {
                        throw invalid_argument("Expected preprocessor directive : " + curr_string + " at " + it.current_ref().toString());
                    }
                }
            default:
                break;
        }
    }
    return token_stream;
}