//
// Created by kubab on 29/12/2022.
//

#include "Board.h"

std::vector<std::vector<Field>> Board::generateBoard(int x, int y) {

    Field *empty = new Field();
    std::vector<Field> row(x);

    std::fill(row.begin(), row.end(), *empty);

    this->bord.resize(y);

    std::fill(this->bord.begin(), this->bord.end(), row);
    delete empty;
    return this->bord;
}

std::vector<std::vector<Field>> Board::generateMine(int mines, int startX, int startY) {
    struct cord {
        int x, y;
    };
    //max 80 % field is mines
    if (mines > (this->y * this->y) / 0.9) {
        throw "To many mines";
    }

    std::vector<cord> minesCord;
    this->mines = mines;
    int i = 0;
    while (i < mines) {
        cord c;
        c.y = rand() % this->y;
        c.x = rand() % this->x;
        if (c.y == startY && c.x == startX) continue;
        bool ok = true;
        for (cord co: minesCord) {
            if (co.x == c.x && co.y == c.y) {
                ok = false;
            }
        }
        if (ok) {
            minesCord.push_back(c);
            i++;
        }
    }
    for (cord c: minesCord) {
        this->bord[c.y][c.x].setType(fieldType::mine);
        next(c.x, c.y);
    }
    return this->bord;
}

std::vector<std::vector<Field>> &Board::getBord() {
    return this->bord;
}

int Board::getX() const {
    return this->x;
}

int Board::getY() const {
    return this->y;
}

int Board::getCount() const {
    return this->mines;
}

Board::~Board() {
}

Board::Board(int x, int y, int count) {
    this->x = x;
    this->y = y;
    this->mines = count;
    this->generateBoard(x, y);
}

Board &Board::operator=(const Board &bord_) {
    this->bord = bord_.bord;
    this->mines = bord_.mines;
    this->y = bord_.y;
    this->x = bord_.x;
    return *this;
}

Board::Board() {
    this->generateBoard(0, 0);
}

void Board::next(int x, int y) {
    this->fieldNextType(x-1, y);
    this->fieldNextType(x-1, y-1);
    this->fieldNextType(x-1, y+1);
    this->fieldNextType(x+1, y);
    this->fieldNextType(x+1, y-1);
    this->fieldNextType(x+1, y+1);
    this->fieldNextType(x, y-1);
    this->fieldNextType(x, y+1);

}

void Board::draw(sf::RenderWindow &window, bool end) {
    sf::RectangleShape basicCell(sf::Vector2f(15 * 4, 15 * 4));
    sf::Texture icons_texture;
    sf::Sprite icon_sprite;
    icons_texture.loadFromFile("Image/Icons16.png");
    icon_sprite.setTexture(icons_texture);
    icon_sprite.scale(4,4);

    for (int y_i = 0; y_i < this->y; y_i++) {
        for (int x_i = 0; x_i < this->x; x_i++) {
            basicCell.setPosition(sf::Vector2f(x_i * 16 * 4, y_i * 16 * 4));
            if ((this->bord[y_i][x_i].getTag() != tags::none && this->bord[y_i][x_i].getTag() != tags::flag)  || end) {
                int fieldType = (int) this->bord[y_i][x_i].getType();
                if (fieldType == -1) {
                    auto tag = this->bord[y_i][x_i].getTag();
                    if (tag == tags::explosion)
                        basicCell.setFillColor(sf::Color(100,0,0));
                    else
                        basicCell.setFillColor(sf::Color(255,0,0));
                    window.draw(basicCell);
                    if (tag == tags::flag)
                    {
                        icon_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
                        icon_sprite.setPosition(static_cast<float>(x_i * 16 * 4), static_cast<float>(y_i * 16 * 4));
                        window.draw(icon_sprite);
                    }

                } else {
                    basicCell.setFillColor(sf::Color::Cyan);
                    window.draw(basicCell);

                    if (0 < fieldType) {
                        icon_sprite.setTextureRect(sf::IntRect(16 * fieldType, 0, 16, 16));
                        icon_sprite.setPosition(static_cast<float>(x_i * 16 * 4), static_cast<float>(y_i * 16 * 4));
                        window.draw(icon_sprite);
                    }
                }
            }else {
                basicCell.setFillColor(sf::Color::Blue);
                window.draw(basicCell);
                if (this->bord[y_i][x_i].getTag() == tags::flag) {
                    icon_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
                    icon_sprite.setPosition(static_cast<float>(x_i * 16 * 4), static_cast<float>(y_i * 16 * 4));
                    window.draw(icon_sprite);
                }
            }
        }
    }
}

void Board::flag(int x, int y) {
    if (this->bord[y][x].getTag() == tags::flag) {
        this->bord[y][x].setTag(tags::none);
    } else{
        this->bord[y][x].setTag(tags::flag);
    }
}

void Board::fieldNextType(int x, int y) {
    if (0<= x && x < this->x && 0 <= y && y < this->y){
        this->bord[y][x].nextFieldType();
    }
}

bool Board::checkIFWin() {
    for (auto row : this->bord) {
        for (auto cell :row) {
            if (cell.getType() != fieldType::mine && cell.getTag() != tags::discovered) {
                return false;
            }
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream& stream, const Board &pattern) {
    stream << pattern.y << " " << pattern.x << " " << pattern.mines << "\n";
    for (auto row:pattern.bord) {
        for (auto cell:row) {
            stream<<cell<<" ";
        }
        stream << "\n";
    }
    return stream;
}

std::istream &operator>>(std::istream& stream, Board &pattern) {
    return stream;
}
