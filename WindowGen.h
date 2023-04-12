#ifndef SAPPER_WINDOWGEN_H
#define SAPPER_WINDOWGEN_H
#include "SFML/Graphics.hpp"
#include "Play.h"

class WindowGen {
protected:
    int x,y;
    Play *play = new Play();
    sf::RenderWindow *mainWindow;
public:
    void startWindow(bool first = true);
    void startGame(int x, int y, int mines);
};


#endif //SAPPER_WINDOWGEN_H
