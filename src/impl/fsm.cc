#include "fsm.h"
#include "fsm_char_sets.h"

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
    block_iterator* it = this->block->get_iterator_ptr();
    parse_info info;

    while (it->has_next() || !info.last ){
        if (it->has_next()){
            info.current_char =  it->next();
        }else {
            info.last = true;
        }
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
            case parser_state::IN_STRING_LITERAL:
                string_literal_state(&info);
                break;
            case parser_state::IN_STRING_ESCAPE_SEQUENCE:
                // string_escape_sequence_state(&info);
                break;
            case parser_state::IN_NUMERIC_LITERAL:
                numeric_literal_state(&info);   
                break;
            case parser_state::IN_PUNCTUATOR:
                punctuator_state(&info);
                break;
            case parser_state::IN_OPERATOR:
                operator_state(&info);
                break;

            default:
                break;
        }        
    }
    return info.token_stream;
}

void fsm::start_state(parse_info* info) {
    if (fsm::whitespace_chars.contains(info->current_char)) {
        transition(parser_state::IN_WHITESPACE);
    } else if (isalpha(info->current_char) || info->current_char == '_') {
        info->current_string += info->current_char;
        transition(parser_state::IN_IDENTIFIER);
    } else if (info->current_char == '#') {
        transition(parser_state::IN_PREPROCESSOR_DIRECTIVE);
    }else {
        throw invalid_argument("Unexpected character : " + string(1, info->current_char) + " at " + this->block->get_iterator().current_ref().toString());
    }
};

void fsm::whitespace_state(parse_info* info) {
    if (fsm::whitespace_chars.contains(info->current_char)) {
        transition(parser_state::IN_WHITESPACE);

    } else if (info->current_char == '#') {
        transition(parser_state::IN_PREPROCESSOR_DIRECTIVE);
    } else if (isalpha(info->current_char) || info->current_char == '_') {
        info->current_string += info->current_char;
        transition(parser_state::IN_IDENTIFIER);

    }  else if (fsm::punctuation_chars.contains(info->current_char)) {
        info->current_string += info->current_char;
        transition(parser_state::IN_PUNCTUATOR);

    } else  if (info->current_char == '"' || info->current_char == '<') {
        //change this, if before is preprocessor directive then this is a string literal, otherwise this is an operator
        if (info->current_char == '<'){
            if (typeid(*info->token_stream.back()) == typeid(preprocessor_directive_token) && info->token_stream.back()->value == "include") {
                transition(parser_state::IN_STRING_LITERAL);
                info->string_literal_for_lib = true;
            }else {
                info->current_string += info->current_char;
                transition(parser_state::IN_OPERATOR);
            }
        }else {
            transition(parser_state::IN_STRING_LITERAL);
        }

    } else if (info->current_char == '\'') {
        transition(parser_state::IN_CHAR_LITERAL);

    } else if (isdigit(info->current_char)){
        info->current_string += info->current_char;
        transition(parser_state::IN_NUMERIC_LITERAL);

    } else if (fsm::operator_chars.contains(info->current_char)) {
        info->current_string += info->current_char;
        transition(parser_state::IN_OPERATOR);

    } else {
        throw invalid_argument("Unexpected character : " + string(1, info->current_char) + " at " + this->block->get_iterator().current_ref().toString());
    }
    //support the other states
};

void fsm::identifier_state(parse_info* info) {
    block_iterator* it = this->block->get_iterator_ptr();
    if (isalnum(info->current_char) || info->current_char == '_') {
        info->current_string += info->current_char;
    } else {
        if (keyword_token::is_keyword(info->current_string)) {
            info->current_token = new keyword_token(info->current_string, it->current_ref());
        } else {
            info->current_token = new identifier_token(info->current_string, it->current_ref());
        }
        info->token_stream.push_back(info->current_token);
        
        if (it->has_prev()) {
            it->prev();
        } else{
            throw invalid_argument("Unexpected end of input while parsing identifier at " + it->current_ref().toString());
        }
        info->reset();
        transition(parser_state::IN_WHITESPACE);
    }
};

void fsm::preprocessor_directive_state(parse_info* info) {
    block_iterator * it = this->block->get_iterator_ptr();
    if (isalpha(info->current_char)) {
        info->current_string += info->current_char;
    }else if (info->current_char == '"' || info->current_char == '<' || info->current_char == '\'' || info->current_char == ' ' || info->current_char == '\t'){
        if (preprocessor_directive_token::directive_map.find(info->current_string) != preprocessor_directive_token::directive_map.end()) {
            info->current_token = new preprocessor_directive_token(info->current_string, it->current_ref());
            info->reset();
            info->token_stream.push_back(info->current_token);
        } else {
            throw invalid_argument("Expected preprocessor directive : " + info->current_string + " at " + it->current_ref().toString());
        }
        transition(parser_state::IN_WHITESPACE);
    }
};

