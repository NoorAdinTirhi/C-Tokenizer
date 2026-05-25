#include <cstdint>
/**
 * @brief Represents C keywords grouped by category.
 *
 * Each enum class captures a keyword subset so tokenization can maintain
 * category-specific maps and metadata without splitting the tokenizer class.
 */
enum class C_keyword_control_flow : uint32_t {
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
    GOTO
};

enum class C_keyword_basic_type : uint32_t {
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
    IMAGINARY    // C99
};

enum class C_keyword_qualifier_storage : uint32_t {
    CONST,
    VOLATILE,
    STATIC,
    EXTERN,
    AUTO,
    REGISTER,
    THREAD_LOCAL // C11
};

enum class C_keyword_user_defined : uint32_t {
    STRUCT,
    UNION,
    ENUM,
    TYPEDEF
};

enum class C_keyword_builtin : uint32_t {
    SIZEOF
};

// C99 / C11 / C23 extension keywords, plus special built-ins.
enum class C_keyword_extension : uint32_t {
    ATOMIC,          // C11
    GENERIC,         // C11
    STATIC_ASSERT,   // C11
    NORETURN,        // C11
    CONSTEXPR,       // C23
    TYPEOF,          // C23
    TYPEOF_UNQUAL    // C23
};

/*
 * C Operators
       ++ --	            Suffix/postfix increment and decrement	Left-to-right
      ()	            Function call
1     []	            Array subscripting
      .	                Structure and union member access
      ->	            Structure and union member access through pointer
      (type){list}	    Compound literal(C99)
      ++ --	            Prefix increment and decrement[note 1]	Right-to-left
      + -	            Unary plus and minus
      ! ~	            Logical NOT and bitwise NOT
2    (type)	        Cast
      *	                Indirection (dereference)
      &	                Address-of
      sizeof	        Size-of[note 2]
      _Alignof	        Alignment requirement(C11)
3     * / %	            Multiplication, division, and remainder	Left-to-right
4     + -	            Addition and subtraction
5     << >>	            Bitwise left shift and right shift
6     < <=	            For relational operators < and ≤ respectively
      > >=	            For relational operators > and ≥ respectively
7     == !=	            For relational = and ≠ respectively
8     &	                Bitwise AND
9     ^	                Bitwise XOR (exclusive or)
10    |	                Bitwise OR (inclusive or)
11    &&	            Logical AND
12    ||	            Logical OR
13    ?:	            Ternary conditional[note 3]	Right-to-left
      =	                Simple assignment
      += -=	            Assignment by sum and difference
14    *= /= %=	        Assignment by product, quotient, and remainder
      <<= >>=	        Assignment by bitwise left shift and right shift
      &= ^= |=	        Assignment by bitwise AND, XOR, and OR
15    ,	                Comma	Left-to-right
 */

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