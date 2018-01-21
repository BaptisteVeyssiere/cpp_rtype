#ifndef GUI_HPP__
# define GUI_HPP__

#include <stack>
#include "Layer.hpp"
#include <SFML/Graphics.hpp>

namespace TekEngine
{
	class Gui
	{
	private:
		bool							display;
		bool							click = false;
		std::stack<TekEngine::Layer*>	layers;
		sf::RenderWindow				*win = NULL;

	public:
		Gui();
		~Gui();

	private:
		Gui(Gui &other);
		Gui	operator=(Gui &other);

	private:
		std::string	checkMouse();

	public:
		void		setWin(sf::RenderWindow	*win);
		void		setDisplay(bool display);
		void		addLayer(TekEngine::Layer	*layer);
		void		removeLayer();
		void		refresh();
		std::string	mouseClick();
	};
}

#endif //GUI_HPP__