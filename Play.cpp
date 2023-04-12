//
// Created by kubab on 05/01/2023.
//

#include "Play.h"

void Play::setEnd() {
    this->end = false;
}

bool Play::getEnd() const {
    return this->end;
}

Play::Play(int x, int y, int mines) {
    this->board = new Board(x, y, mines);
}

Play::~Play() {
    delete this->board;
}

bool Play::move(int x, int y) {
    if (this->end || this->board->getBord()[y][x].getTag() == tags::flag)
        return false;
    this->moveCount++;
    if (this->board->getBord()[y][x].getType() == fieldType::mine) {
        this->board->getBord()[y][x].setTag(tags::explosion);
        this->end = true;
        return false;
    }

    struct cord {
        int x;
        int y;
    };

    std::vector<cord> nones;
    cord start;
    start.x = x;
    start.y = y;

    if (this->board->getBord()[y][x].getType() == fieldType::none)
        nones.push_back(start);
    else {
        this->board->getBord()[y][x].setTag(tags::discovered);
        bool left = x > 0 && x < this->board->getX(),
                right = x >= 0 && x < this->board->getX() - 1,
                up = y >= 0 && y < this->board->getY() - 1,
                down = y > 0 && y < this->board->getY();
        if (left) {
            if (this->board->getBord()[y][x - 1].getType() == fieldType::none) {
                cord add{x - 1, y};
                nones.push_back(add);
            }
        }
        if (right) {
            if (this->board->getBord()[y][x + 1].getType() == fieldType::none) {
                cord add{x + 1, y};
                nones.push_back(add);
            }
        }
        if (down) {
            if (this->board->getBord()[y - 1][x].getType() == fieldType::none) {
                cord add{x, y - 1};
                nones.push_back(add);
            }
        }
        if (up) {
            if (this->board->getBord()[y + 1][x].getType() == fieldType::none) {
                cord add{x, y + 1};
                nones.push_back(add);
            }
        }
        if (up && left) {
            if (this->board->getBord()[y + 1][x - 1].getType() == fieldType::none) {
                cord add{x - 1, y + 1};
                nones.push_back(add);
            }
        }
        if (up && right) {
            if (this->board->getBord()[y + 1][x + 1].getType() == fieldType::none) {
                cord add{x + 1, y + 1};
                nones.push_back(add);
            }
        }
        if (down && left) {
            if (this->board->getBord()[y - 1][x - 1].getType() == fieldType::none) {
                cord add{x - 1, y - 1};
                nones.push_back(add);
            }
        }
        if (down && right) {
            if (this->board->getBord()[y - 1][x + 1].getType() == fieldType::none) {
                cord add{x, y + 1};
                nones.push_back(add);
            }
        }
    }

    while (!nones.empty()) {
        cord current = nones.back();
        nones.pop_back();
        this->board->getBord()[current.y][current.x].setTag(tags::discovered);

        if (this->discover(current.x, current.y + 1) == 1) { // 1
            cord newCord;
            newCord.x = current.x;
            newCord.y = current.y + 1;
            nones.push_back(newCord);
        }
        if (this->discover(current.x + 1, current.y) == 1) { // 2
            cord newCord;
            newCord.x = current.x + 1;
            newCord.y = current.y;
            nones.push_back(newCord);
        }
        if (this->discover(current.x, current.y - 1) == 1) { // 3
            cord newCord;
            newCord.x = current.x;
            newCord.y = current.y - 1;
            nones.push_back(newCord);
        }
        if (this->discover(current.x - 1, current.y) == 1) { // 4
            cord newCord;
            newCord.x = current.x - 1;
            newCord.y = current.y;
            nones.push_back(newCord);
        }


        if (this->discover(current.x + 1, current.y + 1) == 1) { // 1
            cord newCord;
            newCord.x = current.x + 1;
            newCord.y = current.y + 1;
            nones.push_back(newCord);
        }
        if (this->discover(current.x + 1, current.y - 1) == 1) { // 2
            cord newCord;
            newCord.x = current.x + 1;
            newCord.y = current.y - 1;
            nones.push_back(newCord);
        }
        if (this->discover(current.x - 1, current.y + 1) == 1) { // 3
            cord newCord;
            newCord.x = current.x - 1;
            newCord.y = current.y + 1;
            nones.push_back(newCord);
        }
        if (this->discover(current.x - 1, current.y - 1) == 1) { // 4
            cord newCord;
            newCord.x = current.x - 1;
            newCord.y = current.y - 1;
            nones.push_back(newCord);
        }
    }
    this->win = this->board->checkIFWin();
    if (win) end = true;
    return true;
}

int Play::discover(int x, int y) {
    if (x < 0 || x >= this->board->getX() || y < 0 || y >= this->board->getY() ||
        this->board->getBord()[y][x].getTag() == tags::flag)
        return 0;
    if (this->board->getBord()[y][x].getType() == fieldType::mine) return -1;
    if (this->board->getBord()[y][x].getType() == fieldType::none &&
        this->board->getBord()[y][x].getTag() == tags::none) {
        this->board->getBord()[y][x].setTag(tags::discovered);
        return 1;
    };
    if (1 <= static_cast<int>(this->board->getBord()[y][x].getType()) <= 8 ||
        this->board->getBord()[y][x].getTag() != tags::none) {
        this->board->getBord()[y][x].setTag(tags::discovered);
        return 0;
    };
    return 0;
}

Play &Play::operator=(const Play &play) {
    this->board = play.board;
    this->end = play.end;
    this->moveCount = play.moveCount;
    return *this;
}

Play::Play() {
    Play(0, 0, 0);
}

Board *Play::getBoard() const {
    return board;
}

void Play::restart() {
    this->end = false;
    int x, y, mines;
    x = this->board->getX();
    y = this->board->getY();
    mines = this->board->getCount();
    delete this->board;
    this->board = new Board(x, y, mines);
}

void Play::flag(int x, int y) {
    if (this->getBoard()->getBord()[y][x].getTag() == tags::none ||
        this->getBoard()->getBord()[y][x].getTag() == tags::flag) {
        this->moveCount++;
        this->board->flag(x, y);
    }
}

bool Play::isWin() const {
    return win;
}

void Play::setWin(bool win) {
    Play::win = win;
}
