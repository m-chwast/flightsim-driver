#pragma once
#include "ModuleBase.h"

class ModuleHardware : public ModuleBase
{
private:
	unsigned _id;

	virtual bool EventsInitialize() { return false; };
	virtual bool DataInitialize() { return false; };

public:
	ModuleHardware(const SimServices& simServices, unsigned id) : ModuleBase(simServices)
	{
		_id = id;
	}

	unsigned GetID() const { return _id; }

	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* data) {};
	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) {};

	virtual void Initialize() override;

	virtual ~ModuleHardware() {}
};

