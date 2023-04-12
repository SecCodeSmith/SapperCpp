#ifndef SAPPER_BOARD_H
#define SAPPER_BOARD_H
#include <random>
#include <algorithm>
#include <vector>
#include "Field.h"
#include "SFML/Graphics.hpp"


class Board {
protected:
    std::vector<std::vector<Field>> bord;
    int x{}, y{}, count{};
    void next(int x, int y);
    std::vector<std::vector<Field>> generateBoard(int x, int y);
    std::vector<std::vector<Field>> generateMine(int count);
    void fieldNextType(int x, int y);
public:
    void draw(sf::RenderWindow& window, bool end);
    std::vector<std::vector<Field>>& getBord();
    void flag(int x, int y);
    int getX() const;
    bool checkIFWin();
    int getY() const;

    int getCount() const;


    Board();
    Board(int x, int y, int count);

    ~Board();

    Board& operator=(const Board& bord_);
};

#endif //SAPPER_BOARD_H
