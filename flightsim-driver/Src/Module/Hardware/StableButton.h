#pragma once
#include "Button.h"

class StableButton : public Button
{
private:
	bool _isActive = false;

public:
	StableButton(HardwareElementBase& base, unsigned eventID, const char* eventName)
		: Button(base, eventID, eventName) 
	{}

	bool IsActive() const { return _isActive; }
	void SetState(bool isActive) { _isActive = isActive; }
};
