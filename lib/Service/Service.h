#ifndef SERVICE_H
#define SERVICE_H

#include <Firebase_ESP_Client.h>

class Service {
public:
    Service();
    void turnOnLight();
    void turnOffLight();
    void turnOnAirConditioner();
    void turnOffAirConditioner();
    void turnOnFan();
    void turnOffFan();
    void turnOnWaterPump();
    void turnOffWaterPump();
    bool isLightOn();
    bool isAirConditionerOn();
    bool isFanOn();
    bool isWaterPumpOn();
    void updateDeviceStates();
    void initService();

private:
    void loadCredentials();
    void getFirebaseData();
    bool _isLightOn;
    bool _isAirConditionerOn;
    bool _isFanOn;
    bool _isWaterPumpOn;
};

#endif