#pragma once

#include "Enemy.hpp"

#ifdef _WIN32
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#elif _UNIX
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

PACK(
struct ClientEnemy : Enemy
{
	int mdr;
	ClientEnemy() : mdr(0)
	{}
});