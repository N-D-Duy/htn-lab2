#ifndef STATE_H
#define STATE_H

#include <cstdint> // Use this header for uint8_t type

namespace STATE {
    // Command constants
    const uint8_t LED = 0x01;
    const uint8_t FAN = 0x02;
    const uint8_t CONDITIONER = 0x03;
    const uint8_t PUMP = 0x04;
    const uint8_t ROOM_EMPTY = 0x05;
    const uint8_t ROOM_OCCUPIED = 0x06;
}

#endif 