file(GLOB_RECURSE SOURCES "*.cpp" "*.h" "*.hpp")
add_executable(dersbiander ${SOURCES})

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    target_compile_options(dersbiander PRIVATE -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(dersbiander PRIVATE -march=native)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND MSVC_VERSION GREATER 1900)
    target_compile_options(dersbiander PRIVATE /arch:AVX2)
else ()
    message(STATUS "Impossible to set simd instructionto to avx2 for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif ()

target_link_libraries(
        dersbiander
        PRIVATE Dersbiander::Dersbiander_options
        Dersbiander::Dersbiander_warnings)

target_link_system_libraries(
        dersbiander
        PRIVATE
        CLI11::CLI11
        Dersbiander::dersbiander_lib
)

target_include_directories(dersbiander PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

