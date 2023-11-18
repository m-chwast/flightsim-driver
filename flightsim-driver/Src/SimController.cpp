#include "SimController.h"
#include <chrono>
#include <iostream>

void SimController::ControllerHandler()
{
    while (_stopControllerFlag == false)
    {
        if (_startSearchFlag == true)
        {
            _startSearchFlag = false;
            StartSearch(1000);
        }
        if (_stopSearchFlag == true)
        {
            _stopSearchFlag = false;
            StopSearch();
        }

        DispatchHandler();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

bool SimController::TryConnect()
{
    _console.Send("Connecting...\r\n");

    HRESULT result;
    result = SimConnect_Open(&_hSimConnect, "a320 hardware driver", NULL, 0, 0, 0);

    _isConnected = false;

    if (result != S_OK)
    {
        _console.Send("Unable to connect.\r\n");
        _hSimConnect = nullptr;
        return false;
    }

    _isConnected = true;
    _console.Send("Connected!\r\n");
    return true;
}

void SimController::Disconnect()
{
    _console.Send("Disconnecting...\r\n");
    if (_hSimConnect == nullptr || _isConnected == false)
    {
        _console.Send("Already disconnected\r\n");
        return;
    }

    _isConnected = false;
    HRESULT res = SimConnect_Close(_hSimConnect);
    
    if (res == S_OK)
    {
        _console.Send("Disconnected.\r\n");
        return;
    }

    _console.Send("Disconnection error\r\n");
}

void SimController::TryConnectPeriodically(unsigned period, bool connectOnce)
{
    while ((_isConnected == false && connectOnce == true) || connectOnce == false)
    {
        if (_searchActive != true)
            break;

        if (_isConnected != true)
        {
            TryConnect();
        }
        //wait with next try for specified time
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
}

SimController::SimController(ConsoleManager& console, const ModuleMaster* moduleMaster)
    : _console{ console }
{
    _moduleMaster = moduleMaster;
    _simServices = new SimServices(&_hSimConnect, console);
    _controllerThread = new std::thread(&SimController::ControllerHandler, this);
}

void SimController::SearchForServer()
{
    _startSearchFlag = true;
}

void SimController::StopSearchForServer()
{
    _stopSearchFlag = true;
}

void SimController::StartSearch(unsigned period, bool stopSearchAfterFirstConnection)
{
    //something went wrong and search was called twice, so stop the previous instance
    if (_searchThread != nullptr)
        StopSearch();

    _console.Send("Searching for server...\r\n");
    _searchActive = true;
    _searchThread = new std::thread(&SimController::TryConnectPeriodically,
        this, period, stopSearchAfterFirstConnection);
}

void SimController::StopSearch()
{
    _console.Send("Stopping the search...\r\n");
    _searchActive = false;

    if(_searchThread->joinable())
        _searchThread->join();
    _console.Send("Search terminated\r\n");

    if (_searchThread == nullptr)
        return;

    delete _searchThread;
    _searchThread = nullptr;
}

void SimController::DispatchHandler()
{
    SIMCONNECT_RECV* data = nullptr;
    DWORD dataSize;
    HRESULT res = SimConnect_GetNextDispatch(_hSimConnect, &data, &dataSize);;

    //stop condition: no data was received or receive error
    while(res == S_OK && data != nullptr && data->dwID != SIMCONNECT_RECV_ID_NULL)
    {
        //at this point data is valid
        DispatchHandlerProcessData(data);

        //get new data if available
        data = nullptr;
        res = SimConnect_GetNextDispatch(_hSimConnect, &data, &dataSize);        
    }
}

void SimController::DispatchHandlerProcessData(const SIMCONNECT_RECV* data)
{
    switch (data->dwID)
    {
    case SIMCONNECT_RECV_ID_OPEN:
    {
        _console.Send("Received Open data\r\n");
        break;
    }
    case SIMCONNECT_RECV_ID_EVENT:
    {
        auto eventData = static_cast<const SIMCONNECT_RECV_EVENT*>(data);
        _console.Send("Received Event. Module: " + std::to_string(eventData->uGroupID));
        _console.Send(", Event: " + std::to_string(eventData->uEventID) + "\r\n");
        if (_moduleMaster == nullptr)   //it can be nullptr if not set in time
            break;
        ModuleHardware* module = _moduleMaster->GetModule(eventData->uGroupID);
        if (module != nullptr)
            module->ProcessEvent(eventData);
        break;
    }
    case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
    {
        auto simobjectData = static_cast<const SIMCONNECT_RECV_SIMOBJECT_DATA*>(data);
        _console.Send("Received Simobject data\r\n");
        if (_moduleMaster == nullptr)   //it can be nullptr if not set in time
            break;
        ModuleHardware* module = _moduleMaster->GetModule(simobjectData->dwDefineID);
        if (module != nullptr)
            module->ProcessData(simobjectData);
        break;
    }
    case SIMCONNECT_RECV_ID_EXCEPTION: 
    {
        auto simobjectData = static_cast<const SIMCONNECT_RECV_EXCEPTION*>(data);
        _console.Send("Received Exception! dwException: " + std::to_string(simobjectData->dwException) + "\r\n");
        break;
    }
    default:
    {
        _console.Send("Received unhandled data\r\n");
        break;
    }
    }
}

SimController::~SimController()
{
    StopSearch();
    if (_controllerThread == nullptr)
        return;

    _stopControllerFlag = true;
    _controllerThread->join();
    std::cout << "Controller thread joined\r\n";
    delete _controllerThread;
    _controllerThread = nullptr;

    delete _simServices;
}
