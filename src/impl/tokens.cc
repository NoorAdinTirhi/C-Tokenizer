#include <stdexcept>
#include "tokens.h"

using namespace std;

unordered_map<string, C_keywords> keyword_token::keyword_map;
unordered_map<string, C_operator> operator_token::operator_map;

token::token(string value, source_ref ref)
    : value(value), ref(ref)
{
}

keyword_token::keyword_token(string value, source_ref ref)
    : token(value, ref)
{
    if (keyword_map.find(value) == keyword_map.end()) {
        
        // throw invalid_argument("Expected keyword at " + ref.toString() + "got " + value + " instead");
    }
}

operator_token::operator_token(string value, source_ref ref)
    : token(value, ref)
{
    if (operator_map.find(value) == operator_map.end()) {
        // throw invalid_argument("Expected operator : " + value + " at " + ref.toString());
    }
}





void keyword_token::init_keyword_map() {
    keyword_map = {
        {"if", C_keywords::IF},
        {"else", C_keywords::ELSE},
        {"switch", C_keywords::SWITCH},
        {"case", C_keywords::CASE},
        {"default", C_keywords::DEFAULT},
        {"for", C_keywords::FOR},
        {"while", C_keywords::WHILE},
        {"do", C_keywords::DO},
        {"break", C_keywords::BREAK},
        {"continue", C_keywords::CONTINUE},
        {"return", C_keywords::RETURN},
        {"goto", C_keywords::GOTO},

        {"int", C_keywords::INT},
        {"char", C_keywords::CHAR},
        {"float", C_keywords::FLOAT},
        {"double", C_keywords::DOUBLE},
        {"void", C_keywords::VOID},
        {"short", C_keywords::SHORT},
        {"long", C_keywords::LONG},
        {"signed", C_keywords::SIGNED},
        {"unsigned", C_keywords::UNSIGNED},
        {"bool", C_keywords::BOOL}, // C23
        {"complex", C_keywords::COMPLEX}, // C99
        {"imaginary", C_keywords::IMAGINARY}, // C99

        {"const", C_keywords::CONST},
        {"volatile", C_keywords::VOLATILE},
        {"static", C_keywords::STATIC},
        {"extern", C_keywords::EXTERN},
        {"auto", C_keywords::AUTO},
        {"register", C_keywords::REGISTER},
        {"thread_local", C_keywords::THREAD_LOCAL}, // C11

        {"struct", C_keywords::STRUCT},
        {"union", C_keywords::UNION},
        {"enum", C_keywords::ENUM},
        {"typedef", C_keywords::TYPEDEF},

        {"sizeof", C_keywords::SIZEOF},

        // --- C99/C11/C23 Extensions & Special Keywords ---
        {"atomic", C_keywords::ATOMIC}, // C11
        {"generic", C_keywords::GENERIC}, // C11
        {"static_assert", C_keywords::STATIC_ASSERT}, // C11
        {"noreturn", C_keywords::NORETURN}, // C11
        {"constexpr", C_keywords::CONSTEXPR}, // C23
        {"typeof", C_keywords::TYPEOF}, // C23
        {"typeof_unqual", C_keywords::TYPEOF_UNQUAL} //C23
    };
};

void operator_token::init_operator_map() {
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
        {";", C_operator::SEMICOLON}
    };
};