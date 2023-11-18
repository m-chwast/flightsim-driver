#pragma once
#include "Encoder.h"
#include "StableButton.h"


class PushPullEncoder : public Encoder
{
private:
	const StableButton _pushButton;
	const StableButton _pullButton;

public:
	PushPullEncoder(HardwareElementBase& base,
		SimEvent incEvent, SimEvent decEvent,
		SimEvent pushEvent, SimEvent pullEvent)
		: Encoder(base, incEvent, decEvent),
		_pushButton(base, pushEvent), _pullButton(base, pullEvent)
	{}

	virtual bool EventsSetup() const override
	{
		bool setupOk = Encoder::EventsSetup();
		setupOk &= _pushButton.EventSetup();
		setupOk &= _pullButton.EventSetup();
		return setupOk;
	}
};
