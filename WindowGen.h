#ifndef SAPPER_WINDOWGEN_H
#define SAPPER_WINDOWGEN_H
#include "SFML/Graphics.hpp"
#include "Play.h"
#include <iostream>

class WindowGen {
protected:
    Play* play = NULL;
public:
    void setPlay(Play *play);
    void setPlay(Play play);

protected:
    sf::RenderWindow *mainWindow;
    sf::Font font;
public:
    WindowGen();
    ~WindowGen();
    void startWindow();
    void startGame();

    friend std::ostream& operator<<(std::ostream& stream, const WindowGen& pattern);
};


#endif //SAPPER_WINDOWGEN_H
