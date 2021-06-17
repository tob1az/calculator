
add_executable(calc_test 
    NumberTest.cpp 
    OperatorTest.cpp
    ShuntingYardTest.cpp
    )
target_link_libraries(calc_test gtest_main calc_logic)
add_test(NAME calc_test COMMAND calc_test)