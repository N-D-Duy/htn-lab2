#include "Controller.h"
#include "CMD.h"
#include "STATE.h"

Controller::Controller() : service()
{
}

void Controller::setup()
{
    service.initService();
}

void Controller::update(byte command)
{
    switch (command)
    {
    case CMD::LED_ON:
        service.turnOnLight();
        break;
    case CMD::LED_OFF:
        service.turnOffLight();
        break;
    case CMD::FAN_ON:
        service.turnOnFan();
        break;
    case CMD::FAN_OFF:
        service.turnOffFan();
        break;
    case CMD::CONDITIONER_ON:
        service.turnOnAirConditioner();
        break;
    case CMD::CONDITIONER_OFF:
        service.turnOffAirConditioner();
        break;
    case CMD::PUMP_ON:
        service.turnOnWaterPump();
        break;
    case CMD::PUMP_OFF:
        service.turnOffWaterPump();
        break;
    default:
        break;
    }
}

void Controller::roomManagement(byte state)
{
    switch (state)
    {
    case STATE::ROOM_EMPTY:
        if (service.isLightOn())
        {
            service.turnOffLight();
        }
        break;
    case STATE::ROOM_OCCUPIED:
        if (!service.isLightOn())
        {
            service.turnOnLight();
        }
        break;
    default:
        break;
    }
}

bool Controller::getState(byte state)
{
    switch (state)
    {
    case STATE::LED:
        return service.isLightOn();
    case STATE::FAN:
        return service.isFanOn();
    case STATE::CONDITIONER:
        return service.isAirConditionerOn();
    case STATE::PUMP:
        return service.isWaterPumpOn();
    default:
        return false;
    }
}

void Controller::streamData()
{
    service.getFirebaseData();
}
