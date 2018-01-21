#pragma once

#include <cstdint>
#include <vector>
#include "Key.hpp"

#ifdef _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif _UNIX
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

PACK(
struct Inputs
{
	uint16_t structureHeader;
	int16_t x;
	int16_t y;
	Key inputs[8];
	Inputs();
	std::vector<char> getVector();
});