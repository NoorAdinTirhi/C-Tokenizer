#include "tokens.h"
using json = nlohmann::json;

using namespace std;

unordered_map<string, C_keyword_control_flow> keyword_token::control_flow_keyword_map;
unordered_map<string, C_keyword_basic_type> keyword_token::basic_type_keyword_map;
unordered_map<string, C_keyword_qualifier_storage> keyword_token::qualifier_keyword_map;
unordered_map<string, C_keyword_user_defined> keyword_token::user_defined_keyword_map;
unordered_map<string, C_keyword_builtin> keyword_token::builtin_keyword_map;
unordered_map<string, C_keyword_extension> keyword_token::extension_keyword_map;
unordered_map<string, C_operator> operator_token::operator_map;

token::token(string value, source_ref ref)
    : value(value), ref(ref)
{
}

keyword_type_t keyword_token::lookup_keyword(const string& value, source_ref ref)
{
    auto it_control = control_flow_keyword_map.find(value);
    if (it_control != control_flow_keyword_map.end()) {
        return it_control->second;
    }

    auto it_basic = basic_type_keyword_map.find(value);
    if (it_basic != basic_type_keyword_map.end()) {
        return it_basic->second;
    }

    auto it_qualifier = qualifier_keyword_map.find(value);
    if (it_qualifier != qualifier_keyword_map.end()) {
        return it_qualifier->second;
    }

    auto it_user = user_defined_keyword_map.find(value);
    if (it_user != user_defined_keyword_map.end()) {
        return it_user->second;
    }

    auto it_builtin = builtin_keyword_map.find(value);
    if (it_builtin != builtin_keyword_map.end()) {
        return it_builtin->second;
    }

    auto it_extension = extension_keyword_map.find(value);
    if (it_extension != extension_keyword_map.end()) {
        return it_extension->second;
    }

    throw invalid_argument("Expected keyword at " + ref.toString() + " got " + value + " instead");
}

keyword_token::keyword_token(string value, source_ref ref)
    : token(value, ref), keyword_type(lookup_keyword(value, ref))
{
}

operator_token::operator_token(string value, source_ref ref)
    : token(value, ref)
{
    if (operator_map.find(value) == operator_map.end())
    {
        throw invalid_argument("Expected operator : " + value + " at " + ref.toString());
    }
}

literal_token::literal_token(string value, source_ref ref, C_literal_type literal_type)
    : token(value, ref), literal_type(literal_type)
{
}



void token::to_json(json &j)
{
    j["type"] = "token";
    j = json{
        {"value", value},
    };
    json ref_json = json{};
    ref.to_json(ref_json);
    j["ref"] = ref_json;
}

void keyword_token::to_json(json &j) {    
    token::to_json(j);
    j["type"] = "keyword_token";
    j["keyword_category"] = visit([](auto&& arg) {
        using T = decay_t<decltype(arg)>;
        if constexpr (is_same_v<T, C_keyword_control_flow>) return string("control_flow");
        if constexpr (is_same_v<T, C_keyword_basic_type>) return string("basic_type");
        if constexpr (is_same_v<T, C_keyword_qualifier_storage>) return string("qualifier_storage");
        if constexpr (is_same_v<T, C_keyword_user_defined>) return string("user_defined");
        if constexpr (is_same_v<T, C_keyword_builtin>) return string("builtin");
        if constexpr (is_same_v<T, C_keyword_extension>) return string("extension");
    }, keyword_type);
    j["keyword_type"] = visit([](auto&& arg) {
        return static_cast<int>(arg);
    }, keyword_type);
}

void operator_token::to_json(json &j) {
    token::to_json(j);
    j["type"] = "operator_token";
}

void literal_token::to_json(json &j) {
    token::to_json(j);
    j["type"] = "literal_token";
    j["literal_type"] = static_cast<int>(literal_type);
}

