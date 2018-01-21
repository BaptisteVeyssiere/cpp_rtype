cmake_minimum_required(VERSION 3.0.2)

project(r-type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

if (UNIX)

endif(UNIX)

if (WIN32)
	include_directories("lib\\SFML-2.4.2\\include" "include")
	link_directories("lib\\SFML-2.4.2\\lib")
endif(WIN32)

add_executable(r-type "src/main.cpp" "src/Window.cpp" "src/Game.cpp" "src/Layer.cpp" "src/Textures.cpp" "src/Gui.cpp")
target_link_libraries(r-type sfml-graphics-d sfml-audio-d sfml-window-d sfml-system-d)