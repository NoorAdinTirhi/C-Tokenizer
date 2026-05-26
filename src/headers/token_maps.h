#pragma once
#include "tokens.h"

unordered_map<string, C_keyword_control_flow> keyword_token::control_flow_keyword_map;
unordered_map<string, C_keyword_basic_type> keyword_token::basic_type_keyword_map;
unordered_map<string, C_keyword_qualifier_storage> keyword_token::qualifier_keyword_map;
unordered_map<string, C_keyword_user_defined> keyword_token::user_defined_keyword_map;
unordered_map<string, C_keyword_builtin> keyword_token::builtin_keyword_map;
unordered_map<string, C_keyword_extension> keyword_token::extension_keyword_map;
unordered_map<string, C_operator> operator_token::operator_map;
unordered_map<string, string> preprocessor_directive_token::directive_map;
