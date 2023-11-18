#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"


class Encoder
{
private:

protected:
	const unsigned _moduleID;
	const unsigned _dataRequestID;

	const SimServices* const _simServices;
	ConsoleManager* const _console;

public:
	Encoder(unsigned moduleID, unsigned dataRequestID, const SimServices* simServices, ConsoleManager* console)
		: _moduleID{ moduleID }, _dataRequestID{ dataRequestID }, _simServices{ simServices }, _console{ console }
	{
		if (_simServices == nullptr || _console == nullptr)
			throw std::exception("simServices and console can't be null!");
	}
};
