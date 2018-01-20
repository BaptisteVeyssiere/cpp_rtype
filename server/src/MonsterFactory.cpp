#include <stdexcept>
#include "MonsterFactory.hpp"
#ifdef _WIN32
	#include "WinLibLoader.hpp"
#else
	#include "LinuxLibLoader.hpp"
#endif

MonsterFactory::MonsterFactory()
	: currentLastID(4)
{
#ifdef _WIN32
	this->libLoader = std::make_unique<WinLibLoader>();
#else
	this->libLoader = std::make_unique<LinuxLibLoader>();
#endif
}

MonsterFactory::~MonsterFactory()
{

}

bool	MonsterFactory::searchMonster(const std::string &name) const noexcept
{
	if (this->factory.find(name) == this->factory.end())
		return (false);
	return (true);
}

std::unique_ptr<IEntity>	&MonsterFactory::createMonster(const std::string &name)
{
	if (this->factory.find(name) == this->factory.end())
		throw std::logic_error("No monster exists with the name requested");
	return (this->factory[name]((this->currentLastID)++));
}

void	MonsterFactory::addPattern(const std::vector<std::pair<Pos, std::string>> &pattern)
{
	for (auto &entity : pattern)
		if (this->searchMonster(entity.second) == false)
			throw std::runtime_error("The pattern contains non registered monsters");
	this->patternList.push_back(pattern);
}

std::vector<std::unique_ptr<IEntity>>	MonsterFactory::pickPattern(const int index)
{
	if (this->patternList.size() <= index)
		throw std::out_of_range("Index requested is out of range");
	std::vector<std::unique_ptr<IEntity>>	pattern;
	for (unsigned int i = 0; i < this->patternList[index].size(); ++i)
	{
		pattern.push_back(std::move(this->createMonster(this->patternList[index][i].second)));
		pattern[i]->setPos(this->patternList[index][i].first.x, this->patternList[index][i].first.y);
	}
	return (pattern);
}

int		MonsterFactory::getPatternNbr() const noexcept
{
	return (this->patternList.size());
}

void	MonsterFactory::updateLibraries() noexcept
{
	this->libLoader->getNewHandlers(this->factory);
}
