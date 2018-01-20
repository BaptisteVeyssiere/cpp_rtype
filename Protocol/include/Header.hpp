#pragma once

#include <cstdint>
#include <string.h>
#include <vector>

#ifdef _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif _UNIX
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

PACK(
struct Header
{
	uint16_t playersCount;
	uint16_t enemyCount;
	uint16_t entityCount;
	//bool other informations
	Header();
	std::vector<char> getVector();
});