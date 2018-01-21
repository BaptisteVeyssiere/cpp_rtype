#pragma once

#include <memory>
#include "Protocol.hpp"

struct ClientRequest
{
	unsigned int					id;
	std::shared_ptr<Inputs>			input;
	std::shared_ptr<Connect>		connect;
};

struct ServerRequest
{
	unsigned int							id;
	std::shared_ptr<Header>					head;
	std::vector<std::shared_ptr<Entity>>	entities;
	std::vector<std::shared_ptr<Enemy>>		enemies;
	std::vector<std::shared_ptr<Player>>	players;
};