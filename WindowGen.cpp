//
// Created by kubab on 05/01/2023.
//

#include "WindowGen.h"
#include <iostream>

void WindowGen::startWindow(bool first) {
    if (!first) {
        char next;
        std::cout<<"Nastepna T/N: ";
        std::cin>>next;
        if (next == 'N' || next == 'n') {
            return;
        }
    }
    int x, y, mines;
    std::cout<< "Podaj szerokosc: ";
    std::cin >> x;
    std::cout<< "Podaj wysokosc: ";
    std::cin>> y;
    std::cout<< "Podaj ilosc min: ";
    std::cin>>mines;
    this->startGame(x,y,mines);
}

void WindowGen::startGame(int x, int y, int mines) {
    sf::Sprite Alexander;

    //Alexander's texture.
    sf::Texture Alexander_texture;
    //We get the texture from an image
    Alexander_texture.loadFromFile("Image/Alexander.png");

    //We're putting Alexander in the bottom right corner
    Alexander.setPosition(static_cast<float>(64 * (y-1) - Alexander_texture.getSize().y), 64 * x);
    Alexander.setTexture(Alexander_texture);
    Alexander.scale(4,4);
    int Alexander_state;

    this->play = new Play(x, y, mines);
    this->mainWindow = new sf::RenderWindow(sf::VideoMode((x * 16 * 4) - 1, (y+1) * 16 * 4), "Sapper");
    sf::Event event;
    while (this->mainWindow->isOpen()) {
        unsigned int mouse_cell_x = std::clamp(
                static_cast<int>(floor(sf::Mouse::getPosition(*this->mainWindow).x / static_cast<float>(16 * 4))), 0,
                this->play->getBoard()->getX() - 1);
        unsigned int mouse_cell_y = std::clamp(
                static_cast<int>(floor(sf::Mouse::getPosition(*this->mainWindow).y / static_cast<float>(16 * 4))), 0,
                this->play->getBoard()->getY() + 1);

        while (1 == this->mainWindow->pollEvent(event)) {
            switch (event.type) {
                //If the user clicked the close window button
                case sf::Event::Closed: {
                    //We close the window
                    this->mainWindow->close();

                    break;
                }
                case sf::Event::KeyReleased: {
                    switch (event.key.code) {
                        case sf::Keyboard::Enter: {
                            play->restart();
                            break;
                        }
                        case sf::Keyboard::Escape: {
                            mainWindow->close();
                            this->startWindow(false);
                        }
                    }

                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    if (mouse_cell_y < y ) {
                        switch (event.mouseButton.button) {
                            //If the LMB is released
                            case sf::Mouse::Left: {
                                //We open the cell under the cursor
                                play->move(mouse_cell_x, mouse_cell_y);

                                break;
                            }
                            case sf::Mouse::Right: {
                                this->play->flag(mouse_cell_x, mouse_cell_y);
                            }
                        }
                    }
                }
            }
        }
        if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Left) || 1 == sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            Alexander_state = 1;

        }
        else
        {
            //Alexander closes his mouth
            Alexander_state = 0;
        }

        if (this->play->getEnd() && !this->play->isWin())
        {
            //Alexander is disappointed (How could you!)
            Alexander_state = 2;
        }
        //If the game is won
        else if (this->play->getEnd() && this->play->isWin())
        {
            //Alexander is proud! (Yeah)
            Alexander_state = 3;
        }
        this->mainWindow->clear(sf::Color::Black);
        this->play->getBoard()->draw(*this->mainWindow, this->play->getEnd());
        Alexander.setTextureRect(sf::IntRect(Alexander_state * Alexander_texture.getSize().y, 0, Alexander_texture.getSize().y, Alexander_texture.getSize().y));

        this->mainWindow->draw(Alexander);
        this->mainWindow->display();
    }
}
