include(GenerateExportHeader)

find_package(glm REQUIRED)
add_library(dersbiander_lib dersbiander.cpp TokenizerUtils.cpp Tokenizer.cpp Instruction.cpp
        Token.cpp
        TokenizerUtils.cpp)

add_library(Dersbiander::dersbiander_lib ALIAS dersbiander_lib)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(dersbiander_lib PRIVATE -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(dersbiander_lib PRIVATE -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION GREATER 1900)
    target_compile_options(dersbiander_lib PRIVATE /arch:AVX2)
else ()
    message(STATUS "Impossible to set simd instructionto to avx2 for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif ()

target_link_libraries(dersbiander_lib PRIVATE
        Dersbiander_options
        Dersbiander_warnings)
target_link_libraries(dersbiander_lib PUBLIC
        fmt::fmt
        spdlog::spdlog
        glm::glm
)

target_include_directories(dersbiander_lib ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_compile_features(dersbiander_lib PUBLIC cxx_std_20)


set_target_properties(
        dersbiander_lib
        PROPERTIES VERSION ${PROJECT_VERSION}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(dersbiander_lib EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/Dersbiander/dersbiander_export.hpp)

if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(dersbiander_lib PUBLIC VANDIOR_LIB_STATIC_DEFINE)
endif ()
