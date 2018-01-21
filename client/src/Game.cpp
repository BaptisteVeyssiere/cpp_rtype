#include "Game.hpp"
#include <iostream>

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
	ret.insert(ret.end(), b.begin(), b.end());
	ret.insert(ret.end(), a.begin(), a.end());
	return (ret);
}

void Game::setHeader()
{
	infos.entityCount = entities.size();
	infos.enemyCount = enemies.size();
	infos.playersCount = players.size();
}

std::vector<char> Game::getVector()
{
	std::vector<char> ret;

	setHeader();
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
	memcpy(&infos, buff.data(), sizeof(Header));
	buff.erase(buff.begin(), buff.begin() + sizeof(Header));
	for (int i = 0; i < infos.entityCount; i++)
	{
		Entity entityTmp;
		memcpy(&entityTmp, buff.data(), sizeof(Entity));
		buff.erase(buff.begin(), buff.begin() + sizeof(Entity));
		entities.push_back(entityTmp);
	}
	for (int i = 0; i < infos.enemyCount; i++)
	{
		Enemy enemyTmp;
		memcpy(&enemyTmp, buff.data(), sizeof(Enemy));
		buff.erase(buff.begin(), buff.begin() + sizeof(Enemy));
		enemies.push_back(enemyTmp);
	}
	for (int i = 0; i < infos.playersCount; i++)
	{
		Player playerTmp;
		memcpy(&playerTmp, buff.data(), sizeof(Player));
		buff.erase(buff.begin(), buff.begin() + sizeof(Player));
		players.push_back(playerTmp);
	}
}

void Game::display()
{
	this->setHeader();
	std::cout << "--------Game---------" << std::endl;
	std::cout << "Header: " 
		<< " EntityCount: " << infos.entityCount 
		<< " EnemmyCount: " << infos.enemyCount
		<< " PlayersCount: " << infos.playersCount
		<< std::endl;
	for (int i = 0; i < entities.size(); i ++)
		std::cout << "Entity: "
		<< " ID: " << entities[i].ID
		<< " Pos: " << entities[i].pos.x << " " << entities[i].pos.y
		<< " Scale: " << entities[i].scale
		<< " Sprite: " << entities[i].sprite
		<< std::endl;
	for (int i = 0; i < enemies.size(); i++)
		std::cout << "Enemy: "
		<< " ID: " << enemies[i].ID
		<< " Pos: " << enemies[i].pos.x << " " << enemies[i].pos.y
		<< " Scale: " << enemies[i].scale
		<< " Sprite: " << enemies[i].sprite
		<< " Health: " << enemies[i].health
		<< std::endl;
	for (int i = 0; i < players.size(); i++)
		std::cout << "Player: "
		<< " ID: " << players[i].ID
		<< " Pos: " << players[i].pos.x << " " << players[i].pos.y
		<< " Scale: " << players[i].scale
		<< " Sprite: " << players[i].sprite
		<< " Health: " << players[i].health
		<< " Name: " << players[i].name
		<< std::endl;
	std::cout << "------------------------" << std::endl;
}

Header& Game::getInfos()
{
	return (this->infos);
}
std::vector<Entity>& Game::getEntities()
{
	return (this->entities);
}
std::vector<Enemy>& Game::getEnemies()
{
	return (this->enemies);
}
std::vector<Player>& Game::getPlayers()
{
	return (this->players);
}