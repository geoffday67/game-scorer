#include "Players.h"
#include "ChoosePlayers.h"
#include "MainScreen.h"

classChoosePlayers ChoosePlayers;
extern char buffer[];

void classChoosePlayers::showOrder() {
    int n = 0;

    while (n < Players.count() && porder[n] != -1) {
        sprintf (buffer, "%2d", n + 1);
        Output.showText(orderX, porder[n], buffer, COLOUR_ACCENT);
        n++;
    }
}

bool classChoosePlayers::isChosen (int p) {
    int n = 0;

    while (n < Players.count() && porder[n] != -1) {
        if (porder[n] == p) {
            return true;
        }
        n++;
    }
    return false;
}

void classChoosePlayers::activate() {
    for (int n = 0; n < Players.count(); n++) {
        porder[n] = -1;
    }
    next = 0;

    char *pname;
    orderX = 0;
    Output.clear();
    strcpy_P(buffer, pgame_P);
    strcat_P(buffer, PSTR(" PLAYERS"));
    Output.showTitle(buffer);
    Output.showFooter_P(PSTR("* Cancel"), PSTR("# Continue"));
    for (int n = 0; n < Players.count(); n++) {
        pname = Players.get(n)->pname;
        sprintf (buffer, "%d) %s", n + 1, pname);
        Output.showText(0, n, buffer, COLOUR_LIGHT_PRIMARY);
        if ((int) strlen(pname) > orderX) {
            orderX = strlen(pname);
        }
    }
    orderX += 5;
    Output.showText_P(9, 10, PSTR("1-9 Choose player"), COLOUR_PRIMARY);

    EventManager.addListener(EVENT_KEY, this);
}

void classChoosePlayers::deactivate() {
    EventManager.removeListener(this);
}

void classChoosePlayers::setChosen() {
    count = 0;
    while (count < Players.count() && porder[count] != -1) {
        pplayers[count] = Players.get(porder[count]);
        count++;
    }
}

void classChoosePlayers::onEvent(Event* pevent) {
    int p;

    if (pevent->type != EVENT_KEY)
        return;

    KeyEvent *pkey = (KeyEvent*) pevent;

    if (pkey->key == KEY_STAR) {
        this->deactivate();
        MainScreen.activate();
    } else if (pkey->key == KEY_HASH) {
        setChosen();
        this->deactivate();
        pcontinue->activate();
    } else if (pkey->key >= KEY_1 && pkey->key <= Players.count()) {
        p = pkey->key - KEY_1;
        if (!isChosen (p)) {
            porder[next++] = p;
            showOrder();
        }
    }
}
