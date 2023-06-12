#include "SimController.h"
#include <iostream>
#include <chrono>

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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

bool SimController::TryConnect()
{
    std::cout << "Connecting...\r\n";

    HRESULT result;
    result = SimConnect_Open(&_hSimConnect, "a320 hardware driver", NULL, 0, 0, 0);

    _isConnected = false;

    if (result != S_OK)
    {
        std::cout << "Unable to connect.\r\n";
        _hSimConnect = nullptr;
        return false;
    }

    _isConnected = true;
    std::cout << "Connected!\r\n";
    return true;
}

void SimController::Disconnect()
{
    std::cout << "Disconnecting...\r\n";
    if (_hSimConnect == nullptr || _isConnected == false)
    {
        std::cout << "Already disconnected\r\n";
        return;
    }

    _isConnected = false;
    HRESULT res = SimConnect_Close(_hSimConnect);
    
    if (res == S_OK)
    {
        std::cout << "Disconnected.\r\n";
        return;
    }

    std::cout << "Disconnection error\r\n";
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

SimController::SimController()
{
    _simServices = new SimServices(&_hSimConnect);
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

    std::cout << "Searching for server...\r\n";
    _searchActive = true;
    _searchThread = new std::thread(&SimController::TryConnectPeriodically,
        this, period, stopSearchAfterFirstConnection);
}

void SimController::StopSearch()
{
    std::cout << "Stopping the search...\r\n";
    _searchActive = false;

    if(_searchThread->joinable())
        _searchThread->join();
    std::cout << "Search terminated\r\n";

    if (_searchThread == nullptr)
        return;

    delete _searchThread;
    _searchThread = nullptr;
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
