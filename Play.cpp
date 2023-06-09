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

int Play::getMoveCount() const
{
    return this->moveCount;
}

Play::Play(int x, int y, int mines) {
    this->x = x;
    this->y = y;
    this->mines = mines;
    this->generateBoard(x, y);

}

Play::~Play() {
}

bool Play::move(int x, int y) {
    if (this->moveCount == 0) {
        this->generateMine(this->mines, x,y);
    }
    if (this->end || this->bord[y][x].getTag() != tags::none )
        return false;
    this->moveCount++;
    if (this->bord[y][x].getType() == fieldType::mine) {
        this->bord[y][x].setTag(tags::explosion);
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

    if (this->bord[y][x].getType() == fieldType::none)
        nones.push_back(start);
    else {
        if (this->bord[y][x].getType() != fieldType::mine ) {
            this->bord[y][x].setTag(tags::discovered);

        }
    }

    while (!nones.empty()) {
        cord current = nones.back();
        nones.pop_back();
        if (this->bord[current.y][current.x].getType() != fieldType::mine)
            this->bord[current.y][current.x].setTag(tags::discovered);
        else
            continue;

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
    this->win = this->checkIFWin();
    if (win) end = true;
    return true;
}

int Play::discover(int x, int y) {
    if (x < 0 || x >= this->x || y < 0 || y >= this->y ||
        this->bord[y][x].getTag() == tags::flag)
        return 0;
    if (this->bord[y][x].getType() == fieldType::mine) return -1;

    if (this->bord[y][x].getType() == fieldType::none &&
        this->bord[y][x].getTag() == tags::none) {
        return 1;
    };
    if (1 <= static_cast<int>(this->bord[y][x].getType()) && static_cast<int>(this->bord[y][x].getType()) <= 8) {
        this->bord[y][x].setTag(tags::discovered);
        return 0;
    };
    return 0;
}

Play &Play::operator=(const Play &play) {
    this->bord = play.bord;
    this->x = play.x;
    this->y = play.y;
    this->mines = play.mines;
    this->end = play.end;
    this->moveCount = play.moveCount;
    return *this;
}

void Play::restart() {
    this->end = false;
    this->generateBoard(this->x, this->y);
    this->moveCount = 0;
}

void Play::flag(int x, int y) {
    if (this->end || this->moveCount == 0) return;
    if (this->bord[y][x].getTag() == tags::none ||
        this->bord[y][x].getTag() == tags::flag) {
        this->moveCount++;
        Board::flag(x, y);
    }
}

bool Play::isWin() const {
    return win;
}

void Play::setWin(bool win) {
    Play::win = win;
}

std::ostream& operator<<(std::ostream &stream, const Play &pattern) {
    stream << pattern.x << " " << pattern.y << " " << pattern.mines << " " << pattern.end << " " << pattern.win << " " << pattern.moveCount << " \n";
    for (auto row:pattern.bord) {
        for (auto cell:row) {
            stream<<cell<<" ";
        }
        stream << "\n";
    }
    return stream;
}

std::istream& operator>>(std::istream &stream, Play &pattern) {

    std::string tmp;

    stream>>tmp;
    pattern.x = std::stoi(tmp);

    stream>>tmp;
    pattern.y = std::stoi(tmp);

    stream>>tmp;
    pattern.mines = std::stoi(tmp);

    stream>>tmp;
    pattern.end = std::stoi(tmp);

    stream>>tmp;
    pattern.win = std::stoi(tmp);

    stream>>tmp;
    pattern.moveCount = std::stoi(tmp);

    pattern.generateBoard(pattern.x, pattern.y);

    for (int y = 0; y < pattern.y; y++) {
        for (int x = 0; x < pattern.x; x++) {
            Field field;
            stream >> field;
            pattern.bord[y][x] = field;
        }
    }

    return stream;
}

Play::Play(const Play &pattern) {
    this->x = pattern.x;
    this->y = pattern.y;
    this->mines = pattern.mines;
    this->bord = pattern.bord;

    this->moveCount = pattern.moveCount;
    this->end = pattern.end;
    this->win = pattern.win;
}
