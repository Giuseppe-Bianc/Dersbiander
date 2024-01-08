#include "Dersbiander/Instruction.hpp"

#define ONLY_TOKEN_TYPE

DISABLE_WARNINGS_PUSH(26461 26821)

Instruction::Instruction() noexcept
  : tokens({}), instructionTypes({InstructionType::BLANK}),
    allowedTokens({TokenType::KEYWORD_MAIN, TokenType::KEYWORD_VAR, TokenType::KEYWORD_STRUCTURE, TokenType::KEYWORD_FOR,
                   TokenType::KEYWORD_FUNC, TokenType::KEYWORD_RETURN, TokenType::IDENTIFIER, TokenType::OPEN_CURLY_BRACKETS,
                   TokenType::CLOSED_CURLY_BRACKETS, eofTokenType}), booleanOperatorPresent({false}) {
    previousTokens.reserve(tokens.size());
}

[[nodiscard]] std::string Instruction::unexpected(const Token &token) const {
    std::string value;

    if(token.getType() != eofTokenType) {
        value = token.getValue();
    } else {
        value = "EOFT";
    }
    return FORMAT("Unexpected token: {} line {} column {}", value, token.getLine(), token.getColumn());
}

[[nodiscard]] std::vector<std::string> Instruction::typeToString() const noexcept {
    std::vector<std::string> result;
    result.reserve(this->instructionTypes.size());

    // NOLINTNEXTLINE
    for(const InstructionType &i : this->instructionTypes) { result.emplace_back(FORMAT("{}", i)); }
    return result;
}

[[nodiscard]] std::pair<bool, std::string> Instruction::checkToken(const Token &token) {
#ifdef ONLY_TOKEN_TYPE
    std::string msg = FORMAT("{}", token.getType());
#else
    std::string msg = token.toString();
#endif  // ONLY_TOKEN_TYPE
    if(std::ranges::find(this->allowedTokens, token.getType()) == this->allowedTokens.end()) [[unlikely]] { return {false, msg}; }
    switch(token.getType()) {
        using enum TokenType;
    case IDENTIFIER:
        [[fallthrough]];
    case UNARY_OPERATOR:
        this->checkIdentifier(token.getType());
        break;
    // NOLINTNEXTLINE
    case INTEGER:
    case DOUBLE:
    case CHAR:
    case STRING:
        [[fallthrough]];
    case BOOLEAN:
        this->checkNumber(token.getType());
        break;
    case OPERATOR:
        this->checkOperator();
        break;
    case MINUS_OPERATOR:
        this->checkMinusOperator();
        break;
    case EQUAL_OPERATOR:
        [[fallthrough]];
    case OPERATION_EQUAL:
        this->checkEqualOperator();
        break;
    case BOOLEAN_OPERATOR:
    case NOT_OPERATOR:
        [[fallthrough]];
    case LOGICAL_OPERATOR:
        this->checkBooleanAndLogicalOperator(token.getType());
        break;
    case DOT_OPERATOR:
        this->allowedTokens = {IDENTIFIER};
        break;
    case COMMA:
        this->checkComma();
        break;
    case COLON:
        this->checkColon();
        break;
    case OPEN_BRACKETS:
        [[fallthrough]];
    case OPEN_SQUARE_BRACKETS:
        this->checkOpenBrackets(token.getType());
        break;
    case CLOSED_BRACKETS:
        [[fallthrough]];
    case CLOSED_SQUARE_BRACKETS:
        this->checkClosedBrackets(token.getType());
        break;
    case OPEN_CURLY_BRACKETS:
        this->checkOpenCurlyBrackets();
        break;
    case CLOSED_CURLY_BRACKETS:
        this->checkClosedCurlyBracktes();
        break;
    case KEYWORD_MAIN:
        this->checkKeywordMain();
        break;
    case KEYWORD_VAR:
        this->checkKeywordVar();
        break;
    case KEYWORD_STRUCTURE:
        this->checkKeywordStructure();
        break;
    case KEYWORD_FOR:
        this->checkKeywordFor();
        break;
    case KEYWORD_FUNC:
        this->checkKeywordFunc();
        break;
    case KEYWORD_RETURN:
        this->checkKeywordReturn();
        break;
    case eofTokenType:
    case ERROR:
    case UNKNOWN:
        [[fallthrough]];
    case COMMENT:
        break;
    }
    this->previousTokens.emplace_back(token);
    return {true, msg};
}

