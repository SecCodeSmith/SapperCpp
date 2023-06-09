//
// Created by kubab on 05/01/2023.
//

#include "WindowGen.h"

WindowGen::WindowGen()
{
    this->font.loadFromFile("Image/Font.ttf"); //Nerd font
}

void WindowGen::startWindow() {
    bool close = false;
    int x{ 10 }, y{ 10 }, mines{ 5 };
    while (!close)
    {
        sf::RenderWindow* windowStart = new sf::RenderWindow(sf::VideoMode(512 + 64, 64 * 4), "Sapper", sf::Style::Close);



        sf::Event event;

        std::string text_;

        sf::Text text;
        text.setCharacterSize(64);
        text.setFont(this->font);
        text.setColor(sf::Color::Black);

        sf::RectangleShape basicCell(sf::Vector2f(15 * 4, 15 * 4));
        basicCell.setFillColor(sf::Color::Green);
        sf::RectangleShape basicCellDouble(sf::Vector2f(15 * 4 * 2, 15 * 4));
        basicCellDouble.setFillColor(sf::Color::Green);
        sf::RectangleShape startButton(sf::Vector2f(15 * 4 * 3, 15 * 4));
        startButton.setPosition(sf::Vector2f(0, 192));
        startButton.setFillColor(sf::Color::Blue);
        sf::RectangleShape continueButton(sf::Vector2f(15 * 4 * 5, 15 * 4));
        continueButton.setFillColor(sf::Color::Magenta);
        continueButton.setPosition(sf::Vector2f(16 * 4 * 3, 192));
        while (windowStart->isOpen()) {

            unsigned int mouse_cell_x = std::clamp(
                static_cast<int>(floor(sf::Mouse::getPosition(*windowStart).x / static_cast<float>(64))), 0,
                8);
            unsigned int mouse_cell_y = std::clamp(
                static_cast<int>(floor(sf::Mouse::getPosition(*windowStart).y / static_cast<float>(64))), 0,
                4);


            while (1 == windowStart->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed: {
                    windowStart->close();
                    close = true;
                    break;
                }
                case sf::Event::KeyReleased: {
                    if (event.key.code == sf::Keyboard::Escape){
                        windowStart->close();
                        close = true;
                    }
                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    switch (event.mouseButton.button) {
                    case sf::Mouse::Left: {
                        switch (mouse_cell_y)
                        {
                        case 0:
                            switch (mouse_cell_x)
                            {
                            case 3:
                                if (x + 1 <= 50)
                                    x++;
                                break;
                            case 4:
                            case 5:
                                if (x + 10 <= 50)
                                    x += 10;
                                else
                                    x = 50;
                                break;
                            case 6:
                                if (x - 1 >= 3)
                                    x--;
                                break;
                            case 7:
                            case 8:
                                if (x - 10 >= 3)
                                    x -= 10;
                                else
                                    x = 3;
                                break;
                            default:
                                break;
                            }
                            break;

                        case 1:
                            switch (mouse_cell_x)
                            {
                            case 3:
                                if (y + 1 <= 20)
                                    y++;
                                break;
                            case 4:
                            case 5:
                                if (y + 10 <= 20)
                                    y += 10;
                                else
                                    y = 20;
                                break;
                            case 6:
                                if (y - 1 >= 3)
                                    y--;
                                break;
                            case 7:
                            case 8:
                                if (y - 10 >= 3)
                                    y -= 10;
                                else
                                    y = 3;
                                break;
                            default:
                                break;
                            }
                            break;
                        case 2:
                            switch (mouse_cell_x)
                            {
                            case 3:
                                if (mines + 1 <= (x * y) / 100 * 40)
                                    mines++;
                                break;
                            case 4:
                            case 5:
                                if (mines + 10 <= (x * y) / 100 * 40)
                                    mines += 10;
                                else
                                    mines = (x * y) / 100 * 40;
                                break;
                            case 6:
                                if (mines - 1 >= 1)
                                    mines--;
                                break;
                            case 7:
                            case 8:
                                if (mines - 10 >= 1)
                                    mines -= 10;
                                break;
                            default:
                                break;
                            }
                            break;
                        case 3:
                            if (mouse_cell_x >= 0 && mouse_cell_x <= 2) {
                                delete this->play;
                                windowStart->close();
                                this->play = new Play(x, y, mines);
                                startGame();
                            }
                            if (mouse_cell_x >= 3 && mouse_cell_x <= 7 && this->play != NULL){
                                windowStart->close();
                                startGame();
                            }
                            break;
                        default:
                            break;
                        }
                        if (mines > (x * y) / 100 * 40)
                            mines = ((x * y) / 100 * 40)+1;
                        break;

                    default:
                        break;
                    }
                                        break;
                    }
                }
                }

            }


            windowStart->clear(sf::Color::Cyan);

            text_ = "X:" + std::to_string(x);

            text.setString(text_);
            text.setPosition(sf::Vector2f(0, 0));

            text_ = "Y:" + std::to_string(y);

            windowStart->draw(text);

            text.setString(text_);
            text.setPosition(sf::Vector2f(0, 64));

            text_ = "M:" + std::to_string(mines);
            windowStart->draw(text);

            text.setString(text_);
            text.setPosition(sf::Vector2f(0, 128));
            windowStart->draw(text);

            windowStart->draw(startButton); //start button
            text.setPosition(sf::Vector2f(0, 182));
            text.setString("Start");
            windowStart->draw(text);

            if (this->play != NULL){
                windowStart->draw(continueButton);
                text.setPosition(sf::Vector2f(16 * 4 * 3, 182));
                text.setString("Continue");
                windowStart->draw(text);
            }


            for (int i = 0; i < 3; i++) {
                basicCell.setPosition(sf::Vector2f(192, 64 * i));
                windowStart->draw(basicCell);
                text.setString("+1");
                text.setPosition(sf::Vector2f(192, 64 * i - 5));
                windowStart->draw(text);
                basicCellDouble.setPosition(sf::Vector2f(256, 64 * i));
                windowStart->draw(basicCellDouble);
                text.setString("+10");
                text.setPosition(sf::Vector2f(256, 64 * i - 5));
                windowStart->draw(text);
                basicCell.setPosition(sf::Vector2f(320 + 64, 64 * i));
                windowStart->draw(basicCell);
                text.setString("-1");
                text.setPosition(sf::Vector2f(320 + 64, 64 * i - 5));
                windowStart->draw(text);
                basicCellDouble.setPosition(sf::Vector2f(384 + 64, 64 * i));
                windowStart->draw(basicCellDouble);
                text.setString("-10");
                text.setPosition(sf::Vector2f(384 + 64, 64 * i - 5));
                windowStart->draw(text);

            }
            windowStart->display();
        }

        delete windowStart;
    }

}

