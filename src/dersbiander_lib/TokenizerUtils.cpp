#include "Dersbiander/TokenizerUtils.hpp"
#include <unordered_set>

DISABLE_WARNINGS_PUSH(
    4005 4201 4459 4514 4625 4626 4820 6244 6285 6385 6386 26409 26415 26418 26429 26432 26437 26438 26440 26446 26447 26450 26451 26455 26457 26459 26460 26461 26467 26472 26473 26474 26475 26481 26482 26485 26490 26491 26493 26494 26495 26496 26497 26498 26800 26814 26818 26826)

// NOLINTNEXTLINE
bool TokenizerUtils::isPlusORMinus(char cha) noexcept { return cha == '+' || cha == '-'; }

bool TokenizerUtils::isComment(const std::string_view &inputSpan, size_t position) noexcept {
    return position != inputSpan.size() && inputSpan[position] == '/' &&
           (inputSpan[position + 1] == '/' || inputSpan[position + 1] == '*');
}
// NOLINTNEXTLINE
bool TokenizerUtils::isOperator(char c) noexcept {
    static const std::unordered_set<char> operators = {'*', '/', '=', ',', ':', '<', '>', '!', '|', '&', '+', '-', '^'};
    return operators.contains(c);
}

bool TokenizerUtils::isOperationEqualOperator(const std::string &value) noexcept {
    return value == "+=" || value == "-=" || value == "*=" || value == "/=";
}

bool TokenizerUtils::isBooleanOperator(const std::string &value) noexcept {
    return value == "==" || value == ">=" || value == "<=" || value == "!=";
}

bool TokenizerUtils::isLogicalOperator(const std::string &value) noexcept { return value == "&&" || value == "||"; }

bool TokenizerUtils::isUnaryOperator(const std::string &value) noexcept { return value == "++" || value == "--"; }

bool TokenizerUtils::isVarLenOperator(const std::string &val) noexcept {
    return isOperator(val[0]) || isBrackets(val[0]) || isOperationEqualOperator(val) || isBooleanOperator(val) ||
           isLogicalOperator(val);
}

// NOLINTNEXTLINE
bool TokenizerUtils::isBrackets(char cha) noexcept {
    return cha == '(' || cha == ')' || cha == '[' || cha == ']' || cha == '{' || cha == '}';
}

// NOLINTNEXTLINE
bool TokenizerUtils::isApostrophe(char cha) noexcept { return cha == '\''; }

bool TokenizerUtils::isQuotation(char cha) noexcept { return cha == '\"'; }

bool TokenizerUtils::inCNL(char cha) noexcept { return cha == CNL; }

DISABLE_WARNINGS_POP()
