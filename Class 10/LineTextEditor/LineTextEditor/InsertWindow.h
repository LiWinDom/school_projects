#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"

class InsertWindow {
private:
    const uint16_t numSpace = textSize * 2 + paddingSize;
    const uint16_t textSpace = textSize * 16;
    const uint16_t numFieldHeight = textSize + 2 * paddingSize;
    const uint16_t numFieldWidth = numSpace + 2 * paddingSize;
    const uint16_t textFieldHeight = textSize + 2 * paddingSize;
    const uint16_t textFieldWidth = textSpace + 2 * paddingSize;

    std::string selected = "start";
    std::vector<std::wstring> lines = {};
    std::uint8_t startLine = 0, linesNum = 0;

    sf::Font font;

    void onStart(sf::RenderWindow& window);

    void drawNumberFields(sf::RenderWindow& window);

    void displayMain(sf::RenderWindow& window);

    void clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y);

    bool eventProcessingMain(sf::RenderWindow& window);

    void drawText(sf::RenderWindow& window, const std::wstring& text);

    void drawLeftFill(sf::RenderWindow& window);

    void display(sf::RenderWindow& window, const std::wstring& text);

    bool eventProcessingText(sf::RenderWindow& window, std::wstring& text);

public:
    std::pair <uint8_t, std::vector<std::wstring>> insertLines();
};