void Instruction::emplaceCommaEoft() noexcept {
    this->allowedTokens.emplace_back(TokenType::COMMA);
    this->allowedTokens.emplace_back(eofTokenType);
}

void Instruction::emplaceExpressionTokens() {
    using enum InstructionType;
    using enum TokenType;
    this->emplaceBooleanOperator();
    if(this->emplaceTokenType(SQUARE_EXPRESSION, CLOSED_SQUARE_BRACKETS)) { return; }
    if(this->emplaceTokenType(EXPRESSION, CLOSED_BRACKETS)) { return; }
    if(this->lastInstructionTypeIs(PARAMETER_EXPRESSION)) {
        this->allowedTokens.emplace_back(CLOSED_BRACKETS);
        this->allowedTokens.emplace_back(COMMA);
        return;
    }
    if(lastInstructionTypeIs(ARRAY_INIZIALIZATION)) {
        this->allowedTokens.emplace_back(CLOSED_SQUARE_BRACKETS);
        this->allowedTokens.emplace_back(COMMA);
        return;
    }
    if(this->emplaceForTokens()) { return; }
    this->emplaceCommaEoft();
}

bool Instruction::isExpression() noexcept {
    using enum InstructionType;
    return lastInstructionTypeIs(PARAMETER_EXPRESSION) || lastInstructionTypeIs(ASSIGNATION) ||
           lastInstructionTypeIs(INITIALIZATION) || lastInstructionTypeIs(ARRAY_INIZIALIZATION) ||
           lastInstructionTypeIs(EXPRESSION) || lastInstructionTypeIs(SQUARE_EXPRESSION) ||
           lastInstructionTypeIs(RETURN_EXPRESSION) || this->isForExpression();
}

bool Instruction::isForExpression() noexcept {
    using enum InstructionType;
    return lastInstructionTypeIs(FOR_INITIALIZATION) || lastInstructionTypeIs(FOR_CONDITION) || lastInstructionTypeIs(FOR_STEP);
}

void Instruction::checkIdentifier(const TokenType &type) noexcept {
    using enum TokenType;
    using enum InstructionType;
    if(this->isExpression()) {
        this->allowedTokens = {OPERATOR, MINUS_OPERATOR, LOGICAL_OPERATOR, DOT_OPERATOR, OPEN_BRACKETS, OPEN_SQUARE_BRACKETS};
        this->emplaceUnaryOperator(type);
        this->emplaceExpressionTokens();
        return;
    }
    switch(this->lastInstructionType()) {
    case BLANK:
    case OPERATION:
        this->setLastInstructionType(OPERATION);
        this->allowedTokens = {EQUAL_OPERATOR, OPERATION_EQUAL, DOT_OPERATOR, COMMA, OPEN_BRACKETS, OPEN_SQUARE_BRACKETS, eofTokenType};
        if(previousTokens.empty()) { this->allowedTokens.emplace_back(OPEN_BRACKETS); }
        this->emplaceUnaryOperator(type);
        break;
    case DECLARATION:
        if(!this->isPreviousEmpty() && this->previousTokensLast() == COLON) {
            this->allowedTokens = {EQUAL_OPERATOR, OPEN_SQUARE_BRACKETS, eofTokenType};
            break;
        }
        this->allowedTokens = {COMMA, COLON};
        break;
    case FOR_STRUCTURE:
        if(this->isPreviousEmpty()) {
            this->allowedTokens = {};
            break;
        }
        if(this->previousTokensLast() == KEYWORD_VAR) {
            this->allowedTokens = {COLON};
            break;
        }
        this->allowedTokens = {EQUAL_OPERATOR};
        break;
    case DEFINITION:
        this->allowedTokens = {OPEN_BRACKETS};
        break;
    case PARAMETER_DEFINITION:
        if(this->previousTokensLast() == COLON) {
            this->allowedTokens = {COMMA, CLOSED_BRACKETS};
            break;
        }
        this->allowedTokens = {COLON};
        break;
    case RETURN_DEFINITION:
        this->allowedTokens = {COMMA, OPEN_CURLY_BRACKETS};
        break;
    default:
        this->allowedTokens = {};
        break;
    }
}

