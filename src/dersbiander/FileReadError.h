#pragma once

#include "Dersbiander/headers.hpp"

class FileReadError : public std::runtime_error {
public:
    explicit FileReadError(const std::string_view &message)  // NOLINT(*-easily-swappable-parameters)
      : std::runtime_error(message.data()) {}
};
