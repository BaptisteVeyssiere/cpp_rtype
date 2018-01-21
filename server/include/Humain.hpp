#ifndef HUMAIN_HPP_
# define HUMAIN_HPP_

# include "PlayerMissile.hpp"

class Humain : public IEntity
{
public:
	Humain(const int playerId, const std::string &playerName);
	~Humain();

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

#endif // !HUMAIN_HPP_