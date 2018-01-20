#ifndef ILIBLOADER_HPP_
# define ILIBLOADER_HPP_

# include <utility>
# include <functional>
# include <string>
# include <unordered_map>
# include <vector>
# include "IEntity.hpp"

typedef  std::unique_ptr<IEntity>& (*fptr)(const int);

class ILibLoader
{
public:
	ILibLoader() {};
	virtual ~ILibLoader() {};

	virtual bool						isDynamicLib(const std::string &filename) const noexcept = 0;
	virtual std::vector<std::string>	readDirectory(const std::string &dirname) const = 0;
	virtual void						getNewHandlers(std::unordered_map<std::string, std::function<std::unique_ptr<IEntity>&(const int)>>	&factory) = 0;

protected:
	virtual std::string	getSymbolName(const std::string &filename) const noexcept = 0;
	virtual std::function<std::unique_ptr<IEntity>&(const int)>	getSymbol(const std::string &sym, const std::string &file) = 0;
};

#endif // !ILIBLOADER_HPP_