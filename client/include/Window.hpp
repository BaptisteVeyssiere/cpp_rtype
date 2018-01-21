#ifndef WINDOW_HPP__
# define WINDOW_HPP__

#include <SFML/Graphics.hpp>

namespace TekEngine 
{
	class Window
	{
	private:
		sf::RenderWindow	*win;

	public:
		Window();
		~Window();

	private:
		Window(Window &other);
		Window	&operator=(Window &other);

	public:
		int		createWindow(int width, int height, bool fullscreen, const std::string title);
		void	closeWindow(void);
		bool	isOpen(void);
		void	clear();
		void	refresh();
		bool	pollEvent(sf::Event &event);
		sf::RenderWindow	*getWindow();
	};

}

#endif // WINDOW_HPP__
