cmake_minimum_required(VERSION 3.0.2)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("include")

set(SOURCES
"src/main.cpp"
"src/Window.cpp"
"src/Game.cpp"
"src/Layer.cpp"
"src/Textures.cpp"
"src/Gui.cpp"
"src/GameData.cpp")

set(HEADERS
"include/GameData.hpp"
"include/Window.hpp"
"include/Game.hpp"
"include/Layer.hpp"
"include/Textures.hpp"
"include/Gui.hpp")

if (UNIX)
endif(UNIX)

if (WIN32)
	include_directories("lib\\SFML-2.4.2\\include" "include")
	link_directories("lib\\SFML-2.4.2\\lib")
endif(WIN32)

add_executable(r-type ${SOURCES} ${HEADERS})
target_link_libraries(r-type sfml-graphics-d sfml-audio-d sfml-window-d sfml-system-d libprotocol)