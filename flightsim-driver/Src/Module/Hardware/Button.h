#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"
#include "HardwareElementBase.h"
#include "SimEvent.h"


class Button : public HardwareElementBase
{
private:
	const SimEvent _event;
	
public:
	Button(HardwareElementBase& base, const SimEvent pushEvent)
		: HardwareElementBase(base), _event{ pushEvent }
	{}

	virtual bool Press() const
	{
		bool eventOk = _simServices.InvokeSimEvent(_moduleID, _event.GetID());
		bool dataRequestOk = _simServices.RequestData(_moduleID, _dataRequestID);

		if (eventOk == false || dataRequestOk == false)
		{
			std::string msg = "ERROR: Module " + std::to_string(_moduleID);
			msg += ", Event " + std::to_string(_event.GetID()) + ": Press failed\r\n";
			_console.Send(msg);
			return false;
		}
		return true;
	}

	virtual bool EventSetup() const 
	{
		bool setupOk = _simServices.SetUpSimEvent(_moduleID, _event.GetID(), _event.GetName());
		return setupOk;
	}
};
