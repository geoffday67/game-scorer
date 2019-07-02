#ifndef __QWIRKLE__
#define __QWIRKLE__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"

class Qwirkle: public Screen, EventReceiver {
private:
    unsigned char count, current, scoreX;
    int entry;
    int *pscore;
    void showScores();
    void showEntry();

public:
    virtual void activate();
    virtual void deactivate();
    virtual void onEvent(Event* pevent);
};

#endif