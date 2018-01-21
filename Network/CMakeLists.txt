cmake_minimum_required(VERSION 3.0.2)

project(libnet)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("../deps/boost" "include")

add_library(libnet "src/AsioSocket.cpp" "include/ISocket.hpp" "include/AsioSocket.hpp")

if (UNIX)
	target_link_libraries(libnet boost_system pthread)
endif(UNIX)