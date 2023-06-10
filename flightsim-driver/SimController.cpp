#include <iostream>
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
