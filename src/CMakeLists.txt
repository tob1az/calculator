add_library(calc_logic INTERFACE)
target_include_directories(calc_logic INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(calculator main.cpp)
target_link_libraries(calculator calc_logic)
