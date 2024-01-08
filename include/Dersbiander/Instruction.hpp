#pragma once

#include "InstructionType.hpp"
#include "Token.hpp"
#include <vector>

class Instruction {
public:
    explicit Instruction() noexcept;
    [[nodiscard]] std::vector<std::string> typeToString() const noexcept;
    [[nodiscard]] std::pair<bool, std::string> checkToken(const Token &token);
    [[nodiscard]] inline bool canTerminate() {
        return std::ranges::find(this->allowedTokens, eofTokenType) != this->allowedTokens.end();
    }

private:
    std::vector<Token> tokens;
    std::vector<Token> previousTokens;
    std::vector<InstructionType> instructionTypes;
    std::vector<TokenType> allowedTokens;
    std::vector<bool> booleanOperatorPresent;

    // NOLINTBEGIN
    [[nodiscard]] std::string unexpected(const Token &token) const;  // NOLINT(*-identifier-length) NOLINT(functionStatic)
    // NOLINTEND
    void checkIdentifier(const TokenType &type) noexcept;
    void checkNumber(const TokenType &type) noexcept;
    void checkOperator();
    void checkMinusOperator();
    void checkEqualOperator();
    void checkBooleanAndLogicalOperator(const TokenType &type);
    void checkComma();
    void checkColon();
    void checkOpenBrackets(const TokenType &type);
    void checkClosedBrackets(const TokenType &type);
    void checkOpenCurlyBrackets();
    void checkClosedCurlyBracktes();
    void checkKeywordMain();
    void checkKeywordVar();
    void checkKeywordStructure();
    void checkKeywordFor();
    void checkKeywordFunc();
    void checkKeywordReturn();
    void emplaceCommaEoft() noexcept;
    void emplaceExpressionTokens();
    [[nodiscard]] inline bool isExpression() noexcept;
    // NOLINTNEXTLINE
    [[nodiscard]] inline bool isForExpression() noexcept;
    [[nodiscard]] TokenType previousTokensLast() noexcept { return this->previousTokens.back().getType(); }
    [[nodiscard]] bool isPreviousEmpty() const noexcept { return this->previousTokens.empty(); }
    [[nodiscard]] InstructionType &lastInstructionType() noexcept { return this->instructionTypes.back(); }
    [[nodiscard]] inline bool lastInstructionTypeIs(const InstructionType &type) noexcept {
        return this->lastInstructionType() == type;
    }
    inline void addInstructionType(InstructionType instructionType) noexcept {
        this->instructionTypes.emplace_back(instructionType);
    }
    void removeInstructionType() noexcept {
        if(this->instructionTypes.empty()) { return; }
        this->instructionTypes.pop_back();
    }
    void setLastInstructionType(InstructionType instructionType) noexcept {
        if(this->instructionTypes.empty()) { return; }
        this->instructionTypes.pop_back();
        this->instructionTypes.emplace_back(instructionType);
    }
    [[nodiscard]] inline bool lastBooleanOperatorPresent() noexcept { return this->booleanOperatorPresent.back(); }
    void addBooleanOperatorPresent() noexcept { this->booleanOperatorPresent.emplace_back(false); }
    void removeBooleanOperatorPresent() noexcept {
        if(this->booleanOperatorPresent.empty()) { return; }
        this->booleanOperatorPresent.pop_back();
    }
    void setLastBooleanOperatorPresent(bool present) noexcept {
        if(this->booleanOperatorPresent.empty()) { return; }
        this->booleanOperatorPresent.pop_back();
        this->booleanOperatorPresent.emplace_back(present);
    }
    inline void emplaceBooleanOperator() noexcept {
        if(!this->lastBooleanOperatorPresent()) { this->allowedTokens.emplace_back(TokenType::BOOLEAN_OPERATOR); }
    }
    [[nodiscard]] inline bool emplaceTokenType(const InstructionType &instruction, const TokenType token) noexcept {
        if(this->lastInstructionType() == instruction) {
            this->allowedTokens.emplace_back(token);
            return true;
        }
        return false;
    }
    inline void emplaceUnaryOperator(const TokenType &type) noexcept {
        if(type != TokenType::UNARY_OPERATOR) { this->allowedTokens.emplace_back(TokenType::UNARY_OPERATOR); }
    }
    inline bool emplaceForTokens() noexcept;
    std::vector<TokenType> expressionStart = {TokenType::IDENTIFIER,     TokenType::INTEGER,
                                              TokenType::DOUBLE,         TokenType::CHAR,
                                              TokenType::STRING,         TokenType::BOOLEAN,
                                              TokenType::MINUS_OPERATOR, TokenType::NOT_OPERATOR,
                                              TokenType::OPEN_BRACKETS,  TokenType::OPEN_SQUARE_BRACKETS};
};
