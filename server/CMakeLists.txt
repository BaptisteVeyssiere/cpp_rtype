cmake_minimum_required(VERSION 3.0.2)

project(r-type_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

include_directories("include")

add_executable(r-type_server "src/main.cpp"
							"src/Network.cpp"
							"src/IEntity.cpp"
							"src/Timer.cpp"
							"src/GameCore.cpp"
							"src/MonsterFactory.cpp"
							"src/WinLibLoader.cpp"
							"src/Player.cpp"
							"src/PlayerMissile.cpp"
							"include/Timer.hpp"
							"include/Network.hpp"
							"include/IEntity.hpp"
							"include/Hitbox.hpp"
							"include/Type.hpp"
							"include/IMonster.hpp"
							"include/IProjectile.hpp"
							"include/GameCore.hpp"
							"include/MonsterFactory.hpp"
							"include/ILibLoader.hpp"
							"include/WinLibLoader.hpp"
							"include/Player.hpp"
							"include/PlayerMissile.hpp"
							)

if (UNIX)
	target_link_libraries(r-type_server)
endif(UNIX)

target_link_libraries(r-type_server libnet)