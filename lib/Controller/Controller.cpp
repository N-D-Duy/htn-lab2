#include "Controller.h"

Controller::Controller() : service() 
{
}

void Controller::setup()
{
    service.initService();
}
