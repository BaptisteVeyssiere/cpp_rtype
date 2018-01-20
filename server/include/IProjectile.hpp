#ifndef IPROJECTILE_HPP_
# define IPROECTILE_HPP_

# include "IEntity.hpp"

class IProjectile : public IEntity
{
public:
	IProjectile() {};
	virtual ~IProjectile() {};

protected:
	int	damage;
	int	owner;
};

#endif // !IPROJECTILE_HPP_