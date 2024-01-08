include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(Dersbiander_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(Dersbiander_setup_options)
  option(Dersbiander_ENABLE_HARDENING "Enable hardening" ON)
  option(Dersbiander_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    Dersbiander_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    Dersbiander_ENABLE_HARDENING
    OFF)

  Dersbiander_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR Dersbiander_PACKAGING_MAINTAINER_MODE)
    option(Dersbiander_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(Dersbiander_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(Dersbiander_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(Dersbiander_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(Dersbiander_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(Dersbiander_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(Dersbiander_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(Dersbiander_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(Dersbiander_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(Dersbiander_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(Dersbiander_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(Dersbiander_ENABLE_PCH "Enable precompiled headers" OFF)
    option(Dersbiander_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(Dersbiander_ENABLE_IPO "Enable IPO/LTO" ON)
    option(Dersbiander_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(Dersbiander_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(Dersbiander_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(Dersbiander_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(Dersbiander_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(Dersbiander_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(Dersbiander_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(Dersbiander_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(Dersbiander_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(Dersbiander_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(Dersbiander_ENABLE_PCH "Enable precompiled headers" OFF)
    option(Dersbiander_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      Dersbiander_ENABLE_IPO
      Dersbiander_WARNINGS_AS_ERRORS
      Dersbiander_ENABLE_USER_LINKER
      Dersbiander_ENABLE_SANITIZER_ADDRESS
      Dersbiander_ENABLE_SANITIZER_LEAK
      Dersbiander_ENABLE_SANITIZER_UNDEFINED
      Dersbiander_ENABLE_SANITIZER_THREAD
      Dersbiander_ENABLE_SANITIZER_MEMORY
      Dersbiander_ENABLE_UNITY_BUILD
      Dersbiander_ENABLE_CLANG_TIDY
      Dersbiander_ENABLE_CPPCHECK
      Dersbiander_ENABLE_COVERAGE
      Dersbiander_ENABLE_PCH
      Dersbiander_ENABLE_CACHE)
  endif()

  Dersbiander_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (Dersbiander_ENABLE_SANITIZER_ADDRESS OR Dersbiander_ENABLE_SANITIZER_THREAD OR Dersbiander_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(Dersbiander_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(Dersbiander_global_options)
  if(Dersbiander_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    Dersbiander_enable_ipo()
  endif()

  Dersbiander_supports_sanitizers()

  if(Dersbiander_ENABLE_HARDENING AND Dersbiander_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR Dersbiander_ENABLE_SANITIZER_UNDEFINED
       OR Dersbiander_ENABLE_SANITIZER_ADDRESS
       OR Dersbiander_ENABLE_SANITIZER_THREAD
       OR Dersbiander_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${Dersbiander_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${Dersbiander_ENABLE_SANITIZER_UNDEFINED}")
    Dersbiander_enable_hardening(Dersbiander_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(Dersbiander_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(Dersbiander_warnings INTERFACE)
  add_library(Dersbiander_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  Dersbiander_set_project_warnings(
    Dersbiander_warnings
    ${Dersbiander_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(Dersbiander_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(Dersbiander_options)
  endif()

  include(cmake/Sanitizers.cmake)
  Dersbiander_enable_sanitizers(
    Dersbiander_options
    ${Dersbiander_ENABLE_SANITIZER_ADDRESS}
    ${Dersbiander_ENABLE_SANITIZER_LEAK}
    ${Dersbiander_ENABLE_SANITIZER_UNDEFINED}
    ${Dersbiander_ENABLE_SANITIZER_THREAD}
    ${Dersbiander_ENABLE_SANITIZER_MEMORY})

  set_target_properties(Dersbiander_options PROPERTIES UNITY_BUILD ${Dersbiander_ENABLE_UNITY_BUILD})

  if(Dersbiander_ENABLE_PCH)
    target_precompile_headers(
      Dersbiander_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(Dersbiander_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    Dersbiander_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(Dersbiander_ENABLE_CLANG_TIDY)
    Dersbiander_enable_clang_tidy(Dersbiander_options ${Dersbiander_WARNINGS_AS_ERRORS})
  endif()

  if(Dersbiander_ENABLE_CPPCHECK)
    Dersbiander_enable_cppcheck(${Dersbiander_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(Dersbiander_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    Dersbiander_enable_coverage(Dersbiander_options)
  endif()

  if(Dersbiander_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(Dersbiander_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(Dersbiander_ENABLE_HARDENING AND NOT Dersbiander_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR Dersbiander_ENABLE_SANITIZER_UNDEFINED
       OR Dersbiander_ENABLE_SANITIZER_ADDRESS
       OR Dersbiander_ENABLE_SANITIZER_THREAD
       OR Dersbiander_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    Dersbiander_enable_hardening(Dersbiander_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
