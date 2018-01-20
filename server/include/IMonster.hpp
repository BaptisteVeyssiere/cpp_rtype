#ifndef IMONSTER_HPP_
# define IMONSTER_HPP_

# include "IEntity.hpp"

class IMonster : public IEntity
{
public:
	IMonster() {};
	virtual ~IMonster() {};

protected:
	int	score;
	int	cooldown;
};

#endif // !IMONSTER_HPP_