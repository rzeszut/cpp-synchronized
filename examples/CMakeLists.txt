find_package(Threads REQUIRED)

add_executable(ex1 ex1.cpp)
target_link_libraries(ex1 synchronized ${CMAKE_THREAD_LIBS_INIT})
