#pragma once
#include "StableButton.h"


class StableDataDrivenButton : public StableButton
{
private:
	const char* const _dataName;
	const unsigned _buttonDataRequestID;
public:

	StableDataDrivenButton(HardwareElementBase& base, unsigned buttonDataRequestID, const char* dataName)
		: StableButton(base, SimEvent(0, "")), 
		_dataName{dataName}, _buttonDataRequestID{buttonDataRequestID}
	{}

	virtual bool Press() const override
	{
		//set lvar to oppposite of stored value
		int32_t newValue = !IsActive();
		bool dataSetOk = _simServices.SetData(_buttonDataRequestID, 1, sizeof(int32_t), reinterpret_cast<void*>(&newValue));
		bool dataRequestOk = _simServices.RequestData(_moduleID, _dataRequestID);

		if (dataSetOk == false || dataRequestOk == false)
		{
			std::string msg = "ERROR: Module " + std::to_string(_moduleID) + "(DataDrivenButton)";
			msg += ", Button data request ID " + std::to_string(_buttonDataRequestID) + ": Press failed\r\n";
			_console.Send(msg);
			return false;
		}
		return true;
	}

	virtual bool EventSetup() const override
	{
		//this button type setups its own data request
		bool isOk = _simServices.SetUpData(_buttonDataRequestID, _dataName, "Boolean", SIMCONNECT_DATATYPE_INT32);
		return isOk;
	}
};
