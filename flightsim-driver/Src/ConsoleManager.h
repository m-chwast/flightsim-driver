#pragma once

#include <string>
#include <vector>
#include <mutex>

class ConsoleManager
{
private:
	std::string GetCommand();

	void Writer(bool* closeRequest);

	std::vector<std::string> _messages;
	std::mutex _messagesMutex;

public:
	void Handler(bool& closeRequest);

	void Send(std::string message, int priority = 0);
};
