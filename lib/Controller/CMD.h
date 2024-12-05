#ifndef CMD_H
#define CMD_H

#include <cstdint>

namespace CMD {
    // Command constants

    //hallway
    const uint8_t LED_ON_HALLWAY = 0x01;
    const uint8_t LED_OFF_HALLWAY = 0x02;
    
    //yard
    const uint8_t LED_ON_YARD = 0x03;
    const uint8_t LED_OFF_YARD = 0x04;

    //meeting room
    const uint8_t LED_ON_MEETING_ROOM = 0x05;
    const uint8_t LED_OFF_MEETING_ROOM = 0x06;
    const uint8_t PROJECTOR_ON = 0x07;
    const uint8_t PROJECTOR_OFF = 0x08;

    //dormitory
    const uint8_t DOOR_UNLOCK = 0x09;
    const uint8_t DOOR_LOCK = 0x0A;
    const uint8_t LED_ON_DORMITORY = 0x0B;
    const uint8_t LED_OFF_DORMITORY = 0x0C;

}

#endif // CMD_H
