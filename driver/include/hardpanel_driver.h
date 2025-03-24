#pragma once

#include <windows.h>
#include <bluetoothapis.h>

#ifdef HARDPANEL_DRIVER_EXPORTS
#define HARDPANEL_API __declspec(dllexport)
#else
#define HARDPANEL_API __declspec(dllimport)
#endif

namespace hardpanel {

class HARDPANEL_API Driver {
public:
    Driver();
    ~Driver();

    // Initialize the driver
    bool Initialize();

    // Connect to a HardPanel device
    bool Connect(const wchar_t* deviceAddress);

    // Disconnect from the device
    void Disconnect();

    // Send data to the device
    bool SendData(const uint8_t* data, size_t length);

    // Register callback for receiving data
    using DataCallback = std::function<void(const uint8_t* data, size_t length)>;
    void SetDataCallback(DataCallback callback);

private:
    HANDLE hDevice;
    DataCallback dataCallback;
    bool isConnected;
};

} // namespace hardpanel 