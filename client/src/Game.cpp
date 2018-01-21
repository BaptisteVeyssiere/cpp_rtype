#include "Game.hpp"
#include "Layer.hpp"

RType::Game::Game() {

}

RType::Game::~Game() {

}

void RType::Game::init() {
	win.createWindow(1280, 720, false, "RType");
	gui.setWin(win.getWindow());
	menu.addButton("bouton.png", std::pair<int, int>(540, 600), std::pair<int, int>(200, 60), "test");
	menu.addButton("bouton.png", std::pair<int, int>(540, 500), std::pair<int, int>(200, 60), "test2");
	menu.addBackground("bg.jpg");
	subMenu.addButton("superbouton.png", std::pair<int, int>(540, 600), std::pair<int, int>(200, 60), "subtest");
	subMenu.addButton("superbouton.png", std::pair<int, int>(540, 500), std::pair<int, int>(200, 60), "subtest2");
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

	while (win.isOpen()) {
		win.clear();
		this->handleEvents();
		gui.refresh();
		win.refresh();
	}
}

void RType::Game::terminate() {

}