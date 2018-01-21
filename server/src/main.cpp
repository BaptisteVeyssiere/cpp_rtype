#include <iostream>
#include "Network.hpp"
#include "RoomManager.hpp"

int main(int argc, char **argv)
{
	try
	{
		Network &net = Network::getInstance();
		net.startReceivingConnections(57342);
		RoomManager manager;
		manager.process();
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}