#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"
#include "HardwareElementBase.h"


class Button : public HardwareElementBase
{
private:
	const unsigned _eventID;
	const char* const _eventName;
	
public:
	Button(HardwareElementBase& base, unsigned eventID, const char* eventName)
		: HardwareElementBase(base), _eventID{ eventID }, _eventName{ eventName }
	{}

	virtual bool Press() const
	{
		bool eventOk = _simServices.InvokeSimEvent(_moduleID, _eventID);
		bool dataRequestOk = _simServices.RequestData(_moduleID, _dataRequestID);

		if (eventOk == false || dataRequestOk == false)
		{
			std::string msg = "ERROR: Module " + std::to_string(_moduleID);
			msg += ", Event " + std::to_string(_eventID) + ": Press failed\r\n";
			_console.Send(msg);
			return false;
		}
		return true;
	}

	virtual bool EventSetup() const 
	{
		bool setupOk = _simServices.SetUpSimEvent(_moduleID, _eventID, _eventName);
		return setupOk;
	}
};
