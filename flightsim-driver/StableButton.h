#pragma once
#include "Button.h"

class StableButton : Button
{
private:
	bool _isActive = false;

public:
	StableButton(unsigned moduleID, unsigned eventID, const char* eventName, unsigned dataRequestID, const SimServices* simServices, ConsoleManager* console)
		: Button(moduleID, eventID, eventName, dataRequestID, simServices, console) 
	{}

	bool IsActive() const { return _isActive; }
	void SetState(bool isActive) { _isActive = isActive; }
};
