#pragma once

#include "Event.h"
using namespace std;

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;
	EVENT_CLASS_TYPE(WindowClose);
};