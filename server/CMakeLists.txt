cmake_minimum_required(VERSION 3.0.2)

project(r-type_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(SOURCES "src/main.cpp" 
			"src/Network.cpp"
			"src/Room.cpp"
			"src/RoomManager.cpp"
			"src/GameCore.cpp"
			"src/IEntity.cpp"
			"src/IProjectile.cpp"
			"src/WinLibLoader.cpp"
			"src/MonsterFactory.cpp"
			"src/Humain.cpp"
			"src/PlayerMissile.cpp"
			"src/Timer.cpp"
			)

set(HEADERS "include/Request.hpp"
			"include/Network.hpp"
			"include/Room.hpp"
			"include/RoomManager.hpp"
			"include/GameCore.hpp"
			"include/Hitbox.hpp"
			"include/IEntity.hpp"
			"include/ILibLoader.hpp"
			"include/IMonster.hpp"
			"include/IProjectile.hpp"
			"include/MonsterFactory.hpp"
			"include/Humain.hpp"
			"include/PlayerMissile.hpp"
			"include/Pos.hpp"
			"include/Timer.hpp"
			"include/Type.hpp"
			"include/WinLibLoader.hpp"
			)


include_directories("include")
add_executable(r-type_server  ${SOURCES} ${HEADERS})

if (UNIX)
	target_link_libraries(r-type_server)
endif(UNIX)

target_link_libraries(r-type_server libnet libprotocol)