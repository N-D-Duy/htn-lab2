#include "Service.h"
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <time.h>
#include "config.h"

// WiFi credentials
const char *ssid = "Wokwi-GUEST";
const char *password = "";
#define WIFI_CHANNEL 6

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String dorm = "/dorm";
String yard = "/yard";
String meetingRoom = "/meetingRoom";
String hallway = "/hallway";

Service::Service()
{
    Serial.begin(115200);
    delay(100);
    while (Serial.available() > 0)
    {
        Serial.read();
    }
    
}

void Service::getFirebaseData()
{
    FirebaseJson jsonData;
    String streamPath;
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            streamPath = dorm;
            if (Firebase.RTDB.getJSON(&fbdo, streamPath.c_str()))
            {
                if (fbdo.dataType() != "null")
                {
                    jsonData.setJsonData(fbdo.jsonString());

                    FirebaseJsonData jsonDataResult;

                    if (jsonData.get(jsonDataResult, "door") && jsonDataResult.type == "boolean")
                    {
                        _isDoorLocked = jsonDataResult.boolValue;
                    }

                    if (jsonData.get(jsonDataResult, "light") && jsonDataResult.type == "boolean")
                    {
                        _isLightOnDormitory = jsonDataResult.boolValue;
                    }
                }
                else
                {
                    Serial.println("No data available");
                }
            }
            else
            {
                Serial.println(fbdo.errorReason());
            }
            break;

        case 1:
            streamPath = yard;
            if (Firebase.RTDB.getJSON(&fbdo, streamPath.c_str()))
            {
                if (fbdo.dataType() != "null")
                {
                    jsonData.setJsonData(fbdo.jsonString());

                    FirebaseJsonData jsonDataResult;

                    if (jsonData.get(jsonDataResult, "light") && jsonDataResult.type == "boolean")
                    {
                        _isLightOnYard = jsonDataResult.boolValue;
                    }
                }
                else
                {
                    Serial.println("No data available");
                }
            }
            else
            {
                Serial.println(fbdo.errorReason());
            }
            break;

        case 2:
            streamPath = meetingRoom;
            if (Firebase.RTDB.getJSON(&fbdo, streamPath.c_str()))
            {
                if (fbdo.dataType() != "null")
                {
                    jsonData.setJsonData(fbdo.jsonString());

                    FirebaseJsonData jsonDataResult;

                    if (jsonData.get(jsonDataResult, "light") && jsonDataResult.type == "boolean")
                    {
                        _isLightOnMeetingRoom = jsonDataResult.boolValue;
                    }

                    if (jsonData.get(jsonDataResult, "projector") && jsonDataResult.type == "boolean")
                    {
                        _isProjectorOn = jsonDataResult.boolValue;
                    }
                }
                else
                {
                    Serial.println("No data available");
                }
            }

            else
            {
                Serial.println(fbdo.errorReason());
            }
            break;

        case 3:
            streamPath = hallway;
            if (Firebase.RTDB.getJSON(&fbdo, streamPath.c_str()))
            {
                if (fbdo.dataType() != "null")
                {
                    jsonData.setJsonData(fbdo.jsonString());

                    FirebaseJsonData jsonDataResult;

                    if (jsonData.get(jsonDataResult, "light") && jsonDataResult.type == "boolean")
                    {
                        _isLightOnHallway = jsonDataResult.boolValue;
                    }
                }
                else
                {
                    Serial.println("No data available");
                }
            }
            else
            {
                Serial.println(fbdo.errorReason());
            }
            break;
        }
    }
}

void Service::initService()
{
    Serial.println("Initializing service...");
    if (API_KEY == "" || DATABASE_URL == "" || USER_EMAIL == "" || USER_PASSWORD == "")
    {
        Serial.println("Credentials is not set!");
        return;
    }
    int wifiTimeout = 30;
    WiFi.begin(ssid, password, WIFI_CHANNEL);

    while (WiFi.status() != WL_CONNECTED && wifiTimeout > 0)
    {
        delay(500);
        Serial.print(".");
        wifiTimeout--;
    }
    Serial.println("\nConnected to WiFi");

    // Firebase configuration
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);
    config.token_status_callback = tokenStatusCallback;
    config.max_token_generation_retry = 5;

    // Connect to Firebase
    Firebase.begin(&config, &auth);

    // Initialize NTP
    configTime(0, 0, "pool.ntp.org");
    delay(2000); // Wait for time to synchronize
}



void Service::updateData(String path, String key, bool value)
{
    FirebaseJson jsonData;
    jsonData.add(key, value);
    if (Firebase.RTDB.updateNode(&fbdo, path.c_str(), &jsonData))
    {
        // Serial.println("Data updated");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

//hallway
void Service::turnOnLightHallway()
{
    updateData(hallway, "light", true);
}

void Service::turnOffLightHallway()
{
    updateData(hallway, "light", false);
}

bool Service::isLightOnHallway()
{
    return _isLightOnHallway;
}

//yard
void Service::turnOnLightYard()
{
    updateData(yard, "light", true);
}

void Service::turnOffLightYard()
{
    updateData(yard, "light", false);
}

bool Service::isLightOnYard()
{
    return _isLightOnYard;
}

//meeting room
void Service::turnOnLightMeetingRoom()
{
    updateData(meetingRoom, "light", true);
}

void Service::turnOffLightMeetingRoom()
{
    updateData(meetingRoom, "light", false);
}

void Service::turnOnProjector()
{
    updateData(meetingRoom, "projector", true);
}

void Service::turnOffProjector()
{
    updateData(meetingRoom, "projector", false);
}

bool Service::isLightOnMeetingRoom()
{
    return _isLightOnMeetingRoom;
}

bool Service::isProjectorOn()
{
    return _isProjectorOn;
}

//dormitory
void Service::unlockDoor()
{
    updateData(dorm, "door", false);
}

void Service::lockDoor()
{
    updateData(dorm, "door", true);
}

void Service::turnOnLightDormitory()
{
    updateData(dorm, "light", true);
}

void Service::turnOffLightDormitory()
{
    updateData(dorm, "light", false);
}

bool Service::isDoorLocked()
{
    return _isDoorLocked;
}

bool Service::isLightOnDormitory()
{
    return _isLightOnDormitory;
}