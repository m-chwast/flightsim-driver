#pragma once
#include "ConsoleManager.h"


class CommManager
{
private:
	ConsoleManager& _console;

public:
	CommManager(ConsoleManager& console)
		: _console{ console }
	{}
};
