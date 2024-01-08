add_executable(dersbiander main.cpp)

target_link_libraries(
  dersbiander
  PRIVATE Dersbiander::Dersbiander_options
          Dersbiander::Dersbiander_warnings)

target_link_system_libraries(
  dersbiander
  PRIVATE
          CLI11::CLI11)

target_include_directories(dersbiander PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
