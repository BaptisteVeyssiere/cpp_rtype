#include "Entity.hpp"
#include <string.h>

Entity::Entity() : ID(0), pos{0,0}, scale(100)
{
	memset(sprite, 0, 32);
}

std::vector<char> Entity::getVector()
{
	auto const ptr = reinterpret_cast<char*>(this);
	std::vector<char> buffer(ptr, ptr + sizeof(Entity));
	return (buffer);
}