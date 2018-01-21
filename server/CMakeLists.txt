cmake_minimum_required(VERSION 3.0.2)

project(r-type_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("include")
add_executable(r-type_server "src/main.cpp" "src/Network.cpp" "include/Network.hpp")

if (UNIX)
	target_link_libraries(r-type_server)
endif(UNIX)

target_link_libraries(r-type_server libnet libprotocol)