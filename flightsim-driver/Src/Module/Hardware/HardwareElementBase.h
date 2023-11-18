#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"


class HardwareElementBase
{
protected:
	const unsigned _moduleID;
	const unsigned _dataRequestID;

	const SimServices* const _simServices;
	ConsoleManager* const _console;

public:
	HardwareElementBase(unsigned moduleID, unsigned dataRequestID, const SimServices* simServices, ConsoleManager* console)
		: _moduleID{ moduleID }, _dataRequestID{ dataRequestID }, _simServices{ simServices }, _console{ console }
	{
		if (_simServices == nullptr)
			throw std::exception("simServices can't be null!");
		if (_console == nullptr)
			throw std::exception("console can't be null!");
		if (_moduleID >= 100)
		{
			std::string exMsg = "moduleID has to be less than 100; was " + std::to_string(_moduleID);
			throw std::exception(exMsg.c_str());
		}
	}
};
