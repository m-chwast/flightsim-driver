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

	const SimServices& _simServices;
	ConsoleManager& _console;

public:
	HardwareElementBase(unsigned moduleID, unsigned dataRequestID, const SimServices& simServices, ConsoleManager& console)
		: _moduleID{ moduleID }, _dataRequestID{ dataRequestID }, _simServices{ simServices }, _console{ console }
	{
		if (_moduleID >= 100)
		{
			std::string exMsg = "moduleID has to be less than 100; was " + std::to_string(_moduleID);
			throw std::exception(exMsg.c_str());
		}
	}
};
