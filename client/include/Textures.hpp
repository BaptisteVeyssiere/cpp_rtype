#ifndef TEXTURES_HPP__
# define TEXTURES_HPP__

#include <SFML/Graphics.hpp>
#include <list>

namespace TekEngine
{
	class Textures
	{
	private:
		struct Text
		{
			sf::Texture	texture;
			std::string	id;
		};

		std::list<TekEngine::Textures::Text*>			textures;
		Textures::Text									*foundTexture;

	public:
		~Textures();

	private:
		Textures();
		Textures	&operator=(Textures &other);

	public:
		static TekEngine::Textures	*getInstance();
		bool			findTextureById(std::string id);
		sf::Texture		&getTexture();
		void			addTexture(std::string id);
	};
}

#endif //TEXTURES_HPP__
