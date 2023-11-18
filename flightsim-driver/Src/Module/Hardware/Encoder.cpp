#include "Encoder.h"

bool Encoder::InvokeEventAndRequestData(const SimEvent& evt) const
{
	bool eventOk = _simServices.InvokeSimEvent(_moduleID, evt.GetID());
	bool dataRequestOk = _simServices.RequestData(_moduleID, _dataRequestID);

	if (eventOk == false || dataRequestOk == false)
	{
		std::string msg = "ERROR: Module " + std::to_string(_moduleID);
		msg += ", Event " + std::to_string(evt.GetID()) + ": failed to invoke or data request failed\r\n";
		_console.Send(msg);
		return false;
	}
	return true;
}
