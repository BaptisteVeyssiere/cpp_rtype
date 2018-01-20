#include "PlayerMissile.hpp"

PlayerMissile::PlayerMissile(const int x, const int y, const Pos &direction)
{
	this->type = Type::PROJECTILE;
	this->speed = 3;
	this->dying_time = -1;
	this->name = "playerMissile";
	this->hp = 1;
	this->sprite = "playerMissile";
	this->hitbox.x = x;
	this->hitbox.y = y;
	this->hitbox.width = 50;
	this->hitbox.height = 10;
	this->direction.x = direction.x == 0 ? 1 : direction.x;
	this->direction.y = 0;
}

PlayerMissile::~PlayerMissile()
{

}

std::unique_ptr<IEntity>	PlayerMissile::play(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept
{
	this->move(entityList);
	return (nullptr);
}

std::unique_ptr<IEntity>	PlayerMissile::attack() noexcept
{
	return (nullptr);
}

bool						PlayerMissile::die() noexcept
{
	if (this->dying_time < 0)
	{
		this->dying_time = 5;
		return (false);
	}
	else if (this->dying_time == 0)
		return (true);
	else
		--(this->dying_time);
	return (false);
}

void						PlayerMissile::move(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept
{
	int	x = this->hitbox.x + this->direction.x * this->speed;
	int	y = this->hitbox.y + this->direction.y * this->speed;

	if (x >= 0 && x < 10000)
		this->hitbox.x += (this->direction.x * this->speed);
	if (y >= 20 && y < 10000)
		this->hitbox.y += (this->direction.y * this->speed);
}