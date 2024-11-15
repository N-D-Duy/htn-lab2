#ifndef CMD_H
#define CMD_H

#include <cstdint> // Use this header for uint8_t type

namespace CMD {
    // Command constants
    const uint8_t LED_ON = 0x01;
    const uint8_t LED_OFF = 0x02;
    const uint8_t CONDITIONER_ON = 0x03;
    const uint8_t CONDITIONER_OFF = 0x04;
    const uint8_t FAN_ON = 0x05;
    const uint8_t FAN_OFF = 0x06;
    const uint8_t PUMP_ON = 0x07;
    const uint8_t PUMP_OFF = 0x08;
    const uint8_t SENSOR_TRIGGERED = 0x09;
    const uint8_t SENSOR_RESET = 0x0A;
    const uint8_t FINGER_PRINT_TRIGGERED = 0x0B;
    const uint8_t FINGER_PRINT_ERROR = 0x0D;
    const uint8_t FINGER_PRINT_RESET = 0x0C;
}

#endif // CMD_H
