cmake_minimum_required(VERSION 3.0.2)

project(net_test1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("include")

add_executable(net_test1 "src/test1.cpp")

target_link_libraries(net_test1 libnet)