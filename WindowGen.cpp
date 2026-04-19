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
        text.setCharacterSize(45);
        text.setFont(this->font);
        text.setFillColor(sf::Color::Black);

        sf::RectangleShape basicCell(sf::Vector2f(60, 60));
        basicCell.setFillColor(sf::Color(192, 192, 192));
        basicCell.setOutlineThickness(-2);
        basicCell.setOutlineColor(sf::Color(128, 128, 128));
        sf::RectangleShape basicCellDouble(sf::Vector2f(124, 60));
        basicCellDouble.setFillColor(sf::Color(192, 192, 192));
        basicCellDouble.setOutlineThickness(-2);
        basicCellDouble.setOutlineColor(sf::Color(128, 128, 128));
        sf::RectangleShape startButton(sf::Vector2f(188, 60));
        startButton.setPosition(sf::Vector2f(2, 194));
        startButton.setFillColor(sf::Color(160, 200, 160));
        startButton.setOutlineThickness(-2);
        startButton.setOutlineColor(sf::Color(128, 128, 128));
        sf::RectangleShape continueButton(sf::Vector2f(316, 60));
        continueButton.setFillColor(sf::Color(160, 160, 200));
        continueButton.setPosition(sf::Vector2f(194, 194));
        continueButton.setOutlineThickness(-2);
        continueButton.setOutlineColor(sf::Color(128, 128, 128));
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
                                if (mines + 1 <= (x * y * 40) / 100)
                                    mines++;
                                break;
                            case 4:
                            case 5:
                                if (mines + 10 <= (x * y * 40) / 100)
                                    mines += 10;
                                else
                                    mines = (x * y * 40) / 100;
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
                        
                        {
                            int max_mines = (x * y * 40) / 100;
                            if (max_mines < 1) max_mines = 1;
                            
                            if (mines > max_mines)
                                mines = max_mines;
                                
                            if (mines < 1)
                                mines = 1;
                        }
                        break;

                    default:
                        break;
                    }
                                        break;
                    }
                }
                }

            }


            windowStart->clear(sf::Color(220, 220, 220));

            text_ = "X: " + std::to_string(x);
            text.setString(text_);
            text.setPosition(sf::Vector2f(10, 4));
            windowStart->draw(text);

            text_ = "Y: " + std::to_string(y);
            text.setString(text_);
            text.setPosition(sf::Vector2f(10, 68));
            windowStart->draw(text);

            text_ = "M: " + std::to_string(mines);
            text.setString(text_);
            text.setPosition(sf::Vector2f(10, 132));
            windowStart->draw(text);

            bool isLMB = sf::Mouse::isButtonPressed(sf::Mouse::Left);

            if (isLMB && mouse_cell_y == 3 && mouse_cell_x >= 0 && mouse_cell_x <= 2) {
                startButton.setFillColor(sf::Color(140, 180, 140));
                startButton.setOutlineThickness(0);
            } else {
                startButton.setFillColor(sf::Color(160, 200, 160));
                startButton.setOutlineThickness(-2);
            }
            windowStart->draw(startButton); //start button
            text.setPosition(sf::Vector2f(10, 196));
            text.setString("Start");
            windowStart->draw(text);

            if (this->play != NULL){
                if (isLMB && mouse_cell_y == 3 && mouse_cell_x >= 3 && mouse_cell_x <= 7) {
                    continueButton.setFillColor(sf::Color(140, 140, 180));
                    continueButton.setOutlineThickness(0);
                } else {
                    continueButton.setFillColor(sf::Color(160, 160, 200));
                    continueButton.setOutlineThickness(-2);
                }
                windowStart->draw(continueButton);
                text.setPosition(sf::Vector2f(202, 196));
                text.setString("Continue");
                windowStart->draw(text);
            }


            for (int i = 0; i < 3; i++) {
                bool lmb_row = isLMB && mouse_cell_y == i;
                float y_pos = 64 * i + 2;

                basicCell.setPosition(sf::Vector2f(194, y_pos));
                if (lmb_row && mouse_cell_x == 3) {
                    basicCell.setFillColor(sf::Color(170, 170, 170));
                    basicCell.setOutlineThickness(0);
                } else {
                    basicCell.setFillColor(sf::Color(192, 192, 192));
                    basicCell.setOutlineThickness(-2);
                }
                windowStart->draw(basicCell);
                text.setString("+1");
                text.setPosition(sf::Vector2f(198, y_pos + 2));
                windowStart->draw(text);

                basicCellDouble.setPosition(sf::Vector2f(258, y_pos));
                if (lmb_row && (mouse_cell_x == 4 || mouse_cell_x == 5)) {
                    basicCellDouble.setFillColor(sf::Color(170, 170, 170));
                    basicCellDouble.setOutlineThickness(0);
                } else {
                    basicCellDouble.setFillColor(sf::Color(192, 192, 192));
                    basicCellDouble.setOutlineThickness(-2);
                }
                windowStart->draw(basicCellDouble);
                text.setString("+10");
                text.setPosition(sf::Vector2f(262, y_pos + 2));
                windowStart->draw(text);

                basicCell.setPosition(sf::Vector2f(386, y_pos));
                if (lmb_row && mouse_cell_x == 6) {
                    basicCell.setFillColor(sf::Color(170, 170, 170));
                    basicCell.setOutlineThickness(0);
                } else {
                    basicCell.setFillColor(sf::Color(192, 192, 192));
                    basicCell.setOutlineThickness(-2);
                }
                windowStart->draw(basicCell);
                text.setString("-1");
                text.setPosition(sf::Vector2f(390, y_pos + 2));
                windowStart->draw(text);

                basicCellDouble.setPosition(sf::Vector2f(450, y_pos));
                if (lmb_row && (mouse_cell_x == 7 || mouse_cell_x == 8)) {
                    basicCellDouble.setFillColor(sf::Color(170, 170, 170));
                    basicCellDouble.setOutlineThickness(0);
                } else {
                    basicCellDouble.setFillColor(sf::Color(192, 192, 192));
                    basicCellDouble.setOutlineThickness(-2);
                }
                windowStart->draw(basicCellDouble);
                text.setString("-10");
                text.setPosition(sf::Vector2f(454, y_pos + 2));
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
    text.setCharacterSize(48);
    text.setFont(this->font);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10, (play->getY())*64 + 4);

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
        int pressed_x = -1;
        int pressed_y = -1;
        if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            pressed_x = mouse_cell_x;
            pressed_y = mouse_cell_y;
        }

        if (this->mainWindow->isOpen()) {
            this->mainWindow->clear(sf::Color(128, 128, 128)); // classic gray background
            this->play->draw(*this->mainWindow, this->play->getEnd(), pressed_x, pressed_y);
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