cmake_minimum_required(VERSION 3.0.2)

project(libprotocol)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SOURCES
"include/Connect.hpp"
"include/Enemy.hpp"
"include/Entity.hpp"
"include/Player.hpp"
"include/Header.hpp"
"include/Key.hpp"
"include/Pos.hpp"
"include/Inputs.hpp")

set(HEADERS
"src/Connect.cpp"
"src/Enemy.cpp"
"src/Entity.cpp"
"src/Header.cpp"
"src/Inputs.cpp"
"src/Player.cpp")

include_directories("include")

add_library(libprotocol ${SOURCES} ${HEADERS})