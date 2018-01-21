#ifndef GAME_HPP__
# define GAME_HPP__

#include "Window.hpp"
#include "Textures.hpp"
#include "Gui.hpp"
#include "Layer.hpp"
#include <SFML/Audio.hpp>
#include "AsioSocket.hpp"
#include "GameData.hpp"
#include <string>

namespace RType
{
	class Game {
	private:
		AsioSocket			socket;
		TekEngine::Window	win;
		TekEngine::Gui		gui;
		TekEngine::Layer	menu;
		TekEngine::Layer	subMenu;
		sf::Music			music;
		GameData			data;

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

	public:
		void	socketInitialise(std::string ip = "127.0.0.1", int port = 4242);

	public:
		void	sendData();
		void	receiveData();
	};
}

#endif //GAME_HPP__