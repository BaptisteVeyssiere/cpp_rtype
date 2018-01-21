#include "Game.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	Game infos;

	Entity *entity = new Entity();
	Entity entity2;
	Enemy *enemy = new Enemy();
	Player *player = new Player();
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
	Game tmp;
	std::cout << "--------------" << std::endl;
	tmp.getInfosFromServer(buff);
	tmp.display();
	/*Header* head = reinterpret_cast<Header*>(&buff[0]);*/
	/*std::cout << head->entityCount << " "
		<< head->enemyCount << " "
		<< head->playersCount << std::endl;*/
	while(1);
	return (0);
}