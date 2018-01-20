#include "IEntity.hpp"

Type	IEntity::getType() const noexcept
{
	return (this->type);
}

int		IEntity::getID() const noexcept
{
	return (this->id);
}

void	IEntity::setID(const int requested_id) noexcept
{
	this->id = requested_id;
}

int		IEntity::getHP() const noexcept
{
	return (this->hp);
}

void	IEntity::loseHP(const int damage) noexcept
{
	this->hp -= damage;
}

std::string		IEntity::getName() const noexcept
{
	return (this->name);
}

std::string		IEntity::getSprite() const noexcept
{
	return (this->sprite);
}

Hitbox	IEntity::getHitbox() const noexcept
{
	return (this->hitbox);
}

void	IEntity::setPos(const int x, const int y) noexcept
{
	this->hitbox.x = x;
	this->hitbox.y = y;
}