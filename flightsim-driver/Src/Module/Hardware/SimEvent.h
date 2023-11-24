#pragma once
#include <string>

class SimEvent
{
private:
	const std::string _name;
	const unsigned _id;

public:
	SimEvent(unsigned id, const char* name)
		: _id{ id }, _name{ std::string(name == nullptr ? "" : name) }
	{}

	unsigned GetID() const { return _id; }
	const char* GetName() const { return _name.c_str(); }
};

