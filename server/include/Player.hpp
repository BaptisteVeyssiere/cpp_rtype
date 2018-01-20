#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include "PlayerMissile.hpp"

class Player : public IEntity
{
public:
	Player(const int playerId, const std::string &playerName);
	~Player();

private:
	int	cooldown;
	int score;

public:
	std::unique_ptr<IEntity>	play(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept;
	void						changeDirection(const int x, const int y) noexcept;
	void						inputHandler() noexcept;

private:
	std::unique_ptr<IEntity>	attack() noexcept;
	bool						die() noexcept;
	void						move(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept;
};

#endif // !PLAYER_HPP_