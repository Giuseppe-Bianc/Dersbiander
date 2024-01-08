#pragma once

#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
#define DISABLE_WARNINGS_PUSH(...) __pragma(warning(push)) __pragma(warning(disable : __VA_ARGS__))
#define DISABLE_WARNINGS_POP() __pragma(warning(pop))
#else
#define DISABLE_WARNINGS_PUSH(...)
#define DISABLE_WARNINGS_POP()
#endif
