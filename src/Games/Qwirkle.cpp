#include "Players.h"
#include "ChoosePlayers.h"
#include "Qwirkle.h"

extern char buffer [32];

void Qwirkle::showScores() {
    for (int n = 0; n < count; n++) {
        sprintf (buffer, "%4d", pscore[n]);
        Output.showText(scoreX, n, buffer, n == current ? COLOUR_ACCENT : COLOUR_LIGHT_PRIMARY);
    }
}

void Qwirkle::showEntry() {
    buffer [0] = 0;
    if (entry > 0) {
        itoa (entry, buffer, 10);
    }
    strcat_P (buffer, PSTR("\xDB    "));
    Output.showText (17, count + 2, buffer, COLOUR_ACCENT);
}

void Qwirkle::activate() {
    count = ChoosePlayers.count;
    current = 0;
    entry = 0;

    Output.clear();
    Output.showTitle_P(PSTR("QWIRKLE"));
    Output.showFooter_P(PSTR("* Backspace"), PSTR("# Add"));

    pscore = new int [count];
    scoreX = 0;
    char *pname;
    for (int n = 0; n < count; n++) {
        pscore[n] = 0;
        pname = ChoosePlayers.pplayers[n]->pname;
        Output.showText(0, n, pname, COLOUR_LIGHT_PRIMARY);
        if ((int) strlen(pname) > scoreX) {
            scoreX = strlen(pname);
        }
    }
    scoreX += 2;
    showScores();

    Output.showText_P(0, count + 2, PSTR("Score this turn:"), COLOUR_PRIMARY);
    showEntry();

    EventManager.addListener(EVENT_KEY, this);
}

void Qwirkle::deactivate() {
    delete [] pscore;
    EventManager.removeListener(this);
}

void Qwirkle::onEvent(Event* pevent) {
    if (pevent->type != EVENT_KEY)
        return;

    KeyEvent *pkey = (KeyEvent*) pevent;

    if (pkey->key == KEY_HASH) {
        pscore[current] += entry;
        entry = 0;
        if (++current == count) {
            current = 0;
        }
        showScores();
        showEntry();
    } else if (pkey->key == KEY_STAR) {
        if (entry > 0) {
            entry = entry / 10;
            showEntry();
        }
    } else if (pkey->key >= KEY_0 && pkey->key <= KEY_9) {
        entry = (entry * 10) + pkey->key - KEY_0;
        showEntry();
    }
}
