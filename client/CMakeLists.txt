cmake_minimum_required(VERSION 3.0.2)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

if (UNIX)
	add_executable(r-type "src/main.cpp")
	target_link_libraries(r-type boost_system pthread)
endif(UNIX)

if (WIN32)
	include_directories("lib\\SFML-2.4.2\\include\\SFML")
	link_directories("lib\\SFML-2.4.2\\lib")
	add_executable(r-type "src/main.cpp")
	target_link_libraries(r-type sfml-graphics sfml-audio sfml-window sfml-system)
endif(WIN32)