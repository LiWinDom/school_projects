#include "InsertWindow.h"

void InsertWindow::onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/minecraft.ttf");
    sf::Image icon;
    icon.loadFromFile("resourses/icon.png");
    window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void InsertWindow::drawNumberFields(sf::RenderWindow& window) {
    sf::RectangleShape startBorder, numBorder;

    startBorder.setOutlineThickness(borderSize);
    startBorder.setOutlineColor(sf::Color(selected == "start" ? selectedColor : textColor));
    startBorder.setSize(sf::Vector2f(numFieldWidth, numFieldHeight));
    startBorder.setPosition(window.getSize().x - paddingSize - borderSize - numFieldWidth, paddingSize + borderSize);
    startBorder.setFillColor(sf::Color(backgroundColor));

    numBorder.setOutlineThickness(borderSize);
    numBorder.setOutlineColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numBorder.setSize(sf::Vector2f(numFieldWidth, numFieldHeight));
    numBorder.setPosition(window.getSize().x - paddingSize - borderSize - numFieldWidth, 2 * paddingSize + 3 * borderSize + numFieldHeight);
    numBorder.setFillColor(sf::Color(backgroundColor));

    window.draw(startBorder);
    window.draw(numBorder);

    sf::Text startText, numText;
    startText.setFont(font);
    startText.setCharacterSize(textSize);
    startText.setFillColor(sf::Color(selected == "start" ? selectedColor : textColor));
    startText.setString(std::to_wstring(startLine));
    startText.setPosition(window.getSize().x - borderSize - numFieldWidth, 2 * paddingSize + borderSize);

    numText.setFont(font);
    numText.setCharacterSize(textSize);
    numText.setFillColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numText.setString(std::to_wstring(linesNum));
    numText.setPosition(window.getSize().x - borderSize - numFieldWidth, 5 * paddingSize + textSize + 3 * borderSize);

    window.draw(startText);
    window.draw(numText);

    return;
}

void InsertWindow::displayMain(sf::RenderWindow& window) {
    window.clear(sf::Color(backgroundColor));

    sf::Text startText, numText;
    startText.setFont(font);
    startText.setCharacterSize(textSize);
    startText.setFillColor(sf::Color(selected == "start" ? selectedColor : textColor));
    startText.setString(L"Insert after line");
    startText.setPosition(paddingSize, 2 * paddingSize + borderSize);

    numText.setFont(font);
    numText.setCharacterSize(textSize);
    numText.setFillColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numText.setString(L"Number of lines");
    numText.setPosition(paddingSize, 5 * paddingSize + textSize + 3 * borderSize);

    window.draw(startText);
    window.draw(numText);
    drawNumberFields(window);

    window.display();
}

void InsertWindow::clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y) {
    if (y < window.getSize().y / 2) {
        selected = "start";
    }
    else {
        selected = "number";
    }
    return;
}