void WindowGen::startGame() {
    sf::Sprite Alexander;
    this->mainWindow = new sf::RenderWindow(sf::VideoMode((play->getX() * 16 * 4) - 1, (play->getY() + 1) * 16 * 4), "Sapper", sf::Style::Close);

    this->mainWindow->setFramerateLimit(30);
    sf::Texture Alexander_texture;
    Alexander_texture.loadFromFile("Image/Alexander.png");
    Alexander.setPosition(64*(play->getX()-1),64*(play->getY()));
    Alexander.setTexture(Alexander_texture);
    Alexander.scale(4,4);
    int Alexander_state;


    sf::Event event;

    sf::Text text;
    text.setCharacterSize(64);
    text.setFont(this->font);
    text.setColor(sf::Color::Blue);
    text.setPosition(play->getX(), (play->getY())*64);

    while (this->mainWindow->isOpen()) {
        unsigned int mouse_cell_x = std::clamp(
                static_cast<int>(floor(sf::Mouse::getPosition(*this->mainWindow).x / static_cast<float>(16 * 4))), 0,
                this->play->getX() - 1);
        unsigned int mouse_cell_y = std::clamp(
                static_cast<int>(floor(sf::Mouse::getPosition(*this->mainWindow).y / static_cast<float>(16 * 4))), 0,
                this->play->getY() + 1);

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
                        }
                    }

                    break;
                }
                case sf::Event::MouseButtonReleased: {
                    if (mouse_cell_y < play->getY() ) {
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
            Alexander_state = 0;
        }

        if (this->play->getEnd() && !this->play->isWin())
        {
            Alexander_state = 2;
        }
        //If the game is won
        else if (this->play->getEnd() && this->play->isWin())
        {
            Alexander_state = 3;
        }
        if (this->mainWindow->isOpen()) {
            this->mainWindow->clear(sf::Color::Black);
            this->play->draw(*this->mainWindow, this->play->getEnd());
            Alexander.setTextureRect(sf::IntRect(Alexander_state * Alexander_texture.getSize().y, 0, Alexander_texture.getSize().y, Alexander_texture.getSize().y));

            text.setString("Moves: " + std::to_string(this->play->getMoveCount()));
            this->mainWindow->draw(text);
            this->mainWindow->draw(Alexander);
            this->mainWindow->display();
        }
    }
    delete this->mainWindow;
}

WindowGen::~WindowGen() {
    if (this->play != NULL)
        delete this->play;
}

std::ostream &operator<<(std::ostream &stream, const WindowGen &pattern) {
    if (pattern.play != NULL)
        stream<<*pattern.play;
    else
        stream<<"Empty!! \n";
    return stream;
}

void WindowGen::setPlay(Play *play) {
    WindowGen::play = play;
}

void WindowGen::setPlay(Play play) {
    if (this->play != NULL) {
        delete this->play;
    }
    this->play = new Play(play);
}