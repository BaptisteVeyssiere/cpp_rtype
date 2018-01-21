#ifndef SPRITE_HPP__
# define SPRITE_HPP__
#include <SFML/Graphics.hpp>

namespace TekEngine
{
	class Sprite
	{
		sf::Sprite		modele;
		int				spriteNbr;
		int				currentSprite;
		std::clock_t	clock;
		float			animSpeed;
		int				spriteWidth;
		int				spriteHeight;

	public:
		Sprite();
		~Sprite();

	private:
		Sprite(Sprite &other);
		Sprite	operator=(Sprite &other);

	public:
		void		setSprite(std::string path, int spriteNbr, int spriteWidth, int spriteHeight);
		void		refresh();
		void		setMask(sf::Color mask);
		void		setPosition(std::pair<int, int> pos);
		void		setAnimSpeed(float speed);
		void		setScale(float scale);
		sf::Sprite	getSprite();
	};


}

#endif // SPRITE_HPP__