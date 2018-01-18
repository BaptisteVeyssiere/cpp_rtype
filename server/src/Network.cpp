#include <iostream>
#include "Network.hpp"

Network::Network()
{

}

Network::~Network()
{

}

Network	&Network::getInstance()
{
	static Network instance;
	return (instance);
}