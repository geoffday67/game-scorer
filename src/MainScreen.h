#ifndef __MAIN_SCREEN__
#define __MAIN_SCREEN__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"

class classMainScreen: public Screen, EventReceiver {
public:
    virtual void activate();
    virtual void deactivate();
    virtual void onEvent(Event* pevent);
};

extern classMainScreen MainScreen;

#endif