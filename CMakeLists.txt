cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(minesweeper VERSION 1.0)
add_executable(minesweeper src/main.cpp)

target_include_directories(minesweeper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR/include})