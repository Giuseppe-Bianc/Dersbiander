#pragma once
#include "headers.hpp"

class TokenizerUtils {
public:
    [[nodiscard]] static bool isPlusORMinus(char cha) noexcept;
    [[nodiscard]] static bool isComment(const std::string_view &inputSpan, size_t position) noexcept;
    [[nodiscard]] static bool isOperator(char cha) noexcept;
    [[nodiscard]] static bool isOperationEqualOperator(const std::string &value) noexcept;
    [[nodiscard]] static bool isBooleanOperator(const std::string &value) noexcept;
    [[nodiscard]] static bool isLogicalOperator(const std::string &value) noexcept;
    [[nodiscard]] static bool isUnaryOperator(const std::string &value) noexcept;
    [[nodiscard]] static bool isVarLenOperator(const std::string &val) noexcept;
    [[nodiscard]] static bool isBrackets(char cha) noexcept;
    [[nodiscard]] static bool isApostrophe(char cha) noexcept;
    [[nodiscard]] static bool isQuotation(char cha) noexcept;
    [[nodiscard]] static bool inCNL(char cha) noexcept;
};
