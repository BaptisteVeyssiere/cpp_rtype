cmake_minimum_required(VERSION 3.0.2)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("include")

set(SOURCES
"include/GameData.hpp")

set(HEADERS
"src/main.cpp"
"src/GameData.cpp")

if (UNIX)
	add_executable(r-type ${SOURCES} ${HEADERS})
	target_link_libraries(r-type boost_system pthread libprotocol)
endif(UNIX)

if (WIN32)
	include_directories("lib\\SFML-2.4.2\\include" "include")
	link_directories("lib\\SFML-2.4.2\\lib")
	add_executable(r-type ${SOURCES} ${HEADERS})
	target_link_libraries(r-type sfml-graphics sfml-audio sfml-window sfml-system libprotocol)
endif(WIN32)
endif(WIN32)

add_executable(r-type "src/main.cpp" "src/Window.cpp" "src/Game.cpp" "src/Layer.cpp" "src/Textures.cpp" "src/Gui.cpp")
target_link_libraries(r-type sfml-graphics-d sfml-audio-d sfml-window-d sfml-system-d)