bool InsertWindow::eventProcessingMain(sf::RenderWindow& window) {
    sf::Event event;
    static bool isMousePressed = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return true;
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                return true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (selected == "start") {
                    startLine /= 10;
                }
                else if (selected == "number") {
                    linesNum /= 10;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (selected == "start") {
                    startLine = 0;
                }
                else if (selected == "number") {
                    linesNum = 0;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                selected = "start";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                selected = "number";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                if (selected == "start" && startLine < 255) {
                    ++startLine;
                }
                else if (selected == "number" && linesNum < 255) {
                    ++linesNum;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                if (selected == "start" && startLine > 0) {
                    --startLine;
                }
                else if (selected == "number" && linesNum > 1) {
                    --linesNum;
                }
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode >= L'0' && event.text.unicode <= L'9') {
                if (selected == "start") {
                    if (startLine * 10 + event.text.unicode - '0' > 255) {
                        startLine = 255;
                    }
                    else {
                        startLine = startLine * 10 + event.text.unicode - '0';
                    }
                }
                else if (selected == "number") {
                    if (linesNum * 10 + event.text.unicode - '0' > 255) {
                        linesNum = 255;
                    }
                    else {
                        linesNum = linesNum * 10 + event.text.unicode - '0';
                    }
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x > window.getSize().x || mousePos.y > window.getSize().y) continue;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
            clickEvent(window, mousePos.x, mousePos.y);
            isMousePressed = true;
        }
        if (event.type == sf::Event::MouseButtonReleased) isMousePressed = false;
    }
    return false;
}

void InsertWindow::drawText(sf::RenderWindow& window, const std::wstring& text) {
    sf::Text textText;

    textText.setFont(font);
    textText.setCharacterSize(textSize);
    textText.setFillColor(sf::Color(selectedColor));
    textText.setString(text);
    sf::FloatRect bounds = textText.getLocalBounds();
    textText.setPosition(2 * paddingSize + borderSize, 2 * paddingSize + borderSize);
    if (bounds.width > textSpace) {
        textText.setPosition(2 * paddingSize + borderSize + textSpace - bounds.width, 2 * paddingSize + borderSize);
    }

    window.draw(textText);

    return;
}

void InsertWindow::drawLeftFill(sf::RenderWindow& window) {
    sf::RectangleShape leftFill;

    leftFill.setOutlineThickness(0);
    leftFill.setSize(sf::Vector2f(paddingSize, textFieldHeight));
    leftFill.setPosition(0, paddingSize + borderSize);
    leftFill.setFillColor(sf::Color(backgroundColor));

    window.draw(leftFill);

    return;
}

void InsertWindow::display(sf::RenderWindow& window, const std::wstring& text) {
    window.clear(sf::Color(backgroundColor));

    sf::RectangleShape border;

    border.setOutlineThickness(borderSize);
    border.setOutlineColor(sf::Color(selectedColor));
    border.setSize(sf::Vector2f(textFieldWidth, textFieldHeight));
    border.setPosition(paddingSize + borderSize, paddingSize + borderSize);
    border.setFillColor(sf::Color(backgroundColor));

    window.draw(border);
    drawText(window, text);
    drawLeftFill(window);

    window.display();
}

bool InsertWindow::eventProcessingText(sf::RenderWindow& window, std::wstring& text) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return true;
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
                return true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (text.size() > 0) {
                    text.pop_back();
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                text = L"";
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                text += event.text.unicode;
            }
        }
    }
    return false;
}

std::pair <uint8_t, std::vector<std::wstring>> InsertWindow::insertLines() {
    selected = "start";
    startLine = 0;
    linesNum = 0;
    lines = {};

    sf::RenderWindow mainWindow(sf::VideoMode(11 * textSize + 3 * paddingSize + numFieldWidth + 2 * borderSize,
        2 * numFieldHeight + 3 * paddingSize + 4 * borderSize), "Insert lines...", sf::Style::Close);

    mainWindow.setActive();

    onStart(mainWindow);
    while (mainWindow.isOpen()) {
        if (eventProcessingMain(mainWindow)) return std::pair <uint8_t, std::vector<std::wstring>>(0, {});
        displayMain(mainWindow);
    }
    linesNum = std::max((int)linesNum, 1);

    for (uint8_t i = 0; i < linesNum; ++i) {
        sf::RenderWindow textWindow(sf::VideoMode(textFieldWidth + 2 * (paddingSize + borderSize),
            textFieldHeight + 2 * (paddingSize + borderSize)), "Insert line #" + std::to_string(startLine + i + 1), sf::Style::Close);
        std::wstring text;

        while (textWindow.isOpen()) {
            if (eventProcessingText(textWindow, text)) return std::pair <uint8_t, std::vector<std::wstring>>(0, {});
            display(textWindow, text);
        }

        lines.push_back(text);
        continue;
    }

    return std::pair <uint8_t, std::vector<std::wstring>>(startLine, lines);
}