#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"

class Button
{
private:
	const unsigned _moduleID;
	const unsigned _eventID;
	const char* const _eventName;
	const unsigned _dataRequestID;

protected:
	const SimServices* const _simServices;
	ConsoleManager* const _console;

public:

	Button(unsigned moduleID, unsigned eventID, const char* eventName, unsigned dataRequestID, const SimServices* simServices, ConsoleManager* console)
		: _moduleID{ moduleID }, _eventID{ eventID }, _eventName{ eventName }, _dataRequestID{ dataRequestID }, _simServices{ simServices }, _console{ console }
	{
		if (_simServices == nullptr || _console == nullptr)
			throw std::exception("simServices and console can't be null!");
	}

	virtual bool Press() const
	{
		bool eventOk = _simServices->InvokeSimEvent(_moduleID, _eventID);
		bool dataRequestOk = _simServices->RequestData(_moduleID, _dataRequestID);

		if (eventOk == false || dataRequestOk == false)
		{
			std::string msg = "ERROR: Module " + std::to_string(_moduleID);
			msg += ", Event " + std::to_string(_eventID) + ": Press failed\r\n";
			_console->Send(msg);
			return false;
		}
		return true;
	}

	virtual bool EventSetup() const 
	{
		bool setupOk = _simServices->SetUpSimEvent(_moduleID, _eventID, _eventName);
		return setupOk;
	}
};
