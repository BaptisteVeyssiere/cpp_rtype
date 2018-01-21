#include "Player.hpp"

Player::Player() : Enemy(), score(0)
{
	memset(sprite, 0, 10);
}

std::vector<char> Player::getVector()
{
	auto const ptr = reinterpret_cast<char*>(this);
	std::vector<char> buffer(ptr, ptr + sizeof(Player));
	return (buffer);
}