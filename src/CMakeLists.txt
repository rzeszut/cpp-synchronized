find_package(Threads REQUIRED)

add_library(synchronized synchronized.cpp)

add_executable(main main.cpp)

target_link_libraries(main synchronized ${CMAKE_THREAD_LIBS_INIT})
