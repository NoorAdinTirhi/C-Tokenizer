#include <cstdint>
/**
 * @brief Represents the set of all reserved keywords in the C programming language.
 * This enum is intended to be used by the Tokenizer to identify specific 
 * keyword tokens during the lexical analysis phase.
 */
enum class C_keywords : uint32_t {
    // --- Control Flow ---
    IF,
    ELSE,
    SWITCH,
    CASE,
    DEFAULT,
    FOR,
    WHILE,
    DO,
    BREAK,
    CONTINUE,
    RETURN,
    GOTO,

    // --- Basic Types ---
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    VOID,
    SHORT,
    LONG,
    SIGNED,
    UNSIGNED,
    BOOL,        // C23
    COMPLEX,     // C99
    IMAGINARY,   // C99

    // --- Qualifiers & Storage Classes ---
    CONST,
    VOLATILE,
    STATIC,
    EXTERN,
    AUTO,
    REGISTER,
    THREAD_LOCAL, // C11

    // --- User-Defined Types ---
    STRUCT,
    UNION,
    ENUM,
    TYPEDEF,

    // --- Built-in Operators/Keywords ---
    SIZEOF,

    // --- C99/C11/C23 Extensions & Special Keywords ---
    ATOMIC,          // C11
    GENERIC,         // C11
    STATIC_ASSERT,   // C11
    NORETURN,        // C11
    CONSTEXPR,       // C23
    TYPEOF,          // C23
    TYPEOF_UNQUAL    // C23
};

//organize this by order of precedence
enum class C_operator : uint32_t {
    LEFT_PAREN,     // (
    RIGHT_PAREN,    // )
    LEFT_BRACKET,   // [
    RIGHT_BRACKET,  // ]
    LEFT_BRACE,     // {
    RIGHT_BRACE,    // }
    MEMBER_ACCESS,  // .
    POINTER_ACCESS, // ->
    INCREMENT,      // ++
    DECREMENT,      // --

    MULTIPLY,       // *
    DIVIDE,         // /
    MODULO,         // %

    PLUS,           // +
    MINUS,          // -

    LEFT_SHIFT,     // <<
    RIGHT_SHIFT,    // >>

    LESS_THAN,           // <
    GREATER_THAN,        // >
    LESS_EQUAL,     // <=
    GREATER_EQUAL,  // >=

    EQUALS,          // ==
    NOT_EQUALS,      // !=

    BITWISE_AND,    // &
    BITWISE_XOR,    // ^
    BITWISE_OR,     // |

    LOGICAL_AND,    // &&
    LOGICAL_OR,     // ||

    LOGICAL_NOT,    // !
    BITWISE_NOT,    // ~

    TERNARY_CONDITIONAL, // ?:
    COLON,          // :

    ASSIGN,         // =
    PLUS_ASSIGN,    // +=
    MINUS_ASSIGN,   // -=
    MULTIPLY_ASSIGN,// *=
    DIVIDE_ASSIGN,  // /=
    MODULO_ASSIGN,  // %=
    BITWISE_AND_ASSIGN, // &=
    BITWISE_OR_ASSIGN,  // |=
    BITWISE_XOR_ASSIGN, // ^=
    LEFT_SHIFT_ASSIGN,  // <<=
    RIGHT_SHIFT_ASSIGN, // >>=

    COMMA,          // ,
    SEMICOLON       // ;
};

enum class C_literal_type : uint32_t {
    INTEGER_LITERAL,
    FLOATING_POINT_LITERAL,
    CHARACTER_LITERAL,
    STRING_LITERAL
};