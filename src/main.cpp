#include "Controller.h"
#include "CMD.h"
#include "STATE.h"

Controller controller;
#define LED_PIN 26



void updateLight(){
    if(controller.getState(STATE::LED)){
        Serial.println("Light is on");
        digitalWrite(LED_PIN, HIGH);
    }else{
        Serial.println("Light is off");
        digitalWrite(LED_PIN, LOW);
    }
}

void updateFan(){
    if(controller.getState(STATE::FAN)){
        // Turn on fan
    }else{
        // Turn off fan
    }
}

void updateAirConditioner(){
    if(controller.getState(STATE::CONDITIONER)){
        // Turn on air conditioner
    }else{
        // Turn off air conditioner
    }
}

void updateWaterPump(){
    if(controller.getState(STATE::PUMP)){
        // Turn on water pump
    }else{
        // Turn off water pump
    }
}

void updateDevices(){
    updateLight();
    updateFan();
    updateAirConditioner();
    updateWaterPump();
};




void setup()
{
    pinMode(LED_PIN, OUTPUT);
    controller.setup();
}

void loop()
{
    controller.streamData();
    updateDevices();
    Serial.printf("Light: %s", controller.getState(STATE::LED) ? "ON" : "OFF");
    Serial.println();
    delay(10); 
}



