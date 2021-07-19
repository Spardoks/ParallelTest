cmake_minimum_required(VERSION 3.5)

project(accumulate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

set(HEADERS accumulte.hpp)
set(SOURCES main.cpp)

add_executable(accumulate ${HEADERS} ${SOURCES})

target_link_libraries(accumulate PRIVATE Threads::Threads)
