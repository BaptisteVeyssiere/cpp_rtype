#include "Enemy.hpp"

Enemy::Enemy() : Entity(), health(0)
{
}

std::vector<char> Enemy::getVector()
{
	auto const ptr = reinterpret_cast<char*>(this);
	std::vector<char> buffer(ptr, ptr + sizeof(Enemy));
	return (buffer);
}