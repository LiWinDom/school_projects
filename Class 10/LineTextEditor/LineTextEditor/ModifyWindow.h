#pragma once
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>

#include "Config.h"

class InsertSubstring {
private:
    const uint16_t numSpace = textSize * 2 + paddingSize;
    const uint16_t textSpace = textSize * 17;
    const uint16_t numFieldHeight = textSize + 2 * paddingSize;
    const uint16_t numFieldWidth = numSpace + 2 * paddingSize;
    const uint16_t textFieldHeight = textSize + 2 * paddingSize;
    const uint16_t textFieldWidth = textSpace + 2 * paddingSize;

    std::string selected = "number";
    std::wstring line = L"";
    std::uint8_t insertFrom = 0;

    sf::Font font;

    void onStart(sf::RenderWindow& window);

    void drawNumberField(sf::RenderWindow& window);

    void drawLeftFill(sf::RenderWindow& window);

    void drawTextField(sf::RenderWindow& window);

    void display(sf::RenderWindow& window);

    void clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y);

    void eventProcessing(sf::RenderWindow& window);

public:
    std::pair<uint8_t, std::wstring> call();
};

class ChangeSymbol {
private:
    const uint16_t numSpace = textSize * 2 + paddingSize;
    const uint16_t textSpace = textSize;
    const uint16_t numFieldHeight = textSize + 2 * paddingSize;
    const uint16_t numFieldWidth = numSpace + 2 * paddingSize;
    const uint16_t textFieldHeight = textSize + 2 * paddingSize;
    const uint16_t textFieldWidth = textSpace + 2 * paddingSize;

    std::string selected = "number";
    wchar_t symbol = L'\0';
    std::uint8_t change = 0;

    sf::Font font;

    void onStart(sf::RenderWindow& window);

    void drawNumberField(sf::RenderWindow& window);

    void drawTextField(sf::RenderWindow& window);

    void display(sf::RenderWindow& window);

    void clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y);

    void eventProcessing(sf::RenderWindow& window);

public:
    std::pair<uint8_t, wchar_t> call();
};

class ReplaceString {
private:
    const uint16_t numSpace = textSize * 2 + paddingSize;
    const uint16_t textSpace = textSize * 16;
    const uint16_t numFieldHeight = textSize + 2 * paddingSize;
    const uint16_t numFieldWidth = numSpace + 2 * paddingSize;
    const uint16_t textFieldHeight = textSize + 2 * paddingSize;
    const uint16_t textFieldWidth = textSpace + 2 * paddingSize;

    std::string selected = "from";
    std::wstring from = L"", to = L"";
    std::uint16_t startLine = 0, endLine = 256;

    sf::Font font;

    void onStart(sf::RenderWindow& window);

    void drawNumberFields(sf::RenderWindow& window);

    void drawLeftFill(sf::RenderWindow& window);

    void drawTextFields(sf::RenderWindow& window);

    void display(sf::RenderWindow& window);

    void clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y);

    void eventProcessing(sf::RenderWindow& window);

public:
    std::pair<std::pair<uint8_t, uint8_t>, std::pair<std::wstring, std::wstring>> call();
};

class ModifyWindow {
public:
    std::pair<uint8_t, std::wstring> insertSubstring();

    std::pair<uint8_t, wchar_t> changeSymbol();

    std::pair<std::pair<uint8_t, uint8_t>, std::pair<std::wstring, std::wstring>> replaceSubstr();
};