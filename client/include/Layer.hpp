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
		};

		bool									back = false;
		std::list<TekEngine::Layer::Button*>	buttons;
		sf::Sprite								background;

	public:
		Layer();
		~Layer();

	private:
		Layer(Layer &other);
		Layer	&operator=(Layer &other);

	private:
		bool	findButtonId(std::string id);

	public:
		void		DrawLayer(sf::RenderWindow &win);
		std::string	applyHoverMask(sf::Vector2i pos);
		void		resetMask();
		void		addButton(std::string textureName, std::pair<int, int> pos, std::pair<int, int> size, std::string id);
		void		addBackground(std::string textureName);
	};
}

#endif //LAYER_HPP__
