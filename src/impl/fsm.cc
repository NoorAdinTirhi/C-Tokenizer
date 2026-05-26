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
    block_iterator it = this->block->get_iterator();
    
    parse_info info;

    while (it.has_next()){
        info.current_char = it.next();

        switch (current_state) {
            case parser_state::START:
                start_state(&info);
                break;
            case parser_state::IN_WHITESPACE:
                whitespace_state(&info);
                break;
            
            case parser_state::IN_IDENTIFIER:
                identifier_state(&info);
                break;
            
            case parser_state::IN_PREPROCESSOR_DIRECTIVE:
                preprocessor_directive_state(&info);
                break;
            default:
                break;
        }
    }
    return info.token_stream;
}

void fsm::start_state(parse_info* info) {
    if (info->current_char == ' ' || info->current_char == '\t' || info->current_char == '\n' || info->current_char == '\r') {
        transition(parser_state::IN_WHITESPACE);
    } else if (isalpha(info->current_char) || info->current_char == '_') {
        info->current_string += info->current_char;
        transition(parser_state::IN_IDENTIFIER);
    } else if (info->current_char == '#') {
        transition(parser_state::IN_PREPROCESSOR_DIRECTIVE);
    }
    //support the other states
};

void fsm::whitespace_state(parse_info* info) {
    if (info->current_char == ' ' || info->current_char == '\t' || info->current_char == '\n' || info->current_char == '\r') {
        // stay in whitespace
    } else if (isalpha(info->current_char) || info->current_char == '_') {
        info->current_string += info->current_char;
        transition(parser_state::IN_IDENTIFIER);
    } else if (info->current_char == '#') {
        transition(parser_state::IN_PREPROCESSOR_DIRECTIVE);
    }
    //support the other states
};

void fsm::identifier_state(parse_info* info) {
    block_iterator it = this->block->get_iterator();
    
    if (isalnum(info->current_char) || info->current_char == '_') {
        info->current_string += info->current_char;
    } else {
        info->current_token = new identifier_token(info->current_string, it.current_ref());
        info->token_stream.push_back(info->current_token);
        info->reset();
        if (it.has_prev()) it.prev();
        transition(parser_state::START);
    }
};

void fsm::preprocessor_directive_state(parse_info* info) {
    block_iterator it = this->block->get_iterator();
    if (isalpha(info->current_char)) {
        info->current_string += info->current_char;
    }else if (info->current_char == '"' || info->current_char == '<' || info->current_char == '\'' || info->current_char == ' ' || info->current_char == '\t'){
        if (preprocessor_directive_token::directive_map.find(info->current_string) != preprocessor_directive_token::directive_map.end()) {
            info->current_token = new preprocessor_directive_token(info->current_string, it.current_ref());
            info->token_stream.push_back(info->current_token);
        } else {
            throw invalid_argument("Expected preprocessor directive : " + info->current_string + " at " + it.current_ref().toString());
        }
    }
};


parse_info::parse_info() {
    this->token_stream = vector<token*>();
    this->current_char = '\0';

    this->current_string = "";
    this->current_token = nullptr;
    this->string_has_underscore = false;
}

void parse_info::reset() {
    this->current_string = "";
    this->current_token = nullptr;
    this->string_has_underscore = false;
}