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
    case CMD::LED_OFF_HALLWAY:
        service.turnOffLightHallway();
        break;
    case CMD::LED_ON_HALLWAY:
        service.turnOnLightHallway();
        break;

    case CMD::LED_OFF_YARD:
        service.turnOffLightYard();
        break;

    case CMD::LED_ON_YARD:
        service.turnOnLightYard();
        break;

    case CMD::LED_OFF_MEETING_ROOM:
        service.turnOffLightMeetingRoom();
        break;

    case CMD::LED_ON_MEETING_ROOM:
        service.turnOnLightMeetingRoom();
        break;

    case CMD::PROJECTOR_OFF:
        service.turnOffProjector();
        break;

    case CMD::PROJECTOR_ON:
        service.turnOnProjector();
        break;

    case CMD::DOOR_LOCK:
        service.lockDoor();
        break;

    case CMD::DOOR_UNLOCK:
        service.unlockDoor();
        break;

    case CMD::LED_OFF_DORMITORY:
        service.turnOffLightDormitory();
        break;

    case CMD::LED_ON_DORMITORY:
        service.turnOnLightDormitory();
        break;

    default:
        break;
    }
}

void Controller::roomManagement(byte state)
{
    switch (state)
    {
    case STATE::MEETING_ROOM_EMPTY:
        if (service.isLightOnMeetingRoom())
        {
            service.turnOffLightMeetingRoom();
        }

        if (service.isProjectorOn())
        {
            service.turnOffProjector();
        }
        break;
    case STATE::MEETING_ROOM_OCCUPIED:
        if (!service.isLightOnMeetingRoom())
        {
            service.turnOnLightMeetingRoom();
        }
        break;

    case STATE::DORMITORY_LOCKED:
        if (service.isLightOnDormitory())
        {
            service.turnOffLightDormitory();
        }
        break;

    case STATE::DORMITORY_UNLOCKED:
        if (!service.isLightOnDormitory())
        {
            service.turnOnLightDormitory();
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
    case STATE::HALLWAY_LIGHT_ON:
        return service.isLightOnHallway();
    case STATE::HALLWAY_LIGHT_OFF:
        return !service.isLightOnHallway();
    case STATE::YARD_LIGHT_ON:
        return service.isLightOnYard();
    case STATE::YARD_LIGHT_OFF:
        return !service.isLightOnYard();
    case STATE::MEETING_ROOM_LIGHT_ON:
        return service.isLightOnMeetingRoom();
    case STATE::MEETING_ROOM_LIGHT_OFF:
        return !service.isLightOnMeetingRoom();
    case STATE::PROJECTOR_ON:
        return service.isProjectorOn();
    case STATE::PROJECTOR_OFF:
        return !service.isProjectorOn();
    case STATE::DORMITORY_LIGHT_ON:
        return service.isLightOnDormitory();
    case STATE::DORMITORY_LIGHT_OFF:
        return !service.isLightOnDormitory();
    case STATE::DOOR_UNLOCK:
        return !service.isDoorLocked();
    case STATE::DOOR_LOCK:
        return service.isDoorLocked();
    default:
        return false;
    }
}

void Controller::streamData()
{
    service.getFirebaseData();
}
