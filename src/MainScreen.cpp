#include "MainScreen.h"
#include "PlayersScreen.h"
#include "ChoosePlayers.h"
#include "Games/Scrabble.h"
#include "Games/Darts.h"
#include "Games/Qwirkle.h"

classMainScreen MainScreen;

void classMainScreen::activate() {
    Output.clear();
    Output.showTitle_P(PSTR("IMMA GONNA WIN!!!!"));

    Output.showText_P(0, 0, PSTR("1) Play Scrabble"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 1, PSTR("2) Play darts"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 2, PSTR("3) Play Qwirkle"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 4, PSTR("9) List of players"), COLOUR_LIGHT_PRIMARY);

    EventManager.addListener(EVENT_KEY, this);
}

void classMainScreen::deactivate() {
    EventManager.removeListener(this);
}

void classMainScreen::onEvent(Event* pevent) {
    if (pevent->type != EVENT_KEY)
        return;

    KeyEvent *pkey = (KeyEvent*) pevent;

    switch (pkey->key) {
        case KEY_9:
            this->deactivate();
            PlayersScreen.activate();
            break;
        case KEY_1:
            ChoosePlayers.pgame_P = PSTR("SCRABBLE");
            ChoosePlayers.pcontinue = new classScrabble();
            this->deactivate();
            ChoosePlayers.activate();
            break;
        case KEY_2:
            ChoosePlayers.pgame_P = PSTR("DARTS");
            ChoosePlayers.pcontinue = new classDarts();
            this->deactivate();
            ChoosePlayers.activate();
            break;
        case KEY_3:
            ChoosePlayers.pgame_P = PSTR("QWIRKLE");
            ChoosePlayers.pcontinue = new Qwirkle();
            this->deactivate();
            ChoosePlayers.activate();
            break;
    }
}
