#include "WinLibLoader.hpp"

WinLibLoader::WinLibLoader()
{

}

WinLibLoader::~WinLibLoader()
{
	for (auto it = this->handlers.begin(); it != this->handlers.end(); ++it)
		FreeLibrary(it->second);
}

bool	WinLibLoader::isDynamicLib(const std::string &filename) const noexcept
{
	std::string	toMatch = ".dll";
	if (filename.size() >= toMatch.size() &&
		filename.compare(filename.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
		return (true);
	return (false);
}

std::vector<std::string>	WinLibLoader::readDirectory(const std::string &dirname) const
{
	std::string pattern(dirname);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE handler;
	std::vector<std::string> fileList;
	if ((handler = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE)
	{
		if (this->isDynamicLib(data.cFileName))
			fileList.push_back(data.cFileName);
		while (FindNextFile(handler, &data))
			if (this->isDynamicLib(data.cFileName))
				fileList.push_back(data.cFileName);
		FindClose(handler);
	}
	else
		throw std::runtime_error("No directory found");
	return (fileList);
}

void	WinLibLoader::getNewHandlers(std::unordered_map<std::string, std::function<std::unique_ptr<IEntity>&(const int)>> &factory)
{
	std::vector<std::string>	libList = this->readDirectory("monster");
	HMODULE						handle;
	std::string					symbol;

	for (auto file : libList)
		if (this->handlers.find(file) == this->handlers.end())
		{
			handle = LoadLibraryA(file.c_str());
			if (!handle)
				throw std::runtime_error("Can't load .dll file");
			this->handlers.insert({ file, handle });
			symbol = this->getSymbolName(file);
			factory.insert({ symbol, this->getSymbol(symbol, file) });
		}
}

std::string		WinLibLoader::getSymbolName(const std::string &filename) const noexcept
{
	return (filename.substr(0, filename.length() - 4));
}

std::function<std::unique_ptr<IEntity>&(const int)>		WinLibLoader::getSymbol(const std::string &sym, const std::string &file)
{
	FARPROC symbol = GetProcAddress(this->handlers[file], sym.c_str());
	if (!symbol)
		throw std::runtime_error("Symbol not found");
	return (reinterpret_cast<fptr>(symbol));
}