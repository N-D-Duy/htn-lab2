#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Service.h"

class Controller
{
public:
    Controller();
    void setup();

private:
    Service service; 
};

#endif // CONTROLLER_H
