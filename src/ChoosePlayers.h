#ifndef __CHOOSE_PLAYERS__
#define __CHOOSE_PLAYERS__

#include "Screen.h"
#include "EventManager.h"
#include "EventReceiver.h"
#include "Players.h"
#include <vector>

class classChoosePlayers: public Screen, EventReceiver {
private:
    int porder[MAX_PLAYERS];
    int next, orderX;
    void setChosen();
    void showOrder();
    bool isChosen(int n);

public:
    Player *pplayers[MAX_PLAYERS];
    unsigned char count;
    const char *pgame_P;
    Screen *pcontinue;
    virtual void activate();
    virtual void deactivate();
    virtual void onEvent(Event* pevent);
};

extern classChoosePlayers ChoosePlayers;

#endif