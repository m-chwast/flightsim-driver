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
	const char* GetEvent(unsigned eventID) const;

public:
	ModuleHardware(const SimServices& simServices, ConsoleManager& console, unsigned id)
		: ModuleBase(simServices, console),
		_id{ id }
	{}

	unsigned GetID() const { return _id; }

	virtual void ProcessEvent(const SIMCONNECT_RECV_EVENT* data) = 0;
	virtual void ProcessData(const SIMCONNECT_RECV_SIMOBJECT_DATA* data) = 0;

	virtual void Initialize() override;
	virtual void Manage() override;

	virtual ~ModuleHardware() {}
};

enum DataRequestID
{
	DATA_REQUEST_ID_PERIODIC = 0,
	DATA_REQUEST_ID_ACTION,
};
