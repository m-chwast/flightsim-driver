#pragma once
#include "ConsoleManager.h"


class CommManager
{
private:
	ConsoleManager& _console;

	void Handler(bool& closeRequest);

public:
	CommManager(ConsoleManager& console)
		: _console{ console }
	{}

};
