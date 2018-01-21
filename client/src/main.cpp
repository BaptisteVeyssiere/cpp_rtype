#include <iostream>
#include <vector>
#include "Game.hpp"

void test();

int main(int argc, char **argv)
{
	RType::Game	game;

	game.init();
	game.startGameLoop();
	game.terminate();
	test();
	while(1);
	return (0);
}