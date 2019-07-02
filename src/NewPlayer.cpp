#include "NewPlayer.h"
#include "PlayersScreen.h"
#include "Players.h"

classNewPlayer NewPlayer;

void classNewPlayer::setUppercase() {
    palphabet_P = PSTR("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    Output.showText_P(0, 2,  PSTR("A B C D E F"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 4,  PSTR("G H I J K L"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 6,  PSTR("M N O P Q R"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 8,  PSTR("S T U V W X"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 10, PSTR("W Z"), COLOUR_LIGHT_PRIMARY);

    showHighlight(index);
}

void classNewPlayer::setLowercase() {
    palphabet_P = PSTR("abcdefghijklmnopqrstuvwxyz");

    Output.showText_P(0, 2,  PSTR("a b c d e f"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 4,  PSTR("g h i j k l"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 6,  PSTR("m n o p q r"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 8,  PSTR("s t u v w x"), COLOUR_LIGHT_PRIMARY);
    Output.showText_P(0, 10, PSTR("w z"), COLOUR_LIGHT_PRIMARY);

    showHighlight(index);
}

void classNewPlayer::showName() {
    Output.showText (6, 0, name, COLOUR_ACCENT);
    Output.showText_P (6 + strlen(name), 0, PSTR("\xDB "), COLOUR_ACCENT);
}

void classNewPlayer::showNormal(int n) {
    Output.showChar ((n % 6) * 2, 2 + (n / 6) * 2, pgm_read_byte(palphabet_P + n), COLOUR_LIGHT_PRIMARY);
}

void classNewPlayer::showHighlight(int n) {
    Output.showChar ((n % 6) * 2, 2 + (n / 6) * 2, pgm_read_byte(palphabet_P + n), COLOUR_ACCENT);
}

void classNewPlayer::activate() {
    Output.clear();
    Output.showTitle_P(PSTR("NEW PLAYER"));
    Output.showFooter_P(PSTR("* Cancel"), PSTR("# Save"));

    Output.showText_P(0, 0, PSTR("Name:"), COLOUR_TEXT);
    name [0] = 0;
    showName();

    Output.showText_P(19, 3, PSTR("2"), COLOUR_PRIMARY);
    Output.showText_P(19, 4, PSTR("\x18"), COLOUR_PRIMARY);
    Output.showText_P(17, 5, PSTR("4\x1B \x1A"), COLOUR_PRIMARY);
    Output.showText_P(21, 5, PSTR("6"), COLOUR_PRIMARY);
    Output.showText_P(19, 6, PSTR("\x19"), COLOUR_PRIMARY);
    Output.showText_P(19, 7, PSTR("8"), COLOUR_PRIMARY);

    Output.showText_P(14, 9, PSTR("5 Use letter"), COLOUR_PRIMARY);
    Output.showText_P(14, 10, PSTR("0 Backspace"), COLOUR_PRIMARY);

    index = 0;
    setUppercase();

    EventManager.addListener(EVENT_KEY, this);
}

void classNewPlayer::deactivate() {
    EventManager.removeListener(this);
}

void classNewPlayer::onEvent(Event* pevent) {
    if (pevent->type != EVENT_KEY)
        return;

    KeyEvent *pkey = (KeyEvent*) pevent;
    int n;
    Player *pplayer;

    switch (pkey->key) {
        case KEY_STAR:
            this->deactivate();
            PlayersScreen.activate();
            break;
        case KEY_HASH:
            pplayer = new Player(name);
            Players.add(pplayer);
            Players.save();
            this->deactivate();
            PlayersScreen.activate();
            break;
        case KEY_6:
            if (index % 6 < 5) {
                showNormal(index);
                index++;
                showHighlight(index);
            }
            break;
        case KEY_4:
            if (index % 6 > 0) {
                showNormal(index);
                index--;
                showHighlight(index);
            }
            break;
        case KEY_8:
            if (index <= 19) {
                showNormal(index);
                index += 6;
                showHighlight(index);
            }
            break;
        case KEY_2:
            if (index >= 6) {
                showNormal(index);
                index -= 6;
                showHighlight(index);
            }
            break;
        case KEY_5:
            n = strlen(name);
            name[n] = pgm_read_byte(palphabet_P + index);
            name[n+1] = 0;
            showName();
            if (strlen(name) == 1) setLowercase();
            break;
        case KEY_0:
            n = strlen(name);
            if (n > 0) {
                name[n - 1] = 0;
                showName();
            }
            if (strlen(name) == 0) setUppercase();
            break;
    }     
}
