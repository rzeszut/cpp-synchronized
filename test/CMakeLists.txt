find_package(Threads REQUIRED)

add_executable(runTests runner.cpp synchronized_test.cpp)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests synchronized)
target_link_libraries(runTests ${CMAKE_THREAD_LIBS_INIT})

add_test(run-tests runTests)
