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

protected:
	bool InvokeEventAndRequestData(const SimEvent& evt) const;

public:
	Encoder(HardwareElementBase& base, SimEvent incEvent, SimEvent decEvent)
		: HardwareElementBase(base), _incEvent{ incEvent }, _decEvent{ decEvent }
	{}

	bool Increment() const { return InvokeEventAndRequestData(_incEvent); }
	bool Decrement() const { return InvokeEventAndRequestData(_decEvent); }

	virtual bool EventsSetup() const
	{
		bool setupOk = _simServices.SetUpSimEvent(_moduleID, _incEvent.GetID(), _incEvent.GetName());
		setupOk &= _simServices.SetUpSimEvent(_moduleID, _decEvent.GetID(), _decEvent.GetName());
		return setupOk;
	}
};
