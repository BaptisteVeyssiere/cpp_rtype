#pragma once

#include <cstdint>
#include "Enemy.hpp"

#ifdef _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif _UNIX
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

PACK(
struct Player : Enemy
{
	char name[10];
	uint16_t score;
	Player();
	std::vector<char> getVector();
});