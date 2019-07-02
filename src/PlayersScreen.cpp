#include "PlayersScreen.h"
#include "PlayerDetails.h"
#include "Players.h"
#include "NewPlayer.h"
#include "MainScreen.h"

classPlayersScreen::classPlayersScreen () {}

classPlayersScreen::~classPlayersScreen() {}

classPlayersScreen PlayersScreen;

void classPlayersScreen::activate() {
    Output.clear();
    Output.showTitle("PLAYERS");
    Output.showFooter("* Back");

    Output.showText(9, 9, "1-9 Choose player", COLOUR_PRIMARY);
    Output.showText(9, 10, "0 New player", COLOUR_PRIMARY);

    char line [32];
    for (int n = 0; n < Players.count(); n++) {
        sprintf (line, "%d) %s", n + 1, Players.get(n)->pname);
        Output.showText(0, n, line, COLOUR_LIGHT_PRIMARY);
    }

    EventManager.addListener(EVENT_KEY, this);
}

void classPlayersScreen::deactivate() {
    EventManager.removeListener(this);
}

void classPlayersScreen::onEvent(Event* pevent) {
    if (pevent->type != EVENT_KEY)
        return;

    KeyEvent *pkey = (KeyEvent*) pevent;

    if (pkey->key == KEY_0) {
        this->deactivate();
        NewPlayer.activate();
    } else if (pkey->key == KEY_STAR) {
        this->deactivate();
        MainScreen.activate();
    } else if (pkey->key >= KEY_1 && pkey->key <= Players.count()) {
        PlayerDetails.index = pkey->key - 1;
        this->deactivate();
        PlayerDetails.activate();
    }
}
