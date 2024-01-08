#pragma once

#include "format.hpp"

enum class InstructionType : short {
    PARAMETER_EXPRESSION,
    OPERATION,
    ASSIGNATION,
    EXPRESSION,
    SQUARE_EXPRESSION,
    RETURN_EXPRESSION,
    DECLARATION,
    INITIALIZATION,
    ARRAY_INIZIALIZATION,
    MAIN,
    STRUCTURE,
    FOR_STRUCTURE,
    FOR_INITIALIZATION,
    FOR_CONDITION,
    FOR_STEP,
    DEFINITION,
    PARAMETER_DEFINITION,
    RETURN_DEFINITION,
    OPEN_SCOPE,
    CLOSE_SCOPE,
    BLANK
};
template <> struct fmt::formatter<InstructionType> : fmt::formatter<std::string_view> {  // NOLINT(*-include-cleaner)
    template <typename FormatContext> auto format(InstructionType tokenType, FormatContext &ctx) {
        std::string_view name;
        switch(tokenType) {
            using enum InstructionType;
        case PARAMETER_EXPRESSION:
            name = "PARAMETER_EXPRESSION";
            break;
        case OPERATION:
            name = "OPERATION";
            break;
        case ASSIGNATION:
            name = "ASSIGNATION";
            break;
        case EXPRESSION:
            name = "EXPRESSION";
            break;
        case SQUARE_EXPRESSION:
            name = "SQUARE_EXPRESSION";
            break;
        case RETURN_EXPRESSION:
            name = "RETURN_EXPRESSION";
            break;
        case DECLARATION:
            name = "DECLARATION";
            break;
        case INITIALIZATION:
            name = "INITIALIZATION";
            break;
        case ARRAY_INIZIALIZATION:
            name = "ARRAY_INIZIALIZATION";
            break;
        case MAIN:
            name = "MAIN";
            break;
        case STRUCTURE:
            name = "STRUCTURE";
            break;
        case FOR_STRUCTURE:
            name = "FOR_STRUCTURE";
            break;
        case FOR_INITIALIZATION:
            name = "FOR_INITIALIZATION";
            break;
        case FOR_CONDITION:
            name = "FOR_CONDITION";
            break;
        case FOR_STEP:
            name = "FOR_STEP";
            break;
        case DEFINITION:
            name = "DEFINITION";
            break;
        case PARAMETER_DEFINITION:
            name = "PARAMETER_DEFINITION";
            break;
        case RETURN_DEFINITION:
            name = "RETURN_DEFINITION";
            break;
        case OPEN_SCOPE:
            name = "OPEN_SCOPE";
            break;
        case CLOSE_SCOPE:
            name = "CLOSE_SCOPE";
            break;
        case BLANK:
            name = "BLANK";
            break;
        default:
            name = "UNKNOWN";
            break;
        }
        return fmt::formatter<std::string_view>::format(name, ctx);
    }
};
