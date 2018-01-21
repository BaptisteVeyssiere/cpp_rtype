#include "IProjectile.hpp"

int	IProjectile::getDamage() const noexcept
{
	return (this->damage);
}

int	IProjectile::getOwner() const noexcept
{
	return (this->owner);
}