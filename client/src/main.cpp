#include "Game.hpp"

int main(int argc, char **argv)
{
	RType::Game	game;

	game.init();
	game.startGameLoop();
	game.terminate();
	return (0);
}