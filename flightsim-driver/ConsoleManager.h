#pragma once

#include <string>

class ConsoleManager
{
private:
	std::string GetCommand();

public:
	void operator()(bool& closeRequest);
};
