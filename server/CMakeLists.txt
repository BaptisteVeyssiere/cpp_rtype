cmake_minimum_required(VERSION 3.0.2)

project(r-type_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SOURCES "src/main.cpp" "src/Network.cpp" "src/Room.cpp" "src/RoomManager.cpp")
set(HEADERS "include/Request.hpp" "include/Network.hpp" "include/Room.hpp" "include/RoomManager.hpp")


include_directories("include")
add_executable(r-type_server  ${SOURCES} ${HEADERS})

if (UNIX)
	target_link_libraries(r-type_server)
endif(UNIX)

target_link_libraries(r-type_server libnet libprotocol)