#ifndef __PLAYERS_SCREEN__
#define __PLAYERS_SCREEN__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"

class classPlayersScreen: public Screen, EventReceiver {
public:
    classPlayersScreen ();
    virtual ~classPlayersScreen();

    virtual void activate();
    virtual void deactivate();
    virtual void onEvent(Event* pevent);
};

extern classPlayersScreen PlayersScreen;

#endif