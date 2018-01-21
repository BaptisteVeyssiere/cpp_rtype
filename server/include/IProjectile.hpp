#ifndef IPROJECTILE_HPP_
# define IPROJECTILE_HPP_

# include "IEntity.hpp"

class IProjectile : public IEntity
{
public:
	IProjectile() {};
	virtual ~IProjectile() {};

public:
	virtual int	getDamage() const noexcept;
	virtual int getOwner() const noexcept;

protected:
	int	damage;
	int	owner;
};

#endif // !IPROJECTILE_HPP_