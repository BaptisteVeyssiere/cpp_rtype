#ifndef GAMECORE_HPP_
# define GAMECORE_HPP_

# include "IEntity.hpp"
# include "Timer.hpp"
# include "MonsterFactory.hpp"

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
public:


private:
	bool	checkCollision(const Hitbox &first, const Hitbox &second) const noexcept;
	void	addEntity(std::unique_ptr<IEntity> &entity) noexcept;
	void	play() noexcept;
	void	checkInteractions() noexcept;
	//void	getNetworkData(Header &header, std::vector<Players> &player, std::vector<Enemy> &enemy, std::vector<Entity> &entity) const noexcept;
	//void	feedInput(const Key &keys[10]) noexcept;
};

#endif // !GAMECORE_HPP_