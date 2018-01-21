#include "GameCore.hpp"
#include "IProjectile.hpp"
#include "Player.hpp"

GameCore::GameCore(const int player_nbr, const std::vector<std::string> &name)
	: updateAlarm(), FrameAlarm(), entityList()
{
	this->updateAlarm.setAlarm(30000);
	this->FrameAlarm.setAlarm(16);
	for (unsigned int i = 0; i < player_nbr; ++i)
		this->entityList.push_back(std::make_unique<Player>(i, name[i]));
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
/*
void	GameCore::getNetworkData(Header &header, std::vector<Players> &player, std::vector<Enemy> &enemy, std::vector<Entity> &entity) const noexcept
{

}

void	GameCore::feedInput(const int id, const Key &keys[10]) noexcept
{
	for (auto entity : this->entityList)
	{
		if (entity->getID() == id && this->getType() == Type::PLAYER)
		{
			this->inputs["FIRE"] = false;
			this->inputs["CHARGING"] = false;
			for (auto key : keys)
			{
				if (key == Key::FIRE)
					this->inputs["FIRE"] = true;
				else if (key == Key::CHARGING)
					this->inputs["CHARGING"] = true;
			}
		}
	}
}
*/