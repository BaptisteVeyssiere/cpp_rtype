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
struct Connect
{
	uint16_t structureHeader;
	int16_t room;
	char name[10];
	Connect();
	std::vector<char> getVector();
});