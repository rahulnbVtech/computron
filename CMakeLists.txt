cmake_minimum_required(VERSION 3.29)
project(Computron)

set(CMAKE_CSS_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(include)
include_directories(test/catch2)

add_executable(Computron
src/main.cpp
src/computron.cpp
)

add_executable(testing test/test.cpp src/main.cpp src/computron.cpp)
enable_testing()