#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

#include "token_enums.h"
#include "source_ref.h"


struct token {
    string value;
    source_ref ref;

    
    token (string value, source_ref ref);
    virtual void to_json(json& j);
};

struct identifier_token : public token {
    
    identifier_token(string value, source_ref ref);
};

using keyword_type_t = variant<
    C_keyword_control_flow,
    C_keyword_basic_type,
    C_keyword_qualifier_storage,
    C_keyword_user_defined,
    C_keyword_builtin,
    C_keyword_extension>;

struct keyword_token : public token {
    static unordered_map<string, C_keyword_control_flow> control_flow_keyword_map;
    static unordered_map<string, C_keyword_basic_type> basic_type_keyword_map;
    static unordered_map<string, C_keyword_qualifier_storage> qualifier_keyword_map;
    static unordered_map<string, C_keyword_user_defined> user_defined_keyword_map;
    static unordered_map<string, C_keyword_builtin> builtin_keyword_map;
    static unordered_map<string, C_keyword_extension> extension_keyword_map;

    static keyword_type_t lookup_keyword(const string& value, source_ref ref);

    keyword_type_t keyword_type;

    
    static void init_keyword_maps();
    keyword_token(string value, source_ref ref);
    void to_json(json& j) override;
};

struct operator_token : public token {
    static unordered_map<string, C_operator> operator_map;
    C_operator operator_type;

    
    static void init_operator_map();
    operator_token(string value, source_ref ref);
    void to_json(json& j) override;
};

struct literal_token : public token {
    C_literal_type literal_type;

    
    literal_token(string value, source_ref ref, C_literal_type type);
    void to_json(json& j) override;
};

struct preprocessor_directive_token : public token {
    
    static unordered_map<string, string> directive_map;
    preprocessor_directive_token(string value, source_ref ref);
    static void init_directive_map();
    void to_json(json& j) override;
};




