#include "Gui.hpp"

TekEngine::Gui::Gui()
{

}

TekEngine::Gui::~Gui()
{

}

void	TekEngine::Gui::setWin(sf::RenderWindow *win) {
	this->win = win;
}

void	TekEngine::Gui::setDisplay(bool display) {
	this->display = display;
}

void	TekEngine::Gui::addLayer(TekEngine::Layer *layer) {
	layers.push(layer);
}

void	TekEngine::Gui::removeLayer() {
	layers.pop();
}

std::string	TekEngine::Gui::checkMouse() {
	sf::Vector2i pos = sf::Mouse::getPosition(*win);

	layers.top()->resetMask();
	return (layers.top()->applyHoverMask(pos));
}

std::string	TekEngine::Gui::mouseClick() {
	return (checkMouse());
}

void	TekEngine::Gui::refresh() {
	if (display) {
		checkMouse();
		layers.top()->DrawLayer(*win);
	}
}