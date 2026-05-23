#include <string>
#include <unordered_map>

#include "token_enums.h"
#include "source_ref.h"


class token {
    string value;
    source_ref ref;
public:
    token (string value, source_ref ref);
};

class identifier_token : public token {

};

class keyword_token : public token {
    static unordered_map<string, C_keywords> keyword_map;
    C_keywords keyword_type;

    static void init_keyword_map();

public:
    keyword_token(string value, source_ref ref);
    
};

class operator_token : public token {
    static unordered_map<string, C_operator> operator_map;
    C_operator operator_type;

    static void init_operator_map();

public:
    operator_token(string value, source_ref ref);
};

class literal_token : public token {
    C_literal_type literal_type;

public:
    literal_token(string value, source_ref ref);
};




