#pragma once

#include <string>

class ConsoleManager
{
private:
	std::string GetCommand();

	void Writer(bool* closeRequest) const;

public:
	void operator()(bool& closeRequest);
};
