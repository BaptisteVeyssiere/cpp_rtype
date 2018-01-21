#include "Layer.hpp"
#include "Textures.hpp"

TekEngine::Layer::Layer() {

}

TekEngine::Layer::~Layer() {

}

bool	TekEngine::Layer::findButtonId(std::string id) {
	for (auto sprite : buttons) {
		if (sprite->id == id)
			return (true);
	}
	return (false);
}

void	TekEngine::Layer::resetMask() {
	for (auto button : this->buttons) {
		button->sprite.setColor(sf::Color(255, 255, 255));
	}
}

std::string	TekEngine::Layer::applyHoverMask(sf::Vector2i pos) {
	for (auto button : this->buttons) {
		if (pos.x >= button->pos.first && pos.x < button->pos.first + button->size.first &&
			pos.y >= button->pos.second && pos.y < button->pos.second + button->size.second) {
			button->sprite.setColor(sf::Color(180, 180, 180));
			return (button->id);
		}
	}
	return ("");
}

void	TekEngine::Layer::DrawLayer(sf::RenderWindow &win) {
	if (back)
		win.draw(background);
	for (auto button : buttons) {
		win.draw(button->sprite);
	}
}

void	TekEngine::Layer::addBackground(std::string textureName)
{
	sf::Vector2f				newSize;
	TekEngine::Textures			*textures = TekEngine::Textures::getInstance();

	textures->addTexture(textureName);
	if (!textures->findTextureById(textureName))
		throw std::exception();
	newSize.y = static_cast<float>(720) / textures->getTexture().getSize().y;
	newSize.x = static_cast<float>(1280) / textures->getTexture().getSize().x;
	background.setTexture(textures->getTexture());
	background.setScale(newSize);
	back = true;
}

void	TekEngine::Layer::addButton(std::string textureName, std::pair<int, int> pos, std::pair<int, int> size, std::string id) {
	TekEngine::Layer::Button	*button = new TekEngine::Layer::Button;
	sf::Vector2f				newSize;
	TekEngine::Textures			*textures = TekEngine::Textures::getInstance();

	textures->addTexture(textureName);
	if (!textures->findTextureById(textureName))
		throw std::exception();
	if (this->findButtonId(id))
		throw std::exception();
	button->id = id;
	button->pos = pos;
	newSize.y = static_cast<float>(size.second) / textures->getTexture().getSize().y;
	newSize.x = static_cast<float>(size.first) / textures->getTexture().getSize().x;
	button->sprite.setTexture(textures->getTexture());
	button->sprite.setScale(newSize);
	button->sprite.setPosition(sf::Vector2f(pos.first, pos.second));
	button->size.first = size.first;
	button->size.second = size.second;
	buttons.push_back(button);
}