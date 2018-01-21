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
	menu.addButton("bouton.png", std::pair<int, int>(700, 500), std::pair<int, int>(200, 60), "jouer");
	menu.addButton("bouton.png", std::pair<int, int>(700, 700), std::pair<int, int>(200, 60), "test");
	menu.addButton("bouton.png", std::pair<int, int>(700, 600), std::pair<int, int>(200, 60), "test2");
	menu.addText("RTYPE", "R-Type", std::pair<int, int>(800, 100), 70);
	menu.setButtonText("test", "Quitter", 35);
	menu.setButtonText("test2", "Options", 35);
	menu.setButtonText("jouer", "Jouer", 50);
	menu.addBackground("bg.jpg");
	subMenu.addButton("superbouton.png", std::pair<int, int>(700, 700), std::pair<int, int>(200, 60), "subtest");
	subMenu.addButton("superbouton.png", std::pair<int, int>(700, 600), std::pair<int, int>(200, 60), "subtest2");
	subMenu.setButtonText("subtest", "Retour", 35);
	sprite.setSprite("bullet.png", 2, 81, 16);
	sprite.setScale(10);
	sprite.setAnimSpeed(0.05);
	sprite.setPosition(std::pair<int, int>(200, 200));
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
				else if (gui.mouseClick() == "jouer")
					gui.setDisplay(false);
			}
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				gui.setDisplay(true);
			}
		}
	}
}

void	RType::Game::displaySprites() {
	TekEngine::Sprite	*sprite;

	auto players = data.getPlayers();
	auto entities = data.getEntities();

	sprite = new TekEngine::Sprite;

	sprite->setSprite("fond.png", 1, 1600, 900);
	win.getWindow()->draw(sprite->getSprite());
	delete sprite;
	for (auto object : players) {
		sprite = new TekEngine::Sprite;
		sprite->setSprite(object.sprite, 1, 124, 90);
		sprite->setScale(static_cast<float>(object.scale) / 100.0);
		sprite->setPosition(std::pair<int, int>(static_cast<float>(object.pos.y) / 10000.0 * 900.0, static_cast<float>(object.pos.x) / 10000.0 * 1600.0));
		sprite->setMask(sf::Color(255, 255, 0));
		win.getWindow()->draw(sprite->getSprite());
		delete sprite;
	}

	this->socketInitialise("127.0.0.1", 57342);
	for (auto object : entities) {
		sprite = new TekEngine::Sprite;
		sprite->setSprite(object.sprite, 2, 81, 16);
		sprite->setScale(static_cast<float>(object.scale) / 100.0);
		sprite->setPosition(std::pair<int, int>(static_cast<float>(object.pos.y) / 10000.0 * 900.0, static_cast<float>(object.pos.x) / 10000.0 * 1600.0));
		win.getWindow()->draw(sprite->getSprite());
		delete sprite;
	}
}

void RType::Game::startGameLoop() {
	while (win.isOpen()) {
		this->sendData();
		data.display();
		win.clear();
		this->handleEvents();
		this->displaySprites();
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