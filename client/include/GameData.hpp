#pragma once

#include "Protocol.hpp"
#include "ClientEntity.hpp"
#include "ClientEnemy.hpp"
#include "ClientPlayer.hpp"

class GameData {
private:
	Header infos;
	std::vector<ClientEntity> entities;
	std::vector<ClientEnemy> enemies;
	std::vector<ClientPlayer> players;

public:
	void getInfosFromServer(std::vector<char> buff);
	std::vector<char> getVector();
	GameData();
	~GameData();
	Header& getInfos();
	std::vector<ClientEntity>& getEntities();
	std::vector<ClientEnemy>& getEnemies();
	std::vector<ClientPlayer>& getPlayers();
	void	emptyLists();
	void	display();
private:
	std::vector<char> addVector(std::vector<char> a,
		std::vector<char> b);
	void setHeader();
};