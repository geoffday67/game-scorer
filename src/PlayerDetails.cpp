#include "PlayersScreen.h"
#include "Players.h"
#include "PlayerDetails.h"

classPlayerDetails PlayerDetails;

void classPlayerDetails::activate() {
    Output.clear();
    Output.showTitle_P(PSTR("PLAYER DETAILS"));
    Output.showFooter_P(PSTR("* Back"));

    Output.showText(0, 0, Players.get(index)->pname, COLOUR_ACCENT);

    Output.showText_P(18, 10, PSTR("0 Delete"), COLOUR_PRIMARY);

    EventManager.addListener(EVENT_KEY, this);
}

void classPlayerDetails::deactivate() {
    EventManager.removeListener(this);
}

void classPlayerDetails::onEvent(Event* pevent) {
    if (pevent->type != EVENT_KEY)
        return;

    KeyEvent *pkey = (KeyEvent*) pevent;

    switch (pkey->key) {
    case KEY_0:
        Players.remove(index);
        Players.save();
        this->deactivate();
        PlayersScreen.activate();
        break;
    case KEY_STAR:
        this->deactivate();
        PlayersScreen.activate();
        break;
    }
}
