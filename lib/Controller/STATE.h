#ifndef STATE_H
#define STATE_H

#include <cstdint> // Use this header for uint8_t type

namespace STATE {
    // Command constants
    const uint8_t MEETING_ROOM_EMPTY = 0x01;
    const uint8_t MEETING_ROOM_OCCUPIED = 0x02;
    const uint8_t DORMITORY_LOCKED = 0x03;
    const uint8_t DORMITORY_UNLOCKED = 0x04;

    //devices state
    const uint8_t HALLWAY_LIGHT_ON = 0x05;
    const uint8_t HALLWAY_LIGHT_OFF = 0x06;
    const uint8_t YARD_LIGHT_ON = 0x07;
    const uint8_t YARD_LIGHT_OFF = 0x08;
    const uint8_t MEETING_ROOM_LIGHT_ON = 0x09;
    const uint8_t MEETING_ROOM_LIGHT_OFF = 0x0A;
    const uint8_t PROJECTOR_ON = 0x0B;
    const uint8_t PROJECTOR_OFF = 0x0C;
    const uint8_t DORMITORY_LIGHT_ON = 0x0D;
    const uint8_t DORMITORY_LIGHT_OFF = 0x0E;
    const uint8_t DOOR_UNLOCK = 0x0F;
    const uint8_t DOOR_LOCK = 0x10;
}

#endif 