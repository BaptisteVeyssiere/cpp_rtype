#include "Layer.hpp"
#include "Textures.hpp"

TekEngine::Layer::Layer() {
	if (!font.loadFromFile("resources/font/arial.ttf"))
		throw std::exception();
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

bool	TekEngine::Layer::findTextId(std::string id) {
	for (auto sprite : texts) {
		if (sprite->id == id)
			return (true);
	}
	return (false);
}

void	TekEngine::Layer::resetMask() {
	for (auto button : this->buttons) {
		button->sprite.setColor(sf::Color(255, 255, 255));
		button->text.setColor(sf::Color(255, 255, 255));
	}
}

std::string	TekEngine::Layer::applyHoverMask(sf::Vector2i pos) {
	for (auto button : this->buttons) {
		if (pos.x >= button->pos.first && pos.x < button->pos.first + button->size.first &&
			pos.y >= button->pos.second && pos.y < button->pos.second + button->size.second) {
			button->sprite.setColor(sf::Color(180, 180, 180));
			button->text.setColor(sf::Color(180, 180, 180));
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
		if (!button->text.getString().isEmpty())
			win.draw(button->text);
	}
	for (auto str : texts) {
		win.draw(str->text);
	}
}

void	TekEngine::Layer::addBackground(std::string textureName)
{
	sf::Vector2f				newSize;
	TekEngine::Textures			*textures = TekEngine::Textures::getInstance();

	textures->addTexture(textureName);
	if (!textures->findTextureById(textureName))
		throw std::exception();
	newSize.y = static_cast<float>(900) / textures->getTexture().getSize().y;
	newSize.x = static_cast<float>(1600) / textures->getTexture().getSize().x;
	background.setTexture(textures->getTexture());
	background.setScale(newSize);
	back = true;
}

void	TekEngine::Layer::addButton(std::string textureName, std::pair<int, int> pos, std::pair<int, int> size, std::string id) {
	TekEngine::Layer::Button	*button = new TekEngine::Layer::Button;
	sf::Vector2f				newSize;
	sf::Vector2f				textPos;
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
	button->text.setFont(font);
	button->text.setString("");
	button->text.setCharacterSize(24);
	button->text.setFillColor(sf::Color::White);
	buttons.push_back(button);
}

void		TekEngine::Layer::setButtonText(std::string id, std::string text, int size, sf::Color col) {
	sf::Vector2f	textPos;
	
	for (auto button : buttons) {
		if (button->id == id) {
			button->text.setString(text);
			button->text.setCharacterSize(size);
			button->text.setColor(col);
			textPos.y = button->pos.second + (button->size.second / 2) - (button->text.getCharacterSize() / 1.5);
			textPos.x = button->pos.first + (button->size.first / 2) - (button->text.getGlobalBounds().width / 2);
			button->text.setPosition(textPos);
		}
	}
}

void		TekEngine::Layer::setText(std::string id, std::string str, int size, sf::Color col) {
	for (auto text : texts) {
		if (text->id == id) {
			text->text.setString(str);
			text->text.setCharacterSize(size);
			text->text.setColor(col);
		}
	}
}

void		TekEngine::Layer::addText(std::string id, std::string text, std::pair<int, int> pos, int size) {
	TekEngine::Layer::Text	*tmp = new TekEngine::Layer::Text;

	if (this->findTextId(id))
		throw std::exception();
	tmp->id = id;
	tmp->text.setFont(font);
	tmp->text.setString(text);
	tmp->text.setPosition(sf::Vector2f(pos.first, pos.second));
	tmp->text.setCharacterSize(size);
	tmp->text.setColor(sf::Color::White);
	texts.push_back(tmp);
}