void Instruction::checkNumber(const TokenType& type) noexcept {
    using enum TokenType;
    using enum InstructionType;
    if(this->isExpression()) {
        this->allowedTokens = {OPERATOR, MINUS_OPERATOR, LOGICAL_OPERATOR};
        if(type == STRING) {
            this->allowedTokens.emplace_back(DOT_OPERATOR);
            this->allowedTokens.emplace_back(OPEN_SQUARE_BRACKETS);
        }
        this->emplaceExpressionTokens();
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkOperator() {
    using enum TokenType;
    using enum InstructionType;
    if(this->isExpression()) {
        this->allowedTokens = {IDENTIFIER, INTEGER, DOUBLE, CHAR, STRING, BOOLEAN, MINUS_OPERATOR, OPEN_BRACKETS};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkMinusOperator() {
    using enum TokenType;
    using enum InstructionType;
    if(this->isExpression()) {
        this->allowedTokens = {IDENTIFIER, INTEGER, DOUBLE, CHAR, STRING, BOOLEAN, OPEN_BRACKETS};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkEqualOperator() {
    using enum TokenType;
    using enum InstructionType;
    this->allowedTokens = this->expressionStart;
    if(lastInstructionTypeIs(OPERATION) || lastInstructionTypeIs(DECLARATION)) {
        if(lastInstructionTypeIs(OPERATION)) {
            this->setLastInstructionType(ASSIGNATION);
        } else {
            this->setLastInstructionType(INITIALIZATION);
        }
        return;
    }
    if(lastInstructionTypeIs(FOR_STRUCTURE)) {
        this->addInstructionType(FOR_INITIALIZATION);
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkBooleanAndLogicalOperator(const TokenType &type) {
    using enum TokenType;
    using enum InstructionType;
    if(this->isExpression()) {
        this->allowedTokens = this->expressionStart;
        if(type != NOT_OPERATOR) {
            this->allowedTokens.emplace_back(NOT_OPERATOR);
            this->setLastBooleanOperatorPresent(type == BOOLEAN_OPERATOR);
        }
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkComma() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(OPERATION) || lastInstructionTypeIs(DECLARATION) || lastInstructionTypeIs(PARAMETER_DEFINITION) ||
       lastInstructionTypeIs(RETURN_DEFINITION)) {
        this->allowedTokens = {IDENTIFIER};
        return;
    }
    if(lastInstructionTypeIs(FOR_INITIALIZATION)) {
        this->setLastInstructionType(FOR_CONDITION);
    } else if(lastInstructionTypeIs(FOR_CONDITION)) {
        this->setLastInstructionType(FOR_STEP);
    }
    this->setLastBooleanOperatorPresent(false);
    this->allowedTokens = this->expressionStart;
}

void Instruction::checkColon() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(DECLARATION) || lastInstructionTypeIs(FOR_STRUCTURE) ||
       lastInstructionTypeIs(PARAMETER_DEFINITION) || lastInstructionTypeIs(RETURN_DEFINITION)) {
        this->allowedTokens = {IDENTIFIER};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkOpenBrackets(const TokenType &type) {
    using enum TokenType;
    using enum InstructionType;
    this->addBooleanOperatorPresent();
    this->allowedTokens = {IDENTIFIER, INTEGER, DOUBLE, CHAR, STRING, BOOLEAN, MINUS_OPERATOR, NOT_OPERATOR, OPEN_BRACKETS};
    if(type == OPEN_BRACKETS) {
        this->allowedTokens.emplace_back(CLOSED_BRACKETS);
        if(lastInstructionTypeIs(DEFINITION)) {
            this->addInstructionType(PARAMETER_DEFINITION);
            this->allowedTokens = {IDENTIFIER, CLOSED_BRACKETS};
            return;
        }
        if(this->previousTokensLast() == IDENTIFIER || this->previousTokensLast() == CLOSED_SQUARE_BRACKETS) {
            this->addInstructionType(PARAMETER_EXPRESSION);
            return;
        }
        this->addInstructionType(EXPRESSION);
        return;
    }
    if(this->previousTokensLast() == EQUAL_OPERATOR || this->previousTokensLast() == COMMA ||
       this->previousTokensLast() == OPEN_SQUARE_BRACKETS) {
        this->addInstructionType(ARRAY_INIZIALIZATION);
        this->allowedTokens.emplace_back(OPEN_SQUARE_BRACKETS);
        this->allowedTokens.emplace_back(CLOSED_SQUARE_BRACKETS);
        return;
    }
    if(lastInstructionTypeIs(DECLARATION)) { this->allowedTokens.emplace_back(CLOSED_SQUARE_BRACKETS); }
    this->addInstructionType(SQUARE_EXPRESSION);
}

void Instruction::checkClosedBrackets(const TokenType &type) {
    using enum TokenType;
    using enum InstructionType;
    
    this->removeInstructionType();
    this->removeBooleanOperatorPresent();
    if(this->isExpression()) {
        this->allowedTokens = {OPERATOR, MINUS_OPERATOR, LOGICAL_OPERATOR, DOT_OPERATOR, OPEN_SQUARE_BRACKETS};
        if(type == CLOSED_SQUARE_BRACKETS) {
            this->allowedTokens.emplace_back(UNARY_OPERATOR);
            this->allowedTokens.emplace_back(OPEN_BRACKETS);
        }
        this->emplaceExpressionTokens();
        return;
    }
    switch(this->lastInstructionType()) {
    case OPERATION:
        this->allowedTokens = {DOT_OPERATOR, OPEN_SQUARE_BRACKETS};
        if (type == CLOSED_BRACKETS) {
            this->allowedTokens.emplace_back(eofTokenType);
            break;
        }
        this->allowedTokens.emplace_back(EQUAL_OPERATOR);
        this->allowedTokens.emplace_back(OPERATION_EQUAL);
        this->allowedTokens.emplace_back(UNARY_OPERATOR);
        this->allowedTokens.emplace_back(COMMA);
        this->allowedTokens.emplace_back(OPEN_BRACKETS);
        break;
    case DECLARATION:
        this->allowedTokens = {EQUAL_OPERATOR, eofTokenType};
        if(type == CLOSED_SQUARE_BRACKETS) { this->allowedTokens.emplace_back(OPEN_SQUARE_BRACKETS); }
        break;
    case STRUCTURE:
        this->allowedTokens = {OPEN_CURLY_BRACKETS};
        break;
    case DEFINITION:
        this->setLastInstructionType(RETURN_DEFINITION);
        this->allowedTokens = {COLON, OPEN_CURLY_BRACKETS};
        break;
    default:
        this->allowedTokens = {};
        break;
    }
}

void Instruction::checkOpenCurlyBrackets() {
    using enum InstructionType;
    using enum TokenType;
    if(lastInstructionTypeIs(BLANK)) { this->setLastInstructionType(OPEN_SCOPE); }
    this->allowedTokens = {eofTokenType, CLOSED_CURLY_BRACKETS};
}

void Instruction::checkClosedCurlyBracktes() {
    using enum InstructionType;
    if(lastInstructionTypeIs(BLANK)) { this->setLastInstructionType(CLOSE_SCOPE); }
    this->allowedTokens = {eofTokenType};
}

void Instruction::checkKeywordMain() {
    using enum InstructionType;
    using enum TokenType;
    if(this->lastInstructionTypeIs(BLANK)) {
        this->setLastInstructionType(MAIN);
        this->allowedTokens = {OPEN_CURLY_BRACKETS};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkKeywordVar() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(BLANK)) {
        this->setLastInstructionType(DECLARATION);
        this->allowedTokens = {IDENTIFIER};
        return;
    }
    if(lastInstructionTypeIs(FOR_STRUCTURE)) {
        this->allowedTokens = {IDENTIFIER};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkKeywordStructure() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(BLANK)) {
        this->setLastInstructionType(STRUCTURE);
        this->allowedTokens = {OPEN_BRACKETS};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkKeywordFor() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(BLANK)) {
        this->setLastInstructionType(FOR_STRUCTURE);
        this->allowedTokens = {KEYWORD_VAR, IDENTIFIER};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkKeywordFunc() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(BLANK)) {
        this->setLastInstructionType(DEFINITION);
        this->allowedTokens = {IDENTIFIER};
        return;
    }
    this->allowedTokens = {};
}

void Instruction::checkKeywordReturn() {
    using enum TokenType;
    using enum InstructionType;
    if(lastInstructionTypeIs(BLANK)) {
        this->setLastInstructionType(RETURN_EXPRESSION);
        this->allowedTokens = this->expressionStart;
        this->allowedTokens.emplace_back(eofTokenType);
        return;
    }
    this->allowedTokens = {};
}
bool Instruction::emplaceForTokens() noexcept {
    if(this->isForExpression()) {
        this->allowedTokens.emplace_back(TokenType::OPEN_CURLY_BRACKETS);
        if(this->lastInstructionType() != InstructionType::FOR_STEP) { this->allowedTokens.emplace_back(TokenType::COMMA); };
        return true;
    }
    return false;
}

DISABLE_WARNINGS_POP()
