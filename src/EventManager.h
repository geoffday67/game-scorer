#ifndef __EVENT_MANAGER__
#define __EVENT_MANAGER__

#include <vector>
#include <queue>
#include "Event.h"
#include "EventReceiver.h"

#define EVENT_KEY       1

/*****************************************************************************/
class KeyEvent: public Event {
public:
    KeyEvent(int key);
    int key;
};

/*****************************************************************************/
class RegisteredReceiver {
public:
    RegisteredReceiver(EventReceiver *per, int type);
    EventReceiver *pEventReceiver;
    int type;
    bool fired;
};

/*****************************************************************************/
class classEventManager {
public:
    void addListener(int type, EventReceiver *per);
    void removeListener(EventReceiver *per);
    void queueEvent (Event* pevent);
    void processEvents();

private:
    std::queue<Event*> queueEvents;
    std::vector<RegisteredReceiver> listReceivers;
};

extern classEventManager EventManager;

#endif
