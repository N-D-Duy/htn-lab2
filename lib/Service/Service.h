#ifndef SERVICE_H
#define SERVICE_H

#include <Firebase_ESP_Client.h>

class Service {
public:
    Service();
    //hallway
    void turnOnLightHallway();
    void turnOffLightHallway();
    bool isLightOnHallway();

    //yard
    void turnOnLightYard();
    void turnOffLightYard();
    bool isLightOnYard();


    //meeting room
    void turnOnLightMeetingRoom();
    void turnOffLightMeetingRoom();
    void turnOnProjector();
    void turnOffProjector();
    bool isLightOnMeetingRoom();
    bool isProjectorOn();

    //dormitory
    void unlockDoor();
    void lockDoor();
    void turnOnLightDormitory();
    void turnOffLightDormitory();
    bool isDoorLocked();
    bool isLightOnDormitory();

    
    void initService();
    void updateData(String path, String key, bool value);
    void getFirebaseData();

private:
    bool _isLightOnHallway;
    bool _isLightOnYard;
    bool _isLightOnMeetingRoom;
    bool _isProjectorOn;
    bool _isDoorLocked;
    bool _isLightOnDormitory;
};

#endif