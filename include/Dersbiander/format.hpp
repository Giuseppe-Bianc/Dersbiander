#pragma once

#include <fmt/core.h>    // NOLINT(*-include-cleaner)
#include <fmt/format.h>  // NOLINT(*-include-cleaner)

#define FORMAT(...) fmt::format(__VA_ARGS__)
#define FMT_PTR(ptr) fmt::ptr(ptr)
#define FMT_JOIN(container, delimiter) fmt::join(container, delimiter)
