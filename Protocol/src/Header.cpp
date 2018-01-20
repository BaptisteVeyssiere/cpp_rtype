#include "Header.hpp"

Header::Header()
{
	playersCount = enemyCount = entityCount = 0;
}

std::vector<char> Header::getVector()
{
	auto const ptr = reinterpret_cast<char*>(this);
	std::vector<char> buffer(ptr, ptr + sizeof(Header));
	return (buffer);
}