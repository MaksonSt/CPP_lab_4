cmake_minimum_required(VERSION 3.10)
project(MultithreadingLab)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)

add_executable(lab
    main.cpp
    DataStructure.cpp
    FileGenerator.cpp
    Executor.cpp
)

target_link_libraries(lab PRIVATE Threads::Threads)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated_files)