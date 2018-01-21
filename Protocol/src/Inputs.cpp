#include "inputs.hpp"

Inputs::Inputs()
{
	structureHeader = 1;
	x = y = 0;
	for (int i = 7; i >= 0; --i)
		this->inputs[i] = NONE;
}

std::vector<char> Inputs::getVector()
{
	auto const ptr = reinterpret_cast<char*>(this);
	std::vector<char> buffer(ptr, ptr + sizeof(Inputs));
	return (buffer);
}