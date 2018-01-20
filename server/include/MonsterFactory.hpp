#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

# include "IEntity.hpp"
# include "Pos.hpp"
# include "ILibLoader.hpp"

class MonsterFactory
{
public:
	MonsterFactory();
	~MonsterFactory();

private:
	std::unordered_map<std::string, std::function<std::unique_ptr<IEntity>&(const int)>>	factory;
	std::vector<std::vector<std::pair<Pos, std::string>>>									patternList;
	unsigned int																			currentLastID;
	std::unique_ptr<ILibLoader>																libLoader;

public:
	void									updateLibraries() noexcept;
	bool									searchMonster(const std::string &name) const noexcept;
	std::unique_ptr<IEntity>				&createMonster(const std::string &name);
	void									addPattern(const std::vector<std::pair<Pos, std::string>> &pattern);
	std::vector<std::unique_ptr<IEntity>>	pickPattern(const int index);
	int										getPatternNbr() const noexcept;
};

#endif // !MONSTERFACTORY_HPP_