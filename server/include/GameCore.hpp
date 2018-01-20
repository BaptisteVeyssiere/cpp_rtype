#ifndef GAMECORE_HPP_
# define GAMECORE_HPP_

# include "IEntity.hpp"
# include "Timer.hpp"
# include "MonsterFactory.hpp"

class GameCore
{
public:
	GameCore(const int player_nbr);
	~GameCore();

private:
	Timer								updateAlarm;
	Timer								patternAlarm;
	std::list<std::unique_ptr<IEntity>>	entityList;
	MonsterFactory						monsterFactory;
public:


private:
	bool	checkCollision(const Hitbox &first, const Hitbox &second) const noexcept;
	void	addEntity(std::unique_ptr<IEntity> &entity) noexcept;
	void	play() noexcept;
	void	getNetworkData(Header &header, std::vector<Players> &player, std::vector<Enemy> &enemy, std::vector<Entity> &entity) const noexcept;
};

#endif // !GAMECORE_HPP_