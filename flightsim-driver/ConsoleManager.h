#pragma once

#include <string>

class ConsoleManager
{
private:
	std::string GetCommand();

	void Writer(const bool& closeRequest);

public:
	void operator()(bool& closeRequest);
};
