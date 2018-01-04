
#include <iostream>

#include "Controller.h"
#include "Hub.h"
#include "Event.h"

Controller::Controller(Hub* _hub)
{
    _hub->Subscribe(this);
}

Controller::~Controller()
{}

void Controller::OnEvent(Event* _event)
{
    std::cout << _event->m_topic << std::endl;
}
