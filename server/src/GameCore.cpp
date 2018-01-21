#include <cstring>
#include "GameCore.hpp"
#include "IProjectile.hpp"
#include "Player.hpp"
#include "Humain.hpp"

GameCore::GameCore(const int player_nbr, const std::vector<std::string> &name)
	: updateAlarm(), FrameAlarm(), entityList()
{
	this->updateAlarm.setAlarm(30000);
	this->FrameAlarm.setAlarm(16);
	this->inputs[Key::FIRE] = false;
	this->inputs[Key::CHARGING] = false;
	for (unsigned int i = 0; i < player_nbr; ++i)
		this->entityList.push_back(std::move(std::make_unique<Humain>(i, name[i])));
}

GameCore::~GameCore()
{

}

bool	GameCore::checkCollision(const Hitbox &first, const Hitbox &second) const noexcept
{
	if ((second.x >= first.x + first.width) ||
		(second.x + second.width <= first.x) ||
		(second.y >= first.y + first.height) ||
		(second.y + second.height <= first.y))
		return (false);
	return (true);
}

void	GameCore::addEntity(std::unique_ptr<IEntity> &entity) noexcept
{
	this->entityList.push_back(std::move(entity));
}

void	GameCore::checkInteractions() noexcept
{
	for (auto iterator = this->entityList.begin(); iterator != this->entityList.end(); ++iterator)
	{
		for (auto tmp = std::next(iterator, 1); tmp != this->entityList.end(); ++tmp)
		{
			if (this->checkCollision((*tmp)->getHitbox(), (*iterator)->getHitbox()) == true)
			{
				if ((*tmp)->getType() == Type::PLAYER && (*tmp)->getHP() > 0)
				{
					if ((*iterator)->getType() == Type::MONSTER && (*iterator)->getHP() > 0)
					{
						(*iterator)->loseHP(1);
						(*tmp)->loseHP(1);
					}
					if ((*iterator)->getType() == Type::PROJECTILE && dynamic_cast<IProjectile*>(((*iterator)).get())->getOwner() > 3 && (*iterator)->getHP() > 0)
					{
						(*iterator)->loseHP((*iterator)->getHP());
						(*tmp)->loseHP(dynamic_cast<IProjectile*>(((*iterator)).get())->getDamage());
					}
				}
				if ((*tmp)->getType() == Type::MONSTER && (*tmp)->getHP() > 0)
				{
					if ((*iterator)->getType() == Type::PLAYER && (*iterator)->getHP() > 0)
					{
						(*iterator)->loseHP(1);
						(*tmp)->loseHP(1);
					}
					if ((*iterator)->getType() == Type::PROJECTILE && dynamic_cast<IProjectile*>(((*iterator)).get())->getOwner() <= 3 && (*iterator)->getHP() > 0)
					{
						(*iterator)->loseHP((*iterator)->getHP());
						(*tmp)->loseHP(dynamic_cast<IProjectile*>(((*iterator)).get())->getDamage());
					}
				}
				if (((*tmp)->getType() == Type::PROJECTILE) &&
					(((*iterator)->getType() == Type::MONSTER && dynamic_cast<IProjectile*>(((*tmp)).get())->getOwner() <= 3 && (*tmp)->getHP() > 0 && (*iterator)->getHP() > 0) ||
					((*iterator)->getType() == Type::PLAYER && dynamic_cast<IProjectile*>(((*tmp)).get())->getOwner() > 3 && (*tmp)->getHP() > 0 && (*iterator)->getHP() > 0)))
				{
					(*tmp)->loseHP((*tmp)->getHP());
					(*iterator)->loseHP(dynamic_cast<IProjectile*>(((*tmp)).get())->getDamage());
				}
			}
		}
	}
}

void	GameCore::play() noexcept
{
	if (this->updateAlarm.checkAlarm())
	{
		this->monsterFactory.updateLibraries();
		this->updateAlarm.setAlarm(30000);
	}
	if (this->FrameAlarm.checkAlarm())
	{
		for (auto iterator = this->entityList.begin(); iterator != this->entityList.end(); )
		{
			if ((*iterator)->isDead())
				iterator = this->entityList.erase(iterator);
			else
				++iterator;
		}
		std::vector<std::unique_ptr<IEntity>>	newEntities;
		for (auto iterator = this->entityList.begin(); iterator != this->entityList.end(); ++iterator)
		{
			newEntities.push_back((*iterator)->play(this->entityList));
			if (newEntities[newEntities.size() - 1] == nullptr)
				newEntities.pop_back();
		}
		this->checkInteractions();
		for (int i = 0; i < newEntities.size(); ++i)
			newEntities[i]->setID(this->monsterFactory.pickID());
		this->entityList.insert(this->entityList.end(), std::make_move_iterator(newEntities.begin()), std::make_move_iterator(newEntities.end()));
		this->FrameAlarm.setAlarm(16);
	}
}

void	GameCore::getNetworkData(std::shared_ptr<Header> &head, std::vector<std::shared_ptr<Entity>> &entities, 
	std::vector<std::shared_ptr<Enemy>>	&enemies, std::vector<std::shared_ptr<Player>> &players) const noexcept
{
	head = std::make_shared<Header>();
	head->enemyCount = 0;
	head->entityCount = 0;
	head->playersCount = 0;
	int index;
	for (auto &entity : this->entityList)
	{
		if (entity->getType() == Type::PLAYER)
		{
			++(head->playersCount);
			players.push_back(std::make_shared<Player>());
			index = players.size() - 1;
			players[index]->ID = entity->getID();
			players[index]->pos.x = entity->getHitbox().x;
			players[index]->pos.y = entity->getHitbox().y;
			std::strcpy(players[index]->sprite, entity->getSprite().c_str());
			players[index]->scale = 1;
			players[index]->health = entity->getHP();
			std::strcpy(players[index]->name, entity->getName().c_str());
			players[index]->score = 0;
		}
		else if (entity->getType() == Type::MONSTER)
		{
			++(head->enemyCount);
			enemies.push_back(std::make_shared<Enemy>());
			index = enemies.size() - 1;
			enemies[index]->ID = entity->getID();
			enemies[index]->pos.x = entity->getHitbox().x;
			enemies[index]->pos.y = entity->getHitbox().y;
			std::strcpy(enemies[index]->sprite, entity->getSprite().c_str());
			enemies[index]->scale = 1;
			enemies[index]->health = entity->getHP();
		}
		else
		{
			++(head->entityCount);
			entities.push_back(std::make_shared<Entity>());
			index = entities.size() - 1;
			entities[index]->ID = entity->getID();
			entities[index]->pos.x = entity->getHitbox().x;
			entities[index]->pos.y = entity->getHitbox().y;
			std::strcpy(entities[index]->sprite, entity->getSprite().c_str());
			entities[index]->scale = 1;
		}
	}
}

void	GameCore::feedInput(const int id, const Inputs &input) noexcept
{
	for (auto &entity : this->entityList)
	{
		if (entity->getID() == id && entity->getType() == Type::PLAYER)
		{
			entity->setPos(input.x, input.y);
			this->inputs[Key::FIRE] = false;
			this->inputs[Key::CHARGING] = false;
			for (auto key : input.inputs)
				if (this->inputs.find(key) != this->inputs.end())
					this->inputs[key] = true;
		}
	}
}
