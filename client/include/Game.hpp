#pragma once

#include "Player.hpp"
#include "Header.hpp"

class Game {
private:
	Header infos;
	std::vector<Entity> entities;
	std::vector<Enemy> enemies;
	std::vector<Player> players;
public:
	void getInfosFromServer(std::vector<char> buff);
	std::vector<char> getVector();
	Game();
	~Game();
	Header getInfos();
	std::vector<Entity> getEntities();
	std::vector<Enemy> getEnemies();
	std::vector<Player> getPlayers();
private:
	std::vector<char> addVector(std::vector<char> a,
		std::vector<char> b);
};