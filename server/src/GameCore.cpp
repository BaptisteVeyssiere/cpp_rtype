#include "GameCore.hpp"

GameCore::GameCore(const int player_nbr)
	: updateAlarm(), patternAlarm(), entityList()
{
	this->updateAlarm.setAlarm(30000);
	this->patternAlarm.setAlarm(10000);
	// Add [player nbr] players
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

void	GameCore::play() noexcept
{
	if (this->updateAlarm.checkAlarm())
	{
		this->monsterFactory.updateLibraries();
		this->updateAlarm.setAlarm(30000);
	}
	for (auto iterator = this->entityList.begin(); iterator != this->entityList.end(); ++iterator) {
		(*iterator)->play(this->entityList);
		// Get hitbox
		// Loop with all other hitbox to check collisions
		// if collision then if only one is player lose one hp
		// elsif one is projectile destroy other
		// else nothing
		// All new projectile are stocked in tmp
	}
	// Set all new ID
	// Add tmp to entity list
}