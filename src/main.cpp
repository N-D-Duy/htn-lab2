#include <thread> 
#include <atomic>
#include "Controller.h"
#include "CMD.h"
#include "STATE.h"

Controller controller;
std::atomic<bool> roomstate(false);
#define LED_PIN 26

void updateLight() {
    if (controller.getState(STATE::LED)) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
}

void updateFan() {
    if (controller.getState(STATE::FAN)) {
        // Turn on fan
    } else {
        // Turn off fan
    }
}

void updateAirConditioner() {
    if (controller.getState(STATE::CONDITIONER)) {
        // Turn on air conditioner
    } else {
        // Turn off air conditioner
    }
}

void updateWaterPump() {
    if (controller.getState(STATE::PUMP)) {
        // Turn on water pump
    } else {
        // Turn off water pump
    }
}

void updateDevices() {
    updateLight();
    updateFan();
    updateAirConditioner();
    updateWaterPump();
}

void manageRoomState() {
    while (true) {
        int command;
        if (Serial.available() > 0) {
            command = Serial.parseInt();
            if (command == 1) {
                roomstate = false;
                Serial.println("Room state set to EMPTY");
            } else if (command == 2) {
                roomstate = true;
                Serial.println("Room state set to OCCUPIED");
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    controller.setup();

    std::thread roomStateThread(manageRoomState);
    roomStateThread.detach();
}

void loop() {
    if (roomstate) {
        controller.roomManagement(STATE::ROOM_OCCUPIED);
    } else {
        controller.roomManagement(STATE::ROOM_EMPTY);
    }
    controller.streamData();
    updateDevices();
    delay(10);
}
