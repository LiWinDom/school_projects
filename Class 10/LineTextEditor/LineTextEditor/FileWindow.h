#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"

class FileWindow {
private:
    const uint16_t textSpace = textSize * 16;
    const uint16_t fieldHeight = textSize + 2 * paddingSize;
    const uint16_t fieldWidth = textSpace + 2 * paddingSize;

    sf::Font font;
    std::wstring path = L"";

    void onStart(sf::RenderWindow& window);

    void drawPath(sf::RenderWindow& window);

    void drawLeftFill(sf::RenderWindow& window);

    void display(sf::RenderWindow& window);

    void eventProcessing(sf::RenderWindow& window);

public:
    std::wstring openFile();

    std::wstring saveFile();
};