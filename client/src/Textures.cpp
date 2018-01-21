#include "Textures.hpp"

TekEngine::Textures::Textures() {

}

TekEngine::Textures::~Textures() {

}

sf::Texture	&TekEngine::Textures::getTexture() {
	return (foundTexture->texture);
}

bool		TekEngine::Textures::findTextureById(std::string id) {
	for (auto texture : textures) {
		if (texture->id == id) {
			foundTexture = texture;
			return (true);
		}
	}
	return (false);
}

void		TekEngine::Textures::addTexture(std::string id) {
	TekEngine::Textures::Text		*tmp = new TekEngine::Textures::Text;
	std::string						path("resources/textures/" + id);

	if (this->findTextureById(id))
		return;
	if (!tmp->texture.loadFromFile(path))
		throw std::exception();
	tmp->texture.setRepeated(false);
	tmp->texture.setSmooth(true);
	tmp->id = id;
	textures.push_back(tmp);
}

TekEngine::Textures	*TekEngine::Textures::getInstance() {
	static TekEngine::Textures	*instance = new TekEngine::Textures;
	return (instance);
}
