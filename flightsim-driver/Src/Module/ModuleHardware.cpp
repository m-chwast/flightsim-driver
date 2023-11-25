#include <chrono>
#include <stdexcept>
#include "ModuleHardware.h"


void ModuleHardware::Initialize()
{
	PrintInitMessage();

	bool initOk = EventsInitialize();
	_console.Send(_name + " Event setup " + (initOk == true ? "finished" : "failed") + "\r\n");

	initOk = DataInitialize();
	_console.Send(_name + " Data setup " + (initOk == true ? "finished" : "failed") + "\r\n");
}

bool ModuleHardware::EventsInitialize() const
{
	bool initOk = true;

	for (const Button* b : _buttons)
	{
		bool eventSetupOk = b->EventSetup();
		if (eventSetupOk == false)
			initOk = false;
	}

	for (const Encoder* e : _encoders)
	{
		bool eventSetupOk = e->EventsSetup();
		if (eventSetupOk == false)
			initOk = false;
	}

	return initOk;
}

void ModuleHardware::Manage()
{
	static std::chrono::time_point<std::chrono::system_clock> lastUpdate;

	//check if data updating is active
	if (_dataUpdatePeriod < 0)
		return;

	auto timeNow = std::chrono::system_clock::now();
	auto timeDiff = timeNow - lastUpdate;

	if (timeDiff >= std::chrono::milliseconds(_dataUpdatePeriod))
	{
		_simServices.RequestData(GetID(), DATA_REQUEST_ID_PERIODIC);
		lastUpdate = timeNow;
	}
}

void ModuleHardware::RegisterEvent(unsigned id, const char* evt)
{
	if (evt == nullptr)
		throw std::invalid_argument("Event name cannot be null");
	if (_events.contains(id))
		throw std::invalid_argument("Event " + std::to_string(id) + " already registered");
	_events.insert(std::pair(id, evt));
}

const char* ModuleHardware::GetEventName(unsigned eventID) const
{
	if (_events.contains(eventID) == false)
		throw std::invalid_argument("Event " + std::to_string(eventID) + " not in events map");
	return _events.at(eventID);
}

void ModuleHardware::SendDataToHardware(const uint8_t* data, unsigned size) const
{ 
	std::vector<uint8_t> dataToSend(size);
	for (int i = 0; i < size; i++)
	{
		dataToSend.push_back(data[i]);
	}
	_commManager.SendData(GetID(), dataToSend); 
}

ModuleHardware::~ModuleHardware()
{
	for (const Button* b : _buttons)
	{
		if (b != nullptr)
		{
			delete b;
		}
	}
	for (const Encoder* e : _encoders)
	{
		if (e != nullptr)
		{
			delete e;
		}
	}
}
