#include "Connect.hpp"

Connect::Connect()
{
}

std::vector<char> Connect::getVector()
{
	auto const ptr = reinterpret_cast<char*>(this);
	std::vector<char> buffer(ptr, ptr + sizeof(Connect));
	return (buffer);
}