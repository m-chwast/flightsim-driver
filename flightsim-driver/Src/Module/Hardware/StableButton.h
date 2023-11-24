#pragma once
#include "Button.h"

class StableButton : public Button
{
private:
	bool _isActive = false;

public:
	StableButton(HardwareElementBase& base, const SimEvent pushEvent)
		: Button(base, pushEvent) 
	{}

	bool IsActive() const { return _isActive; }
	void SetState(bool isActive) { _isActive = isActive; }
};
