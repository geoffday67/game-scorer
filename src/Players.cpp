#include <string.h>
#include "Players.h"
#include <EEPROM.h>

classPlayers Players;

/******************************************************************************/
Player::Player() {}

Player::Player(const char *psrc_name) {
    pname = new char [strlen (psrc_name) + 1];
    strcpy (pname, psrc_name);
}

Player::~Player() {
    delete [] pname;
}

/******************************************************************************/
void classPlayers::add(Player *pplayer){
    pplayers[playerCount++] = pplayer;
}

Player* classPlayers::get(int n){
    return pplayers[n];
}

void classPlayers::remove(int n) {
    int dest = 0;
    for (int src = 0; src < playerCount; src++) {
        if (src == n) {
            delete pplayers[src];
        } else {
            pplayers[dest++] = pplayers[src];
        }
    }
    playerCount--;
}

int classPlayers::count() {
    return playerCount;
}

int writeString(int index, char *pstring) {
    EEPROM.write(index++, strlen(pstring));
    while (*pstring) {
        EEPROM.write (index++, *pstring++);
    }
    return index;
}

int readString(int index, char **ppstring) {
    unsigned char length = EEPROM.read(index++);
    *ppstring = new char [length + 1];
    unsigned char n;
    for (n = 0; n < length; n++) {
        (*ppstring)[n] = EEPROM.read(index++);
    }
    (*ppstring)[n] = 0;
    return index;
}

void classPlayers::save() {
    EEPROM.write(0, 'P');
    EEPROM.write(1, playerCount);

    int index = 2;
    for (int n = 0; n < playerCount; n++) {
        index = writeString(index, pplayers[n]->pname);
    }
}

void classPlayers::restore() {
    Player *pplayer;
    int count;

    if (EEPROM.read(0) != 'P')
        return;

    count = EEPROM.read(1);
    int index = 2;
    for (int n = 0; n < count; n++) {
        pplayer = new Player();
        index = readString(index, &(pplayer->pname));
        add(pplayer);
    }
}