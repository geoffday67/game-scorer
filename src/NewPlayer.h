#ifndef __NEW_PLAYER__
#define __NEW_PLAYER__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"

class classNewPlayer: public Screen, EventReceiver {
public:
    virtual void activate();
    virtual void deactivate();
    virtual void onEvent(Event* pevent);

private:
    char name [32];
    char *palphabet_P;
    int index;

    void setUppercase();
    void setLowercase();
    void showName();
    void showHighlight(int n);
    void showNormal(int n);
};

extern classNewPlayer NewPlayer;

#endif