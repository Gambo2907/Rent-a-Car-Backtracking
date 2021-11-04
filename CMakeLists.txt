cmake_minimum_required(VERSION 2.6)
project(Rent-a-Car-Backtracking)

set(CMAKE_CXX_FLAGS "-g -Wall")

include_directories(.)
file(GLOB Rent-a-Car-Backtracking_SRC
    "*.h"
    "*.cpp"
)
add_executable(Rent-a-Car-Backtracking ${Rent-a-Car-Backtracking_SRC} )