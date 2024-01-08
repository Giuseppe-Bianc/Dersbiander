include(GenerateExportHeader)

add_library(dersbiander_lib dersbiander.cpp)

add_library(Dersbiander::dersbiander_lib ALIAS dersbiander_lib)

target_link_libraries(dersbiander_lib PRIVATE Dersbiander_options Dersbiander_warnings)

target_include_directories(dersbiander_lib ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(dersbiander_lib PUBLIC cxx_std_20)

set_target_properties(
  dersbiander_lib
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(dersbiander_lib EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/Dersbiander/dersbiander_lib_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(dersbiander_lib PUBLIC dersbiander_lib_STATIC_DEFINE)
endif()
