#include "Game.hpp"
#include <SFML/Audio.hpp>
#include "Layer.hpp"
#include <vector>
#include <time.h>

RType::Game::Game()
{

}

RType::Game::~Game() {

}

void RType::Game::init() {
	win.createWindow(1600, 900, false, "RType");
	gui.setWin(win.getWindow());
	if (!music.openFromFile("resources/sound/bgm.ogg"))
		throw std::exception();
	music.play();
	music.setVolume(10);
	music.setLoop(true);
	menu.addButton("bouton.png", std::pair<int, int>(700, 700), std::pair<int, int>(200, 60), "test");
	menu.addButton("bouton.png", std::pair<int, int>(700, 600), std::pair<int, int>(200, 60), "test2");
	menu.addText("RTYPE", "R-Type", std::pair<int, int>(800, 100), 70);
	menu.setButtonText("test", "Quitter", 35);
	menu.setButtonText("test2", "Options", 35);
	menu.addBackground("bg.jpg");
	subMenu.addButton("superbouton.png", std::pair<int, int>(700, 700), std::pair<int, int>(200, 60), "subtest");
	subMenu.addButton("superbouton.png", std::pair<int, int>(700, 600), std::pair<int, int>(200, 60), "subtest2");
	subMenu.setButtonText("subtest", "Retour", 35);
	gui.addLayer(&menu);
	gui.setDisplay(true);
}

void	RType::Game::handleEvents() {
	sf::Event	event;

	while (win.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			win.closeWindow();
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (gui.mouseClick() == "test")
					win.closeWindow();
				else if (gui.mouseClick() == "test2")
					gui.addLayer(&subMenu);
				else if (gui.mouseClick() == "subtest")
					gui.removeLayer();
			}
		}
	}
}

void RType::Game::startGameLoop() {
	std::clock_t	c = clock();
	sf::Color		color;
	int				i = 0;

	this->socketInitialise("127.0.0.1", 4567);
	while (win.isOpen()) {
		this->sendData();
		data.display();
		win.clear();
		this->handleEvents();
		if (++i % 3 == 0) {
			c = clock() - c;
			menu.setText("RTYPE", std::to_string(static_cast<int>(3 / ((float)c / CLOCKS_PER_SEC))), 150, color);
			color.r = i % 255;
			color.g = i * 2 % 255;
			color.b = i / 2 % 255;
			c = clock();
		}
		gui.refresh();
		win.refresh();
		this->receiveData();
	}
}

void RType::Game::socketInitialise(std::string ip, int port)
{
	socket.registerAddress(ip);
	socket.registerPort(port);
	socket.prepareToConnect();
}

void RType::Game::sendData()
{
	socket.sendRequest(data.getVector());
}

void RType::Game::receiveData()
{
	unsigned int size;
	std::vector<char> buffer;
	socket.receiveRequest(buffer, size);
	data.emptyLists();
	data.getInfosFromServer(buffer);
}

void RType::Game::terminate() {

}