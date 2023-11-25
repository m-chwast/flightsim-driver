#pragma once
#include <vector>
#include <map>
#include "ModuleBase.h"
#include "Button.h"
#include "Encoder.h"


class ModuleHardware : public ModuleBase
{
private:
	const unsigned _id;

	std::vector<const Button*> _buttons;
	std::vector<const Encoder*> _encoders;

	std::map<unsigned, const char*> _events;

	virtual bool EventsInitialize() const;
	virtual bool DataInitialize() = 0;

protected:
	int _dataUpdatePeriod = -1;	//-1 -> no update, period is in ms 

	void RegisterButton(const Button* button) { _buttons.push_back(button); }
	void RegisterEncoder(const Encoder* encoder) { _encoders.push_back(encoder); }

	void RegisterEvent(unsigned id, const char* evt);
	const char* GetEventName(unsigned eventID) const;
	SimEvent GetEvent(unsigned eventID) const { return SimEvent(eventID, GetEventName(eventID)); }

	void SendDataToHardware(const uint8_t* data, unsigned size) const;

public:
	ModuleHardware(const ModuleUtils& utils, unsigned id)
		: ModuleBase(utils),
		_id{ id }
	{
		if (id == 0)
			throw std::invalid_argument("module ID cannot be 0 (to create reserved id space for the module)");
	}

	unsigned GetID() const { return _id; }
	unsigned GetFirstReservedID() const { return GetID() * 100; }

	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* data) = 0;
	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) = 0;

	virtual void Initialize() override;
	virtual void Manage() override;

	virtual ~ModuleHardware();
};

enum DataRequestID
{
	DATA_REQUEST_ID_PERIODIC = 0,
	DATA_REQUEST_ID_ACTION,
};
