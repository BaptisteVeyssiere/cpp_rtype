#include "Humain.hpp"

Humain::Humain(const int playerId, const std::string &playerName)
{
	this->type = Type::PLAYER;
	this->speed = 10;
	this->id = playerId;
	this->dying_time = -1;
	this->name = playerName;
	this->hp = 3;
	this->cooldown = 0;
	this->score = 0;
	this->direction.x = 1;
	this->direction.y = 0;
	this->sprite = "player" + playerId;
	this->hitbox.x = 0;
	this->hitbox.y = 1000 + playerId * 2000;
	this->hitbox.width = 775;
	this->hitbox.height = 1000;
}

Humain::~Humain()
{

}

bool	Humain::die() noexcept
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

void	Humain::move(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept
{
	int	x = this->hitbox.x + this->direction.x * this->speed;
	int	y = this->hitbox.y + this->direction.y * this->speed;

	if (x >= 0 && x < 10000)
		this->hitbox.x = x;
	if (y >= 20 && y < 9980)
		this->hitbox.y = y;
}

std::unique_ptr<IEntity>	Humain::attack() noexcept
{
	if (this->cooldown == 0)
	{
		this->cooldown = 20;
		return (std::make_unique<PlayerMissile>(this->hitbox.x, this->hitbox.y, this->direction, this->id));
	}
	--(this->cooldown);
	return (nullptr);
}

void		Humain::changeDirection(const int x, const int y) noexcept
{
	this->direction.x = x;
	this->direction.y = y;
}

std::unique_ptr<IEntity>	Humain::play(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept
{
	if (this->getHP() <= 0)
		this->die();
	else
	{
		this->move(entityList);
		/*
		if (this->input[FIRE] == true)
			return (this->attack());
		if (this->input[CHARGING] == true)
			return (this->attack());
			*/
	}
	return (nullptr);
}

void	Humain::inputHandler() noexcept
{

}

