#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

std::vector<char> Game::addVector(std::vector<char> a, std::vector<char> b)
{
	std::vector<char> ret;

	ret.reserve(a.size() + b.size());
	ret.insert(ret.end(), a.begin(), a.end());
	ret.insert(ret.end(), b.begin(), b.end());
	return (ret);
}

std::vector<char> Game::getVector()
{
	std::vector<char> ret;

	infos.entityCount = entities.size();
	infos.enemyCount = enemies.size();
	infos.playersCount = players.size();
	ret = addVector(infos.getVector(), ret);
	for (int i = 0; i < entities.size(); i++)
		ret = addVector(entities[i].getVector(), ret);
	for (int i = 0; i < enemies.size(); i++)
		ret = addVector(enemies[i].getVector(), ret);
	for (int i = 0; i < players.size(); i++)
		ret = addVector(players[i].getVector(), ret);
	return (ret);
}

void	Game::getInfosFromServer(std::vector<char> buff)
{
	std::memcpy(&infos, buff.data(), sizeof(Header));
}

Header Game::getInfos()
{
	return (this->infos);
}

std::vector<Entity> Game::getEntities()
{
	return (this->entities);
}
std::vector<Enemy> Game::getEnemies()
{
	return (this->enemies);
}
std::vector<Player> Game::getPlayers()
{
	return (this->players);
}