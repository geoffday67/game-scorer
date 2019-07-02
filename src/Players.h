#ifndef __PLAYERS__
#define __PLAYERS__

#define MAX_PLAYERS     9

class Player {
public:
    Player();
    Player(const char *psrc_name);
    virtual ~Player();
    char *pname = 0;
};

class classPlayers {
private:
    Player *pplayers[MAX_PLAYERS];
    unsigned char playerCount = 0;
    
public:
    int count();
    void add(Player *pplayer);
    Player* get(int n);
    void remove(int n);
    void save();
    void restore();
};

extern classPlayers Players;

#endif
