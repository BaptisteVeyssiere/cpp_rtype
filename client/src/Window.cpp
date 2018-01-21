#include "Window.hpp"
#include <SFML/Graphics.hpp>

TekEngine::Window::Window() {

}

TekEngine::Window::~Window() {

}

int	TekEngine::Window::createWindow(int width, int height, bool fullscreen, std::string title) {
	sf::VideoMode	mode;

	if (fullscreen)
		mode = sf::VideoMode::getFullscreenModes()[0];
	else
		mode = sf::VideoMode(width, height, 32);

	if ((win = new sf::RenderWindow(mode, title.c_str(), sf::Style::Close | sf::Style::Titlebar)) == nullptr)
		throw std::exception();
	win->setFramerateLimit(60);
	return (0);
}

void	TekEngine::Window::clear() {
	win->clear();
}

bool	TekEngine::Window::isOpen() {
	return (win->isOpen());
}

void	TekEngine::Window::refresh() {
	win->display();
}

void	TekEngine::Window::closeWindow(void) {
	win->close();
}

bool	TekEngine::Window::pollEvent(sf::Event &event) {
	return (win->pollEvent(event));
}

sf::RenderWindow	*TekEngine::Window::getWindow() {
	return (win);
}