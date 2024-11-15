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
String streamPath = "/lab2";

Service::Service()
{
    Serial.begin(115200);
}

void Service::getFirebaseData()
{
    FirebaseJson jsonData;
    if (Firebase.RTDB.getJSON(&fbdo, streamPath.c_str()))
    {
        if (fbdo.dataType() != "null")
        {
            jsonData.setJsonData(fbdo.jsonString());

            FirebaseJsonData jsonDataResult;
            
            if (jsonData.get(jsonDataResult, "light") && jsonDataResult.type == "boolean")
            {
                _isLightOn = jsonDataResult.boolValue;
            }

            
            if (jsonData.get(jsonDataResult, "fan") && jsonDataResult.type == "boolean")
            {
                _isFanOn = jsonDataResult.boolValue;
            }

            
            if (jsonData.get(jsonDataResult, "conditioner") && jsonDataResult.type == "boolean")
            {
                _isAirConditionerOn = jsonDataResult.boolValue;
            }

            
            if (jsonData.get(jsonDataResult, "pump") && jsonDataResult.type == "boolean")
            {
                _isWaterPumpOn = jsonDataResult.boolValue;
            }
            Serial.printf("Light: %d, Fan: %d, Air Conditioner: %d, Water Pump: %d\n", _isLightOn, _isFanOn, _isAirConditionerOn, _isWaterPumpOn);
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
}

void Service::initService()
{
    Serial.println("Initializing service...");
    if(API_KEY == "" || DATABASE_URL == "" || USER_EMAIL == "" || USER_PASSWORD == "") {
        Serial.println("Credentials is not set!");
        return;
    }
    int wifiTimeout = 30;
    WiFi.begin(ssid, password, WIFI_CHANNEL);

    while (WiFi.status() != WL_CONNECTED && wifiTimeout > 0) {
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


void Service::turnOffLight(){
    FirebaseJson jsonData;
    jsonData.add("light", false);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Light turned off");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

void Service::turnOnLight(){
    FirebaseJson jsonData;
    jsonData.add("light", true);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Light turned on");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

void Service::turnOffFan(){
    FirebaseJson jsonData;
    jsonData.add("fan", false);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Fan turned off");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

void Service::turnOnFan(){
    FirebaseJson jsonData;
    jsonData.add("fan", true);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Fan turned on");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}


void Service::turnOffAirConditioner(){
    FirebaseJson jsonData;
    jsonData.add("conditioner", false);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Air Conditioner turned off");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

void Service::turnOnAirConditioner(){
    FirebaseJson jsonData;
    jsonData.add("conditioner", true);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Air Conditioner turned on");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

void Service::turnOffWaterPump(){
    FirebaseJson jsonData;
    jsonData.add("pump", false);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Water Pump turned off");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

void Service::turnOnWaterPump(){
    FirebaseJson jsonData;
    jsonData.add("pump", true);
    if (Firebase.RTDB.updateNode(&fbdo, streamPath.c_str(), &jsonData))
    {
        Serial.println("Water Pump turned on");
    }
    else
    {
        Serial.println(fbdo.errorReason());
    }
}

bool Service::isLightOn(){
    return _isLightOn;
}

bool Service::isFanOn(){
    return _isFanOn;
}

bool Service::isAirConditionerOn(){
    return _isAirConditionerOn;
}

bool Service::isWaterPumpOn(){
    return _isWaterPumpOn;
}