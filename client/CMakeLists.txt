cmake_minimum_required(VERSION 3.0.2)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("include")

set(SOURCES
"include/Game.hpp")

set(HEADERS
"src/main.cpp"
"src/Game.cpp")

if (UNIX)
	add_executable(r-type ${SOURCES} ${HEADERS})
	target_link_libraries(r-type boost_system pthread libprotocol)
endif(UNIX)

if (WIN32)
	include_directories("lib\\SFML-2.4.2\\include\\SFML")
	link_directories("lib\\SFML-2.4.2\\lib")
	add_executable(r-type ${SOURCES} ${HEADERS})
	target_link_libraries(r-type sfml-graphics sfml-audio sfml-window sfml-system libprotocol)
endif(WIN32)