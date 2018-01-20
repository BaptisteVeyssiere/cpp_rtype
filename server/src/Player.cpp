#include "Player.hpp"

Player::Player(const int playerId, const std::string &playerName)
{
	this->type = Type::PLAYER;
	this->speed = 2;
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
	this->hitbox.y = 20 + playerId * 400;
	this->hitbox.width = 100;
	this->hitbox.height = 50;
}

Player::~Player()
{

}

bool	Player::die() noexcept
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

void	Player::move(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept
{
	int	x = this->hitbox.x + this->direction.x * this->speed;
	int	y = this->hitbox.y + this->direction.y * this->speed;

	if (x >= 0 && x < 10000)
		this->hitbox.x += (this->direction.x * this->speed);
	if (y >= 20 && y < 10000)
		this->hitbox.y += (this->direction.y * this->speed);
}

std::unique_ptr<IEntity>	Player::attack() noexcept
{
	if (this->cooldown == 0)
	{
		this->cooldown = 20;
		return (std::make_unique<PlayerMissile>(this->hitbox.x, this->hitbox.y, this->direction));
	}
	--(this->cooldown);
	return (nullptr);
}

void		Player::changeDirection(const int x, const int y) noexcept
{
	this->direction.x = x;
	this->direction.y = y;
}

std::unique_ptr<IEntity>	Player::play(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept
{
	if (this->getHP() <= 0)
		this->die();
	else
	{
		this->move(entityList);
		//if (this->input[FIRE] == true)
		//	return (this->attack());
	}
	return (nullptr);
}

void	Player::inputHandler() noexcept
{

}