void fsm::string_literal_state(parse_info* info) {
    if (!info->string_literal_for_lib && info->current_char == '\\') {//TODO : handle this
        transition(parser_state::IN_STRING_ESCAPE_SEQUENCE);
    }else if (info->current_char == '"'){
        if (info->string_literal_for_lib) {
            throw invalid_argument("Unexpected character : " + string(1, info->current_char) + " at " + this->block->get_iterator().current_ref().toString() + " expected '>' for library string literal");
        } else {
            info->current_token = new literal_token(info->current_string, this->block->get_iterator().current_ref(), C_literal_type::STRING_LITERAL);
            info->token_stream.push_back(info->current_token);
            info->reset();
            transition(parser_state::IN_WHITESPACE);
        }
    }else if (info->current_char == '>'){
        if (info->string_literal_for_lib) {
            info->current_token = new literal_token(info->current_string, this->block->get_iterator().current_ref(), C_literal_type::STRING_LITERAL);
            info->token_stream.push_back(info->current_token);
            info->reset();
            transition(parser_state::IN_WHITESPACE);
        }else {
            info->current_string += info->current_char;
        }
    }else {
        info->current_string += info->current_char;
    }
}

void fsm::numeric_literal_state(parse_info* info) {
    //only support integers for now
    if (isdigit(info->current_char)){
        info->current_string += info->current_char;
    }else{
        info->current_token = new literal_token(info->current_string, this->block->get_iterator().current_ref(), C_literal_type::INTEGER_LITERAL);
        info->token_stream.push_back(info->current_token);
        if (this->block->get_iterator().has_prev()) this->block->get_iterator_ptr()->prev(); else throw invalid_argument("Unexpected end of input while parsing numeric literal at " + this->block->get_iterator().current_ref().toString());
        info->reset();
        transition(parser_state::IN_WHITESPACE);
    }
}

void fsm::operator_state(parse_info* info) {
    if (fsm::operator_chars.contains(info->current_char)) {
        info->current_string += info->current_char;
    }else {
        if (operator_token::operator_map.find(info->current_string) != operator_token::operator_map.end()) {
            info->current_token = new operator_token(info->current_string, this->block->get_iterator().current_ref());
            info->token_stream.push_back(info->current_token);
        } else {
            throw invalid_argument("Expected operator : " + info->current_string + " at " + this->block->get_iterator().current_ref().toString());
        }
        info->reset();
        if (this->block->get_iterator().has_prev()) this->block->get_iterator_ptr()->prev(); else throw invalid_argument("Unexpected end of input while parsing operator at " + this->block->get_iterator().current_ref().toString());
        transition(parser_state::IN_WHITESPACE);
    }
}

void fsm::punctuator_state(parse_info* info) {
    info->current_token = new punctuator_token(info->current_string, this->block->get_iterator().current_ref());
    info->token_stream.push_back(info->current_token);
    info->reset();
    //current character is not the punctuator, its the one next to it, therefore we need to step back before returning to whitespace
    if (this->block->get_iterator().has_prev()) this->block->get_iterator_ptr()->prev(); else throw invalid_argument("Unexpected end of input while parsing operator at " + this->block->get_iterator().current_ref().toString());
    transition(parser_state::IN_WHITESPACE);
}

void fsm::init_sets(){
    whitespace_chars = {' ', '\t', '\n', '\r', '\000'};
    operator_chars = {'+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^', '~', '?', ':', '.', ','};
    punctuation_chars = {';', '(', ')', '{', '}', '[', ']'};
}


parse_info::parse_info() {
    this->token_stream = vector<token*>();
    this->current_char = '\0';

    this->current_string = "";
    this->current_token = nullptr;
    this->string_has_underscore = false;
    this->string_literal_for_lib = false;
    this->last = false;
}

void parse_info::reset() {
    this->current_string = "";
    this->string_has_underscore = false;
    this->string_literal_for_lib = false;
}

string parse_info::to_string() const {
    string result = "Current char: " + string(1, this->current_char) + "\n";
    result += "Current string: " + this->current_string + "\n";
    result += "Current token: " + (this->current_token ? this->current_token->value : "null") + "\n";
    result += "String has underscore: " + string(this->string_has_underscore ? "true" : "false") + "\n";
    result += "String literal for lib: " + string(this->string_literal_for_lib ? "true" : "false") + "\n";
    return result;
}