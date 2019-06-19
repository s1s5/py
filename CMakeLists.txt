cmake_minimum_required (VERSION 3.5)
project (cxxpy)

set(CMAKE_CXX_STANDARD 17)
include_directories(AFTER include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")

enable_testing()
add_subdirectory(test)
