#ifndef LIBLOADER_HPP_
# define LIBLOADER_HPP_

# include <windows.h>
# include "ILibLoader.hpp"

class WinLibLoader : public ILibLoader
{
public:
	WinLibLoader();
	~WinLibLoader();

private:
	std::unordered_map<std::string, HMODULE>	handlers;

public:
	bool						isDynamicLib(const std::string &filename) const noexcept;
	std::vector<std::string>	readDirectory(const std::string &dirname) const;
	void						getNewHandlers(std::unordered_map<std::string, std::function<std::unique_ptr<IEntity>&(const int)>>	&factory);

private:
	std::string	getSymbolName(const std::string &filename) const noexcept;
	std::function<std::unique_ptr<IEntity>&(const int)>	getSymbol(const std::string &sym, const std::string &file);
};

#endif // !WINLIBLOADER_HPP_