#pragma once

#include <string>

class ModuleBase
{
protected:
	std::string _name = "defaultName";

	void PrintInitMessage();

public:
	
	virtual void Initialize() = 0;
	virtual void Manage() = 0;
};
