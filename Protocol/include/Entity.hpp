#pragma once

#include <cstdint>
#include <vector>
#include "Pos.hpp"

#ifdef _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif _UNIX
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

PACK(
struct Entity
{
	uint16_t ID;
	Pos		pos;
	char	sprite[32];
	uint16_t scale;
	Entity();
	std::vector<char> getVector();
});