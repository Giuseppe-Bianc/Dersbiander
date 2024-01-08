#include "Dersbiander/dersbiander.hpp"
#include "FileReadError.h"
#include <string>
namespace fs = std::filesystem;

// #define ONLY_TOKEN_TYPE

DISABLE_WARNINGS_PUSH(
    4005 4201 4459 4514 4625 4626 4820 6244 6285 6385 6386 26409 26415 26418 26429 26432 26437 26438 26440 26446 26447 26450 26451 26455 26457 26459 26460 26461 26467 26472 26473 26474 26475 26481 26482 26485 26490 26491 26493 26494 26495 26496 26497 26498 26800 26814 26818 26821 26826)

#include <CLI/CLI.hpp>

DISABLE_WARNINGS_POP()
// This file will be generated automatically when cur_you run the CMake
// configuration step. It creates a namespace called `Dersbiander`. You can modify
// the source template at `configured_files/config.hpp.in`.
#include <internal_use_only/config.hpp>

DISABLE_WARNINGS_PUSH(26461 26821)
// NOLINTNEXTLINE
static void timeTokenizer(Tokenizer &tokenizer, std::vector<Token> &tokens) {
    tokens.clear();
    AutoTimer timer("tokenizer.tokenize()");
    tokens = tokenizer.tokenize();
}

static std::string readFromFile(const std::string &filename) {
    AutoTimer timer("readFromFile");
    fs::path filePath = filename;

    if(!fs::exists(filePath)) { throw FileReadError(FORMAT("File not found: {}", filename)); }
    if(!fs::is_regular_file(filePath)) { throw FileReadError(FORMAT("Path is not a regular file: {}", filename)); }

    std::stringstream buffer;

    if(std::ifstream fileStream{filePath, std::ios::in | std::ios::binary}; fileStream.is_open()) {
        // Ensure that the file is opened securely
        fileStream.exceptions(std::ios::failbit | std::ios::badbit);

        try {
            buffer << fileStream.rdbuf();
        } catch(const std::ios_base::failure &e) {
            throw FileReadError(FORMAT("Unable to read file: {}. Reason: {}", filename, e.what()));
        }
    } else {
        // Handle the case when the file cannot be opened
        // You might throw an exception or return an error indicator
        throw FileReadError(FORMAT("Unable to open file: {}", filename));
    }

    // Extract the content as a string
    return buffer.str();
}

#ifdef _WIN32  // Windows
constexpr std::string_view filename = "../../../input.txt";
#elif defined __unix__  // Linux and Unix-like systems
constexpr std::string_view filename = "input.txt";  // Linux and Unix
#endif

// NOLINTNEXTLINE(bugprone-exception-escape, readability-function-cognitive-complexity)
int main(int argc, const char **argv) {
    spdlog::set_pattern(R"(%^[%T] [%l] %v%$)");
    const auto console = spdlog::stdout_color_mt(R"(console)");
    spdlog::set_default_logger(console);

    std::string lines = readFromFile(filename.data());
    std::size_t line{};
    try {
        CLI::App app{FORMAT("{} version {}", Dersbiander::cmake::project_name, Dersbiander::cmake::project_version)};

        bool show_version = false;
        bool run_code_from_console = false;
        //[[maybe_unused]] bool time_error = false;
        std::optional<std::string> input;
        app.add_option("-i,--input", input, "A message to print back out");
        app.add_flag("--version", show_version, "Show version information");
        app.add_flag("--jit", run_code_from_console, "Run code from the console");

        CLI11_PARSE(app, argc, argv)
        if(show_version) {
            LINFO("{} version {}", Dersbiander::cmake::project_name, Dersbiander::cmake::project_version);
            return EXIT_SUCCESS;
        }

        if(run_code_from_console) [[unlikely]] {
            // if(input.has_value()) {
            // } else {
            // }
        } else [[likely]] {
            // for(const std::string &str : lines) {
            /* if(str.size() < 93) {
                    LINFO("code'{}',code length {}",str, str.length());
                } else {
                    LINFO("code'{}'",str);
                    LINFO("code length {}", str.length());
                }*/
            Tokenizer tokenizer(lines);
            std::vector<Token> tokens{};
            timeTokenizer(tokenizer, tokens);
            std::vector<Instruction> instructions{};
            // Instruction instruction(tokens);
            if(tokens.empty()) [[unlikely]] {
                LINFO("Empty tokens");
                return 0;
            }
            for(const Token &token : tokens) {
#ifdef ONLY_TOKEN_TYPE
                LINFO("Token {}", token.type);
#else
                LINFO("{}", token);
#endif  // ONLY_TOKEN_TYPE
            }
            instructions.reserve(tokens.size());
            AutoTimer tim("tokenizer total time");
            line = tokens.at(0).getLine();
            for(const Token &token : tokens) {
                if(token.getType() == TokenType::COMMENT) [[unlikely]] { continue; }
                if(token.getLine() >= line) [[likely]] {
                    if(instructions.empty() || instructions.back().canTerminate()) [[likely]] {
                        instructions.emplace_back();
                    } else if(instructions.back().typeToString().back() != "EXPRESSION" && token.getType() != TokenType::STRING)
                        [[unlikely]] {
                        LINFO("Unexpected token: ENDL");
                        break;
                    }
                    line = token.getLine() + 1;
                }
                const auto &[verify, token_s] = instructions.back().checkToken(token);
                LINFO("{} {}", verify, token_s);
                if(!verify) [[unlikely]] { break; }
            }
            //}
        }
    } catch(const std::exception &e) {
        LERROR("Unhandled exception in main: {}", e.what());
        return EXIT_FAILURE;
    }
}

DISABLE_WARNINGS_POP()
