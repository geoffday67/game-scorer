#ifndef __PLAYER_DETAILS__
#define __PLAYER_DETAILS__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"

class classPlayerDetails: public Screen, EventReceiver {
public:
    int index;
    virtual void activate();
    virtual void deactivate();
    virtual void onEvent(Event* pevent);
};

extern classPlayerDetails PlayerDetails;

#endif