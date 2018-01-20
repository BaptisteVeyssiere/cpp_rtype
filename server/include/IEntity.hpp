#ifndef IENTITY_HPP_
# define IENTITY_HPP_

# include <string>
# include <memory>
# include <list>
# include "Type.hpp"
# include "Hitbox.hpp"
# include "Pos.hpp"

class IEntity
{
public:
	IEntity() {};
	virtual ~IEntity() {};

protected:
	Type		type;
	int			speed;
	int			id;
	int			hp;
	int			dying_time;
	std::string	name;
	std::string	sprite;
	Hitbox		hitbox;
	Pos			direction;


public:
	virtual std::unique_ptr<IEntity>	play(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept = 0;
	Type								getType() const noexcept;
	int									getID() const noexcept;
	void								setID(const int requested_id) noexcept;
	int									getHP() const noexcept;
	void								loseHP(const int damage) noexcept;
	std::string							getName() const noexcept;
	std::string							getSprite() const noexcept;
	Hitbox								getHitbox() const noexcept;
	void								setPos(const int x, const int y) noexcept;

protected:
	virtual std::unique_ptr<IEntity>	attack() noexcept = 0;
	virtual bool						die() noexcept = 0;
	virtual void						move(const std::list<std::unique_ptr<IEntity>> &entityList) noexcept = 0;
};

#endif // !IENTITY_HPP_