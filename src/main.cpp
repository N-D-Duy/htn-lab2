#include <Arduino.h>
#include <atomic>
#include "Controller.h"
#include "CMD.h"
#include "STATE.h"
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <string>

// Define pins
#define LED_YARD 12
#define LED_HALLWAY 32
#define LED_MEETING_ROOM 18
#define LED_DORM 14

#define HALLWAY_SENSOR_PIN 33      // hallway
#define MEETING_ROOM_SENSOR_PIN 19 // meeting room
#define LDR_PIN 34

#define SERVO_PIN 27

#define IR_RECEIVER_PIN 17

Controller controller;
Servo dormServo;
LiquidCrystal_I2C lcd1(0x27, 16, 2);
IRrecv receiver(IR_RECEIVER_PIN);

struct Student
{
    String id;
    String name;
};

Student students[] =
    {
        "1",
        "Nguyen Van A",
        "5",
        "Nguyen Van B",
        "9",
        "Nguyen Van C",
};

int numStudents = sizeof(students) / sizeof(students[0]);
int studentCount = 0;
String currentStudent = "";

// Atomic flags to track device states
std::atomic<bool> light_hallway_state(false);
std::atomic<bool> light_meeting_room_state(false);
std::atomic<bool> yard_light_state(false);
std::atomic<bool> attendance_state(false);

void updateDataFirebase(byte command)
{
    switch (command)
    {
    case CMD::LED_ON_HALLWAY:
        controller.update(CMD::LED_ON_HALLWAY);
        break;

    case CMD::LED_OFF_HALLWAY:
        controller.update(CMD::LED_OFF_HALLWAY);
        break;

    case CMD::LED_ON_YARD:
        controller.update(CMD::LED_ON_YARD);
        break;

    case CMD::LED_OFF_YARD:
        controller.update(CMD::LED_OFF_YARD);
        break;

    case CMD::LED_ON_MEETING_ROOM:
        controller.update(CMD::LED_ON_MEETING_ROOM);
        break;

    case CMD::LED_OFF_MEETING_ROOM:
        controller.update(CMD::LED_OFF_MEETING_ROOM);
        break;
    case CMD::PROJECTOR_ON:
        controller.update(CMD::PROJECTOR_ON);
        break;
    case CMD::PROJECTOR_OFF:
        controller.update(CMD::PROJECTOR_OFF);
        break;
    case CMD::DOOR_UNLOCK:
        controller.update(CMD::DOOR_UNLOCK);
        break;
    case CMD::DOOR_LOCK:
        controller.update(CMD::DOOR_LOCK);
        break;

    default:
        break;
    }
}

void commandUpdater()
{
    if (Serial.available() > 0)
    {
        uint8_t byteCommand = static_cast<uint8_t>(Serial.parseInt());
        Serial.printf("Command received: %d\n", byteCommand);

        switch (byteCommand)
        {
        case CMD::LED_ON_HALLWAY:
            Serial.println("LED_ON_HALLWAY");
            updateDataFirebase(CMD::LED_ON_HALLWAY);
            break;
        case CMD::LED_OFF_HALLWAY:
            Serial.println("LED_OFF_HALLWAY");
            updateDataFirebase(CMD::LED_OFF_HALLWAY);
            break;
        case CMD::LED_ON_YARD:
            Serial.println("LED_ON_YARD");
            updateDataFirebase(CMD::LED_ON_YARD);
            break;
        case CMD::LED_OFF_YARD:
            Serial.println("LED_OFF_YARD");
            updateDataFirebase(CMD::LED_OFF_YARD);
            break;
        case CMD::LED_ON_MEETING_ROOM:
            Serial.println("LED_ON_MEETING_ROOM");
            updateDataFirebase(CMD::LED_ON_MEETING_ROOM);
            break;
        case CMD::LED_OFF_MEETING_ROOM:
            Serial.println("LED_OFF_MEETING_ROOM");
            updateDataFirebase(CMD::LED_OFF_MEETING_ROOM);
            break;
        case CMD::PROJECTOR_ON:
            Serial.println("PROJECTOR_ON");
            updateDataFirebase(CMD::PROJECTOR_ON);
            break;
        case CMD::PROJECTOR_OFF:
            Serial.println("PROJECTOR_OFF");
            updateDataFirebase(CMD::PROJECTOR_OFF);
            break;
        case CMD::DOOR_UNLOCK:
            Serial.println("DOOR_UNLOCK");
            updateDataFirebase(CMD::DOOR_UNLOCK);
            break;
        case CMD::DOOR_LOCK:
            Serial.println("DOOR_LOCK");
            updateDataFirebase(CMD::DOOR_LOCK);
            break;
        case CMD::LED_ON_DORMITORY:
            Serial.println("LED_ON_DORMITORY");
            updateDataFirebase(CMD::LED_ON_DORMITORY);
            break;
        case CMD::LED_OFF_DORMITORY:
            Serial.println("LED_OFF_DORMITORY");
            updateDataFirebase(CMD::LED_OFF_DORMITORY);
            break;
        default:
            Serial.printf("Invalid command: %d\n", byteCommand);
            break;
        }
    }
}