void keyword_token::init_keyword_maps()
{
    control_flow_keyword_map = {
        {"if", C_keyword_control_flow::IF},
        {"else", C_keyword_control_flow::ELSE},
        {"switch", C_keyword_control_flow::SWITCH},
        {"case", C_keyword_control_flow::CASE},
        {"default", C_keyword_control_flow::DEFAULT},
        {"for", C_keyword_control_flow::FOR},
        {"while", C_keyword_control_flow::WHILE},
        {"do", C_keyword_control_flow::DO},
        {"break", C_keyword_control_flow::BREAK},
        {"continue", C_keyword_control_flow::CONTINUE},
        {"return", C_keyword_control_flow::RETURN},
        {"goto", C_keyword_control_flow::GOTO}
    };

    basic_type_keyword_map = {
        {"int", C_keyword_basic_type::INT},
        {"char", C_keyword_basic_type::CHAR},
        {"float", C_keyword_basic_type::FLOAT},
        {"double", C_keyword_basic_type::DOUBLE},
        {"void", C_keyword_basic_type::VOID},
        {"short", C_keyword_basic_type::SHORT},
        {"long", C_keyword_basic_type::LONG},
        {"signed", C_keyword_basic_type::SIGNED},
        {"unsigned", C_keyword_basic_type::UNSIGNED},
        {"bool", C_keyword_basic_type::BOOL},           // C23
        {"complex", C_keyword_basic_type::COMPLEX},     // C99
        {"imaginary", C_keyword_basic_type::IMAGINARY} // C99
    };

    qualifier_keyword_map = {
        {"const", C_keyword_qualifier_storage::CONST},
        {"volatile", C_keyword_qualifier_storage::VOLATILE},
        {"static", C_keyword_qualifier_storage::STATIC},
        {"extern", C_keyword_qualifier_storage::EXTERN},
        {"auto", C_keyword_qualifier_storage::AUTO},
        {"register", C_keyword_qualifier_storage::REGISTER},
        {"thread_local", C_keyword_qualifier_storage::THREAD_LOCAL} // C11
    };

    user_defined_keyword_map = {
        {"struct", C_keyword_user_defined::STRUCT},
        {"union", C_keyword_user_defined::UNION},
        {"enum", C_keyword_user_defined::ENUM},
        {"typedef", C_keyword_user_defined::TYPEDEF}
    };

    builtin_keyword_map = {
        {"sizeof", C_keyword_builtin::SIZEOF}
    };

    extension_keyword_map = {
        {"atomic", C_keyword_extension::ATOMIC},               // C11
        {"generic", C_keyword_extension::GENERIC},             // C11
        {"static_assert", C_keyword_extension::STATIC_ASSERT}, // C11
        {"noreturn", C_keyword_extension::NORETURN},           // C11
        {"constexpr", C_keyword_extension::CONSTEXPR},         // C23
        {"typeof", C_keyword_extension::TYPEOF},               // C23
        {"typeof_unqual", C_keyword_extension::TYPEOF_UNQUAL}  // C23
    };
};

void operator_token::init_operator_map()
{
    operator_map = {
        // --- C Operators ---
        {"+", C_operator::PLUS},
        {"-", C_operator::MINUS},
        {"*", C_operator::MULTIPLY},
        {"/", C_operator::DIVIDE},
        {"%", C_operator::MODULO},
        {"++", C_operator::INCREMENT},
        {"--", C_operator::DECREMENT},
        {"==", C_operator::EQUALS},
        {"!=", C_operator::NOT_EQUALS},
        {">", C_operator::GREATER_THAN},
        {"<", C_operator::LESS_THAN},
        {">=", C_operator::GREATER_EQUAL},
        {"<=", C_operator::LESS_EQUAL},
        {"&&", C_operator::LOGICAL_AND},
        {"||", C_operator::LOGICAL_OR},
        {"!", C_operator::LOGICAL_NOT},
        {"&", C_operator::BITWISE_AND},
        {"|", C_operator::BITWISE_OR},
        {"^", C_operator::BITWISE_XOR},
        {"~", C_operator::BITWISE_NOT},
        {"<<", C_operator::LEFT_SHIFT},
        {">>", C_operator::RIGHT_SHIFT},
        {"=", C_operator::ASSIGN},
        {"+=", C_operator::PLUS_ASSIGN},
        {"-=", C_operator::MINUS_ASSIGN},
        {"*=", C_operator::MULTIPLY_ASSIGN},
        {"/=", C_operator::DIVIDE_ASSIGN},
        {"%=", C_operator::MODULO_ASSIGN},
        {"&=", C_operator::BITWISE_AND_ASSIGN},
        {"|=", C_operator::BITWISE_OR_ASSIGN},
        {"^=", C_operator::BITWISE_XOR_ASSIGN},
        {"<<=", C_operator::LEFT_SHIFT_ASSIGN},
        {">>=", C_operator::RIGHT_SHIFT_ASSIGN},
        {".", C_operator::MEMBER_ACCESS},
        {"->", C_operator::POINTER_ACCESS},
        {"?", C_operator::TERNARY_CONDITIONAL},
        {":", C_operator::COLON},
        {",", C_operator::COMMA},
        {";", C_operator::SEMICOLON}};
};