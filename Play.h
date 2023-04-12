//
// Created by kubab on 05/01/2023.
//

#ifndef SAPPER_PLAY_H
#define SAPPER_PLAY_H
#include "Board.h"

class Play {
protected:
    Board *board;
public:
    Board *getBoard() const;

protected:
    int moveCount = 0;
    bool end = false;
    bool win = false;
public:
    void setWin(bool win);

public:
    bool isWin() const;

protected:
    int discover(int x, int y);
public:
    Play(int x, int y, int mines);
    Play();
    ~Play();
    void restart();
    bool move(int x, int y);
    void flag(int x, int y);
    Play& operator=(const Play& play);
    void setEnd();
    bool getEnd() const;
};
#endif //SAPPER_PLAY_H