void setup()
{
    // Thiết lập GPIO
    pinMode(LED_YARD, OUTPUT);
    pinMode(LED_HALLWAY, OUTPUT);
    pinMode(LED_MEETING_ROOM, OUTPUT);
    pinMode(LED_DORM, OUTPUT);

    pinMode(HALLWAY_SENSOR_PIN, INPUT);
    digitalWrite(HALLWAY_SENSOR_PIN, LOW);
    pinMode(MEETING_ROOM_SENSOR_PIN, INPUT);
    digitalWrite(MEETING_ROOM_SENSOR_PIN, LOW);

    receiver.enableIRIn();

    dormServo.attach(SERVO_PIN);
    dormServo.write(0);
    lcd1.init();
    pinMode(LDR_PIN, INPUT);
    digitalWrite(LDR_PIN, LOW);

    controller.setup();
}

void updateDeviceState()
{
    if (controller.getState(STATE::HALLWAY_LIGHT_ON))
    {
        digitalWrite(LED_HALLWAY, HIGH);
    }
    else
    {
        digitalWrite(LED_HALLWAY, LOW);
    }

    if (controller.getState(STATE::YARD_LIGHT_ON))
    {
        digitalWrite(LED_YARD, HIGH);
    }
    else
    {
        digitalWrite(LED_YARD, LOW);
    }

    if (controller.getState(STATE::MEETING_ROOM_LIGHT_ON))
    {
        digitalWrite(LED_MEETING_ROOM, HIGH);
    }
    else
    {
        digitalWrite(LED_MEETING_ROOM, LOW);
    }

    if (controller.getState(STATE::DORMITORY_LIGHT_ON))
    {
        digitalWrite(LED_DORM, HIGH);
    }
    else
    {
        digitalWrite(LED_DORM, LOW);
    }

    if (controller.getState(STATE::DOOR_UNLOCK))
    {
        dormServo.write(90);
    }
    else
    {
        dormServo.write(0);
    }

    if (controller.getState(STATE::PROJECTOR_ON))
    {
        lcd1.backlight();
    }
    else
    {
        lcd1.noBacklight();
    }
}

void irHandler()
{
    if (receiver.decode())
    {
        if(studentCount >= numStudents)
        {
            Serial.println("Lop da day");
            receiver.resume();
            return;
        }
        String msv;
        switch (receiver.decodedIRData.command)
        {
        case 48:
            msv = "1";
            break;
        case 24:
            msv = "2";
            break;
        case 122:
            msv = "3";
            break;
        case 16:
            msv = "4";
            break;
        case 56:
            msv = "5";
            break;
        case 90:
            msv = "6";
            break;
        case 66:
            msv = "7";
            break;
        case 74:
            msv = "8";
            break;
        case 82:
            msv = "9";
            break;
        default:
            msv = "";
            break;
        }
        for (const auto &s : students)
        {
            if (s.id == msv)
            {
                attendance_state.store(true);
                studentCount++;
                currentStudent = s.name;
                break;
            }
        }

        if(!attendance_state.load()){
            Serial.println("Sinh vien khong hop le");
        }

        receiver.resume();
    }
    if(attendance_state.load())
    {
        attendance_state.store(false);
        Serial.printf("Student count: %d/%d\n", studentCount, numStudents);
        Serial.printf("Welcome %s\n", currentStudent.c_str());
    }
}

void loop()
{
    irHandler();
    controller.streamData();

    // Update atomic flags for device states
    light_hallway_state.store(digitalRead(HALLWAY_SENSOR_PIN) == HIGH);
    light_meeting_room_state.store(digitalRead(MEETING_ROOM_SENSOR_PIN) == HIGH);
    yard_light_state.store(analogRead(LDR_PIN) > 1000);

    // Firebase update logic
    if (light_hallway_state.load() && controller.getState(STATE::HALLWAY_LIGHT_OFF))
    {
        updateDataFirebase(CMD::LED_ON_HALLWAY);
    }
    else if (!light_hallway_state.load() && controller.getState(STATE::HALLWAY_LIGHT_ON))
    {
        updateDataFirebase(CMD::LED_OFF_HALLWAY);
    }

    if (light_meeting_room_state.load() && controller.getState(STATE::MEETING_ROOM_LIGHT_OFF))
    {
        updateDataFirebase(CMD::LED_ON_MEETING_ROOM);
    }
    else if (!light_meeting_room_state.load() && controller.getState(STATE::MEETING_ROOM_LIGHT_ON))
    {
        updateDataFirebase(CMD::LED_OFF_MEETING_ROOM);
        updateDataFirebase(CMD::PROJECTOR_OFF);
    }

    if (!yard_light_state.load() && controller.getState(STATE::YARD_LIGHT_OFF))
    {
        updateDataFirebase(CMD::LED_ON_YARD);
    }
    else if (yard_light_state.load() && controller.getState(STATE::YARD_LIGHT_ON))
    {
        updateDataFirebase(CMD::LED_OFF_YARD);
    }

    commandUpdater();
    updateDeviceState();
    delay(10);
}
