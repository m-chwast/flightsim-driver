#pragma once
#include <string>
#include "SimServices.h"
#include "ConsoleManager.h"

class Button
{
private:
	const unsigned _moduleID;
	const unsigned _eventID;
	const char* _eventName;

	const SimServices* const _simServices;
	ConsoleManager* const _console;

public:

	Button(unsigned moduleID, unsigned eventID, const char* eventName, const SimServices* simServices, ConsoleManager* console)
		: _moduleID{ moduleID }, _eventID{ eventID }, _eventName{ eventName }, _simServices{ simServices }, _console{ console }
	{}

	virtual void Press() const
	{
		_simServices->InvokeSimEvent(_moduleID, _eventID);
	}
};
