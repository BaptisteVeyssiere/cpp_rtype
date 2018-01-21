#ifndef LAYER_HPP__
# define LAYER_HPP__

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

namespace TekEngine
{
	class Layer
	{
	private:
		struct Button
		{
			sf::Sprite	sprite;
			std::pair<int, int>	pos;
			std::pair<int, int>	size;
			std::string			id;
			sf::Text			text;
		};

		struct Text
		{
			sf::Text		text;
			std::string		id;
		};

		bool									back = false;
		std::list<TekEngine::Layer::Button*>	buttons;
		std::list<TekEngine::Layer::Text*>		texts;
		sf::Sprite								background;
		sf::Font								font;

	public:
		Layer();
		~Layer();

	private:
		Layer(Layer &other);
		Layer	&operator=(Layer &other);

	private:
		bool	findButtonId(std::string id);
		bool	findTextId(std::string id);

	public:
		void		DrawLayer(sf::RenderWindow &win);
		std::string	applyHoverMask(sf::Vector2i pos);
		void		resetMask();
		void		addButton(std::string textureName, std::pair<int, int> pos, std::pair<int, int> size, std::string id);
		void		addBackground(std::string textureName);
		void		setButtonText(std::string id, std::string text, int size, sf::Color col = sf::Color::White);
		void		addText(std::string id, std::string text, std::pair<int, int> pos, int size);
		void		setText(std::string id, std::string str, int size, sf::Color col = sf::Color::White);
	};
}

#endif //LAYER_HPP__
