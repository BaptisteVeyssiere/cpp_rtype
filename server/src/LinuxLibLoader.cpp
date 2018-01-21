#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include "LinuxLibLoader.hpp"

LinuxLibLoader::LinuxLibLoader()
{

}

LinuxLibLoader::~LinuxLibLoader()
{
	for (std::unordered_map<std::string, void*>::iterator it = this->handlers.begin(); it != this->handlers.end(); ++it)
		dlclose(it->second);
}

bool	LinuxLibLoader::isDynamicLib(const std::string &filename) const noexcept
{
	std::string	toMatch = ".so";
	if (filename.size() >= toMatch.size() &&
		filename.compare(filename.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
		return (true);
	return (false);
}

std::vector<std::string>	LinuxLibLoader::readDirectory(const std::string &dirname) const
{
	DIR* dirp = opendir(dirname.c_str());
	if (!dirp)
		throw std::runtime_error("No directory found");
	std::vector<std::string> fileList;
	struct dirent *entry;
	while (!(entry = readdir(dirp))) {
		if (this->isDynamicLib(entry->d_name))
			fileList.push_back(entry->d_name);
	}
	if (closedir(dirp) < 0)
		throw std::runtime_error("Can't close directory");
	return (fileList);
}

void	LinuxLibLoader::getNewHandlers(std::unordered_map<std::string, std::function<std::unique_ptr<IEntity>&(const int)>>	&factory)
{
	std::vector<std::string>	libList = this->readDirectory("monster");
	void						*handle;
	std::string					symbol;


	for (auto file : libList)
		if (this->handlers.find(file) == this->handlers.end())
		{
			handle = dlopen(file, RTLD_LAZY);
			if (!handle)
				throw std::runtime_error("Can't load .so file");
			this->handlers.insert({ file, handle });
			symbol = this->getSymbolName(file);
			factory.insert({ symbol, this->getSymbol(symbol, file) });
		}
}

std::string		LinuxLibLoader::getSymbolName(const std::string &filename) const noexcept
{
	return (filename.substr(0, filename.length() - 3));
}

std::function<std::unique_ptr<IEntity>&(const int)>		LinuxLibLoader::getSymbol(const std::string &sym, const std::string &file)
{
	void *symbol = dlsym(this->handlers[file], sym);
	if (!symbol)
		throw std::runtime_error("Symbol not found");
	return (reinterpret_cast<fptr>(symbol));
}