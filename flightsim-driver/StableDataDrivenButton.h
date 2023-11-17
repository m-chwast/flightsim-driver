#pragma once
#include "StableButton.h"


class StableDataDrivenButton : public StableButton
{
private:
	const char* const _dataName;
	const unsigned _buttonDataRequestID;
public:

	StableDataDrivenButton(unsigned moduleID, unsigned buttonDataRequestID, const char* dataName, 
		unsigned generalDataRequestID, const SimServices* simServices, ConsoleManager* console)
		: StableButton(moduleID, 0, "", generalDataRequestID, simServices, console), 
		_dataName{dataName}, _buttonDataRequestID{buttonDataRequestID}
	{}

	virtual bool Press() const override
	{

	}

	virtual bool EventSetup() const override
	{
		//this button type setups its own data request
		bool isOk = _simServices->SetUpData(_buttonDataRequestID, _dataName, "Boolean", SIMCONNECT_DATATYPE_INT32);
		return isOk;
	}
};
