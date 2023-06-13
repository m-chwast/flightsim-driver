#pragma once
#include "ModuleBase.h"

class ModuleHardware : public ModuleBase
{
private:
	unsigned _id;

	virtual bool EventsInitialize() { return false; };
	virtual bool DataInitialize() { return false; };

protected:
	int _dataUpdatePeriod = -1;	//-1 -> no update, period is in ms 

public:
	ModuleHardware(const SimServices& simServices, unsigned id) : ModuleBase(simServices)
	{
		_id = id;
	}

	unsigned GetID() const { return _id; }

	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* data) {};
	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) {};

	virtual void Initialize() override;
	virtual void Manage() override;

	virtual ~ModuleHardware() {}
};

enum DataRequestID
{
	DATA_REQUEST_ID_PERIODIC = 0,
	DATA_REQUEST_ID_ACTION,
};
