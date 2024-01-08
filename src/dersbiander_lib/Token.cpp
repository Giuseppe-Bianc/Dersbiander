#include "Dersbiander/Token.hpp"
std::string Token::to_string() const {
    if(_type == eofTokenType) { return FORMAT("type: {}, line {}, column {}", _type, _line, _column); }
    return FORMAT("type: {}, value: '{}', line {}, column {}", _type, _value, _line, _column);
}
