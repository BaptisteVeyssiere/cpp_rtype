#include <iostream>
#include <vector>
#include "GameData.hpp"

void test()
{
	GameData infos;

	ClientEntity *entity = new ClientEntity();
	ClientEntity entity2;
	ClientEnemy *enemy = new ClientEnemy();
	ClientPlayer *player = new ClientPlayer();
	//initialisation entity
	entity->ID = 10;
	entity->pos.x = 2;
	entity->pos.y = 5;
	entity->scale = 100;
	strcpy(entity->sprite, "entity");
	//initialisation entity
	entity2.ID = 10;
	entity2.pos.x = 2;
	entity2.pos.y = 5;
	entity2.scale = 100;
	strcpy(entity2.sprite, "entity");
	//initialisation enemy
	enemy->ID = 11;
	enemy->pos.x = 3;
	enemy->pos.y = 6;
	enemy->scale = 101;
	enemy->health = 4;
	strcpy(enemy->sprite, "enemy");
	//initialisation player
	player->ID = 12;
	player->pos.x = 4;
	player->pos.y = 7;
	player->scale = 102;
	player->health = 5;
	strcpy(player->sprite, "player");
	strcpy(player->name, "balou");
	//putting structs in vectors
	infos.getEntities().push_back(*entity);
	infos.getEntities().push_back(entity2);
	infos.getEnemies().push_back(*enemy);
	infos.getPlayers().push_back(*player);
	infos.display();
	std::vector<char> buff = infos.getVector();
	for (int i = 0; i < buff.size(); i++)
		std::cout << buff[i];
	std::cout << std::endl;
	GameData tmp;
	std::cout << "--------------" << std::endl;
	tmp.getInfosFromServer(buff);
	tmp.display();
}