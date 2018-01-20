#ifndef PLAYERMISSILE_HPP_
# define PLAYERMISSILE_HPP_

# include "IProjectile.hpp"

class PlayerMissile : public IProjectile
{
public:
	PlayerMissile(const int x, const int y, const Pos &direction);
	~PlayerMissile();

public:
	std::unique_ptr<IEntity>	play(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept;

private:
	std::unique_ptr<IEntity>	attack() noexcept;
	bool						die() noexcept;
	void						move(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept;
};

#endif // !PLAYERMISSILE_HPP_