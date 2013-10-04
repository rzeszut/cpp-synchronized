find_package(Threads)

add_executable(runTests runner.cpp synchronized_test.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests synchronized)

add_test(run-tests runTests)
