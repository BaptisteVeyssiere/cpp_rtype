#ifndef GAMECORE_HPP_
# define GAMECORE_HPP_

# include "IEntity.hpp"
# include "Timer.hpp"
# include "MonsterFactory.hpp"
#include "Protocol.hpp"

class GameCore
{
public:
	GameCore(const int player_nbr, const std::vector<std::string> &name);
	~GameCore();

private:
	Timer								updateAlarm;
	Timer								FrameAlarm;
	std::list<std::unique_ptr<IEntity>>	entityList;
	MonsterFactory						monsterFactory;
	std::unordered_map<Key, bool>		inputs;
public:
	void	play() noexcept;
	void	getNetworkData(std::shared_ptr<Header> &head, std::vector<std::shared_ptr<Entity>> &entities,
		std::vector<std::shared_ptr<Enemy>>	&enemies, std::vector<std::shared_ptr<Player>> &players) const noexcept;
	void	feedInput(const int id, const Inputs &inputs) noexcept;

private:
	bool	checkCollision(const Hitbox &first, const Hitbox &second) const noexcept;
	void	addEntity(std::unique_ptr<IEntity> &entity) noexcept;
	void	checkInteractions() noexcept;
};

#endif // !GAMECORE_HPP_