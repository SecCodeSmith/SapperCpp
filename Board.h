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
    int x{}, y{}, mines{};
    void next(int x, int y);
    std::vector<std::vector<Field>> generateMine(int mines, int startX, int startY);
    void fieldNextType(int x, int y);
public:
    std::vector<std::vector<Field>> generateBoard(int x, int y);
    void draw(sf::RenderWindow& window, bool end);
    std::vector<std::vector<Field>>& getBord();
    virtual void flag(int x, int y);
    int getX() const;
    bool checkIFWin();
    int getY() const;

    int getCount() const;


    Board();
    Board(int x, int y, int count);

    ~Board();

    Board& operator=(const Board& bord_);

    friend std::ostream& operator<<(std::ostream& stream, const Board& pattern);
    friend std::istream& operator>>(std::istream& stream, Board& pattern);
};

#endif //SAPPER_BOARD_H
