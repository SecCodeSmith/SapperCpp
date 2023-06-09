#include <iostream>
#include <fstream>
#include "WindowGen.h"

int main() {
    Play play;
    std::fstream file;
    file.open("save", std::ios::in);
    WindowGen window;
    if (file.is_open()) {
        file >> play;
        window.setPlay(play);
    }
    file.close();

    window.startWindow();

    file.open("save", std::ios::out);
    file<<window;
    file.close();
    return 0;
}
