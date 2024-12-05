#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Service.h"

class Controller
{
public:
    Controller();
    void setup();
    void update(byte command);
    void streamData();
    bool getState(byte state);
    void roomManagement(byte state);

private:
    Service service; 
};

#endif // CONTROLLER_H
