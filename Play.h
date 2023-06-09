//
// Created by kubab on 05/01/2023.
//

#ifndef SAPPER_PLAY_H
#define SAPPER_PLAY_H
#include "Board.h"

class Play : public Board {
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
    Play(int x=0, int y=0, int mines=0);
    Play(const Play& pattern);
    ~Play();
    void restart();
    bool move(int x, int y);
    void flag(int x, int y);
    Play& operator=(const Play& play);
    void setEnd();
    bool getEnd() const;
    int getMoveCount() const;

    friend std::ostream& operator<<(std::ostream& stream, const Play &pattern);
    friend std::istream&  operator>>(std::istream& stream, Play& pattern);
};
#endif //SAPPER_PLAY_H
