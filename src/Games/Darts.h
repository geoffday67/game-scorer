#ifndef __DARTS__
#define __DARTS__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"

class classDarts: public Screen, EventReceiver {
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