#include <iostream>
#include <chrono>
#include "SimController.h"

bool SimController::TryConnect()
{
    std::cout << "Connecting...\r\n";

    HRESULT result;
    result = SimConnect_Open(&hSimConnect, "a320 hardware driver", NULL, 0, 0, 0);

    _isConnected = false;

    if (result != S_OK)
    {
        std::cout << "Unable to connect.\r\n";
        hSimConnect = nullptr;
        return false;
    }

    _isConnected = true;
    std::cout << "Connected!\r\n";
    return true;
}

void SimController::Disconnect()
{
    std::cout << "Disconnecting...\r\n";
    if (hSimConnect == nullptr || _isConnected == false)
    {
        std::cout << "Already disconnected\r\n";
        return;
    }

    _isConnected = false;
    HRESULT res = SimConnect_Close(hSimConnect);
    
    if (res == S_OK)
    {
        std::cout << "Disconnected.\r\n";
        return;
    }

    std::cout << "Disconnection error\r\n";
}

void SimController::TryConnectPeriodically(unsigned period, bool connectOnce)
{
    bool connectedOnce = false;
    
    if (_isConnected == true)
        connectedOnce = true;

    while ((_isConnected == false && connectOnce == true) || connectOnce == false)
    {
        if (_isConnected != true)
        {
            TryConnect();
        }
        //wait with next try for specified time
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }
}

void SimController::SearchForServer(unsigned period, bool stopSearchAfterFirstConnection)
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

    _searchThread->join();
    std::cout << "Search terminated\r\n";

    if (_searchThread == nullptr)
        return;

    delete _searchThread;
    _searchThread = nullptr;
}
