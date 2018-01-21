#include "Sprite.hpp"
#include "Textures.hpp"

TekEngine::Sprite::Sprite() {
	this->clock = std::clock();
}

TekEngine::Sprite::~Sprite() {

}

sf::Sprite	TekEngine::Sprite::getSprite() {
	return (this->modele);
}	

void	TekEngine::Sprite::setSprite(std::string path, int spriteNbr, int spriteWidth, int spriteHeight) {
	TekEngine::Textures	*textures = TekEngine::Textures::getInstance();

	textures->addTexture(path);
	if (!textures->findTextureById(path))
		throw std::exception();
	this->spriteNbr = spriteNbr;
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->currentSprite = 0;
	this->modele.setTexture(textures->getTexture());
	this->modele.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(spriteWidth, spriteHeight)));
}

void	TekEngine::Sprite::setMask(sf::Color col) {
	this->modele.setColor(col);
}

void	TekEngine::Sprite::setPosition(std::pair<int, int> pos) {
	this->modele.setPosition(sf::Vector2f(pos.second, pos.first));
}

void	TekEngine::Sprite::refresh() {
	std::clock_t	t = std::clock();
	sf::IntRect		rect;

	if (static_cast<float>((t - this->clock)) / CLOCKS_PER_SEC >= this->animSpeed) {
		rect = this->modele.getTextureRect();
		if (++this->currentSprite == this->spriteNbr) {
			rect.left = 0;
			this->currentSprite = 0;
		}
		else
			rect.left += this->spriteWidth;
		this->modele.setTextureRect(rect);
		this->clock = std::clock();
	}
}

void	TekEngine::Sprite::setAnimSpeed(float speed) {
	this->animSpeed = speed;
}

void	TekEngine::Sprite::setScale(float scale) {
	this->modele.setScale(sf::Vector2f(scale, scale));
}