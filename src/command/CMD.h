#ifndef CMD_H
#define CMD_H

#include <string>

namespace CMD {
    // Command constants
    const std::byte LED_ON = 0x01;
    const std::byte LED_OFF = 0x02;
    const std::byte CONDITIONER_ON = 0x03;
    const std::byte CONDITIONER_OFF = 0x04;
    const std::byte FAN_ON = 0x05;
    const std::byte FAN_OFF = 0x06;
    const std::byte PUMP_ON = 0x07;
    const std::byte PUMP_OFF = 0x08;
}

#endif