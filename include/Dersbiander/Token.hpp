#pragma once

#include "headers.hpp"
#include <string>

enum class TokenType : int {
    IDENTIFIER,
    CHAR,
    INTEGER,
    BOOLEAN,
    DOUBLE,
    STRING,
    OPERATOR,
    MINUS_OPERATOR,
    EQUAL_OPERATOR,
    OPERATION_EQUAL,
    BOOLEAN_OPERATOR,
    NOT_OPERATOR,
    LOGICAL_OPERATOR,
    UNARY_OPERATOR,
    DOT_OPERATOR,
    COMMA,
    COLON,
    OPEN_BRACKETS,
    CLOSED_BRACKETS,
    OPEN_SQUARE_BRACKETS,
    CLOSED_SQUARE_BRACKETS,
    OPEN_CURLY_BRACKETS,
    CLOSED_CURLY_BRACKETS,
    KEYWORD_MAIN,
    KEYWORD_VAR,
    KEYWORD_STRUCTURE,
    KEYWORD_FOR,
    KEYWORD_FUNC,
    KEYWORD_RETURN,
    COMMENT,
    EOFT,
    ERROR,
    UNKNOWN

};

template <> struct fmt::formatter<TokenType> : fmt::formatter<std::string_view> {  // NOLINT(*-include-cleaner)
    template <typename FormatContext> auto format(TokenType tokenType, FormatContext &ctx) {
        std::string_view name;
        switch(tokenType) {
            using enum TokenType;
        case IDENTIFIER:
            name = "IDENTIFIER";
            break;
        case CHAR:
            name = "CHAR";
            break;
        case BOOLEAN:
            name = "BOOLEAN";
            break;
        case INTEGER:
            name = "INTEGER";
            break;
        case DOUBLE:
            name = "DOUBLE";
            break;
        case STRING:
            name = "STRING";
            break;
        case OPERATOR:
            name = "OPERATOR";
            break;
        case MINUS_OPERATOR:
            name = "MINUS_OPERATOR";
            break;
        case EQUAL_OPERATOR:
            name = "EQUAL_OPERATOR";
            break;
        case OPERATION_EQUAL:
            name = "OPERATION_EQUAL";
            break;
        case BOOLEAN_OPERATOR:
            name = "BOOLEAN_OPERATOR";
            break;
        case NOT_OPERATOR:
            name = "NOT_OPERATOR";
            break;
        case LOGICAL_OPERATOR:
            name = "LOGICAL_OPERATOR";
            break;
        case UNARY_OPERATOR:
            name = "UNARY_OPERATOR";
            break;
        case DOT_OPERATOR:
            name = "DOT_OPERATOR";
            break;
        case COMMA:
            name = "COMMA";
            break;
        case COLON:
            name = "COLON";
            break;
        case OPEN_BRACKETS:
            name = "OPEN_BRACKETS";
            break;
        case CLOSED_BRACKETS:
            name = "CLOSED_BRACKETS";
            break;
        case OPEN_SQUARE_BRACKETS:
            name = "OPEN_SQUARE_BRACKETS";
            break;
        case CLOSED_SQUARE_BRACKETS:
            name = "CLOSED_SQUARE_BRACKETS";
            break;
        case OPEN_CURLY_BRACKETS:
            name = "OPEN_CURLY_BRACKETS";
            break;
        case CLOSED_CURLY_BRACKETS:
            name = "CLOSED_CURLY_BRACKETS";
            break;
        case KEYWORD_MAIN:
            name = "KEYWORD_MAIN";
            break;
        case KEYWORD_VAR:
            name = "KEYWORD_VAR";
            break;
        case KEYWORD_STRUCTURE:
            name = "KEYWORD_STRUCTURE";
            break;
        case KEYWORD_FOR:
            name = "KEYWORD_FOR";
            break;
        case KEYWORD_FUNC:
            name = "KEYWORD_FUNC";
            break;
        case KEYWORD_RETURN:
            name = "KEYWORD_RETURN";
            break;
        case COMMENT:
            name = "COMMENT";
            break;
        case TokenType::EOFT:
            name = "EOF";
            break;
        case ERROR:
            name = "ERROR";
            break;
        case TokenType::UNKNOWN:
            [[fallthrough]];
        default:
            name = "UNKNOWN";
            break;
        }
        return fmt::formatter<std::string_view>::format(name, ctx);
    }
};

static inline constexpr TokenType eofTokenType = TokenType::EOFT;

class Token {
public:
    Token() noexcept : _type(TokenType::UNKNOWN), _value{}, _line{}, _column{} {}  // NOLINT(*-redundant-member-init)
    Token(TokenType type, const std::string_view &value, std::size_t line, std::size_t column) noexcept
      : _type(type), _value(value), _line(line), _column(column) {}

    [[nodiscard]] inline TokenType getType() const noexcept { return _type; }
    [[nodiscard]] inline std::string getValue() const noexcept { return _value; }
    [[nodiscard]] inline std::size_t getLine() const noexcept { return _line; }
    [[nodiscard]] inline std::size_t getColumn() const noexcept { return _column; }
    [[nodiscard]] std::string to_string() const;  // NOLINT(*-include-cleaner)
    inline void setType(TokenType type) noexcept { _type = type; }
    inline void setValue(const std::string &value) noexcept { _value = value; }
    void setLine(std::size_t line) noexcept { _line = line; }
    void setColumn(std::size_t column) noexcept { _column = column; }
    [[nodiscard]] inline bool isNumber() const noexcept {
        return this->_type == TokenType::INTEGER || this->_type == TokenType::DOUBLE;
    }
    auto operator<=>(const Token &) const = default;

private:
    TokenType _type;
    std::string _value;
    std::size_t _line;
    std::size_t _column;
};

template <> struct fmt::formatter<Token> : fmt::formatter<std::string_view> {  // NOLINT(*-include-cleaner)
    template <typename FormatContext> auto format(const Token &val, FormatContext &ctx) {
        return fmt::formatter<std::string_view>::format(val.to_string(), ctx);
    }
};
