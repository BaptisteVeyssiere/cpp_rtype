cmake_minimum_required(VERSION 3.0.2)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(r-type "src/main.cpp")

if (UNIX)
	target_link_libraries(r-type boost_system pthread)
endif(UNIX)