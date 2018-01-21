#ifndef LINUXLIBLOADER_HPP_
# define LINUXLIBLOADER_HPP_

# include "ILibLoader.hpp"

class LinuxLibLoader : public ILibLoader
{
public:
	LinuxLibLoader();
	~LinuxLibLoader();
private:
	std::unordered_map<std::string, void*>	handlers;

public:
	bool						isDynamicLib(const std::string &filename) const noexcept;
	std::vector<std::string>	readDirectory(const std::string &dirname) const;
	void						getNewHandlers(std::unordered_map<std::string, std::function<std::unique_ptr<IEntity>&(const int)>>	&factory);

private:
	std::string	getSymbolName(const std::string &filename) const noexcept;
	std::function<std::unique_ptr<IEntity>&(const int)>	getSymbol(const std::string &sym, const std::string &file);
};

#endif // !LINUXWINLIBLOADER_HPP_