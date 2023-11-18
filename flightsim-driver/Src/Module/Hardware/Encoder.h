#pragma once
#include <string>
#include <exception>
#include "SimServices.h"
#include "ConsoleManager.h"
#include "HardwareElementBase.h"
#include "SimEvent.h"


class Encoder : public HardwareElementBase
{
private:
	const SimEvent _incEvent;
	const SimEvent _decEvent;

public:
	Encoder(HardwareElementBase& base, SimEvent incEvent, SimEvent decEvent)
		: HardwareElementBase(base), _incEvent{ incEvent }, _decEvent{ decEvent }
	{}

	virtual bool EventsSetup() const
	{
		bool setupOk = _simServices.SetUpSimEvent(_moduleID, _incEvent.GetID(), _incEvent.GetName());
		setupOk |= _simServices.SetUpSimEvent(_moduleID, _decEvent.GetID(), _decEvent.GetName());
		return setupOk;
	}
};
