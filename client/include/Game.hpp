#ifndef GAME_HPP__
# define GAME_HPP__

#include "Window.hpp"
#include "Textures.hpp"
#include "Gui.hpp"
#include "Layer.hpp"

namespace RType
{
	class Game {
	private:
		TekEngine::Window	win;
		TekEngine::Gui		gui;
		TekEngine::Layer	menu;
		TekEngine::Layer	subMenu;

	public:
		Game();
		~Game();

	private:
		Game(Game &other);
		Game	operator=(Game &other);

	private:
		void	handleEvents();

	public:
		void	init();
		void	startGameLoop();
		void	terminate();
	};
}

#endif //GAME_HPP__