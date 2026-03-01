#include "ModifyWindow.h"

void InsertSubstring::onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/minecraft.ttf");
    sf::Image icon;
    icon.loadFromFile("resourses/icon.png");
    window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void InsertSubstring::drawNumberField(sf::RenderWindow& window) {
    sf::RectangleShape numBorder;

    numBorder.setOutlineThickness(borderSize);
    numBorder.setOutlineColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numBorder.setSize(sf::Vector2f(numFieldWidth, numFieldHeight));
    numBorder.setPosition(window.getSize().x - paddingSize - borderSize - numFieldWidth, paddingSize + borderSize);
    numBorder.setFillColor(sf::Color(backgroundColor));

    window.draw(numBorder);

    sf::Text numText;
    numText.setFont(font);
    numText.setCharacterSize(textSize);
    numText.setFillColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numText.setString(std::to_wstring(insertFrom));
    numText.setPosition(window.getSize().x - borderSize - numFieldWidth, 2 * paddingSize + borderSize);

    window.draw(numText);

    return;
}

void InsertSubstring::drawLeftFill(sf::RenderWindow& window) {
    sf::RectangleShape leftFill;

    leftFill.setOutlineThickness(0);
    leftFill.setSize(sf::Vector2f(paddingSize, textFieldHeight));
    leftFill.setPosition(0, numFieldHeight + 2 * paddingSize + 3 * borderSize);
    leftFill.setFillColor(sf::Color(backgroundColor));

    window.draw(leftFill);

    return;
}

void InsertSubstring::drawTextField(sf::RenderWindow& window) {
    sf::RectangleShape border;

    border.setOutlineThickness(borderSize);
    border.setOutlineColor(sf::Color(selected == "line" ? selectedColor : textColor));
    border.setSize(sf::Vector2f(textFieldWidth, textFieldHeight));
    border.setPosition(paddingSize + borderSize, numFieldHeight + 2 * paddingSize + 3 * borderSize);
    border.setFillColor(sf::Color(backgroundColor));
    window.draw(border);

    sf::Text textText;

    textText.setFont(font);
    textText.setCharacterSize(textSize);
    textText.setFillColor(sf::Color(selected == "line" ? selectedColor : textColor));
    textText.setString(line);
    sf::FloatRect bounds = textText.getLocalBounds();
    textText.setPosition(2 * paddingSize + borderSize, numFieldHeight + 3 * (borderSize + paddingSize));
    if (bounds.width > textSpace) {
        textText.setPosition(2 * paddingSize + borderSize + textSpace - bounds.width, numFieldHeight + 3 * (borderSize + paddingSize));
    }
    window.draw(textText);

    drawLeftFill(window);

    return;
}

void InsertSubstring::display(sf::RenderWindow& window) {
    window.clear(sf::Color(backgroundColor));

    sf::Text numText;
    numText.setFont(font);
    numText.setCharacterSize(textSize);
    numText.setFillColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numText.setString(L"Insert after symbol");
    numText.setPosition(paddingSize, 2 * paddingSize + borderSize);
    window.draw(numText);

    drawNumberField(window);
    drawTextField(window);

    window.display();
}

void InsertSubstring::clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y) {
    if (y < window.getSize().y / 2) {
        selected = "number";
    }
    else {
        selected = "line";
    }
    return;
}

void InsertSubstring::eventProcessing(sf::RenderWindow& window) {
    sf::Event event;
    static bool isMousePressed = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            insertFrom = 0;
            line = L"";
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                insertFrom = 0;
                line = L"";
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (selected == "number") {
                    insertFrom /= 10;
                }
                else if (selected == "line") {
                    if (line.size() > 0) {
                        line.pop_back();
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (selected == "number") {
                    insertFrom = 0;
                }
                else if (selected == "line") {
                    line = L"";
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                selected = "number";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                selected = "line";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                if (selected == "number" && insertFrom < 255) {
                    ++insertFrom;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                if (selected == "number" && insertFrom > 0) {
                    --insertFrom;
                }
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (selected == "number") {
                if (event.text.unicode >= L'0' && event.text.unicode <= L'9') {
                    if (insertFrom * 10 + event.text.unicode - '0' > 255) {
                        insertFrom = 255;
                    }
                    else {
                        insertFrom = insertFrom * 10 + event.text.unicode - '0';
                    }
                }
            }
            else if (selected == "line") {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    line += event.text.unicode;
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
    return;
}

std::pair<uint8_t, std::wstring> InsertSubstring::call() {
    sf::RenderWindow window(sf::VideoMode(textFieldWidth + 2 * (borderSize + paddingSize),
        textFieldHeight + numFieldHeight + 4 * borderSize + 3 * paddingSize), "Insert substring...", sf::Style::Close);
    window.setActive();

    onStart(window);
    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }
    return std::pair <uint8_t, std::wstring>(insertFrom, line);
}



void ChangeSymbol::onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/minecraft.ttf");
    sf::Image icon;
    icon.loadFromFile("resourses/icon.png");
    window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void ChangeSymbol::drawNumberField(sf::RenderWindow& window) {
    sf::RectangleShape numBorder;

    numBorder.setOutlineThickness(borderSize);
    numBorder.setOutlineColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numBorder.setSize(sf::Vector2f(numFieldWidth, numFieldHeight));
    numBorder.setPosition(textSize * 10 + borderSize, paddingSize + borderSize);
    numBorder.setFillColor(sf::Color(backgroundColor));

    window.draw(numBorder);

    sf::Text numText;
    numText.setFont(font);
    numText.setCharacterSize(textSize);
    numText.setFillColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numText.setString(std::to_wstring(change));
    numText.setPosition(textSize * 10 + borderSize + paddingSize, 2 * paddingSize + borderSize);

    window.draw(numText);

    return;
}

void ChangeSymbol::drawTextField(sf::RenderWindow& window) {
    sf::RectangleShape border;

    border.setOutlineThickness(borderSize);
    border.setOutlineColor(sf::Color(selected == "symbol" ? selectedColor : textColor));
    border.setSize(sf::Vector2f(textFieldWidth, textFieldHeight));
    border.setPosition(window.getSize().x - paddingSize - textFieldWidth - borderSize, paddingSize + borderSize);
    border.setFillColor(sf::Color(backgroundColor));
    window.draw(border);

    sf::Text textText;

    textText.setFont(font);
    textText.setCharacterSize(textSize);
    textText.setFillColor(sf::Color(selected == "symbol" ? selectedColor : textColor));
    if (symbol == L'\0') {
        textText.setString("");
    }
    else {
        textText.setString(symbol);
    }
    sf::FloatRect bounds = textText.getLocalBounds();
    textText.setPosition(window.getSize().x - paddingSize - std::floor((textFieldWidth + bounds.width) / 2) - borderSize, 2 * paddingSize + borderSize);
    window.draw(textText);

    return;
}

void ChangeSymbol::display(sf::RenderWindow& window) {
    window.clear(sf::Color(backgroundColor));

    sf::Text numText;
    numText.setFont(font);
    numText.setCharacterSize(textSize);
    numText.setFillColor(sf::Color(selected == "number" ? selectedColor : textColor));
    numText.setString(L"Change symbol");
    numText.setPosition(paddingSize, 2 * paddingSize + borderSize);
    window.draw(numText);

    sf::Text toText;
    toText.setFont(font);
    toText.setCharacterSize(textSize);
    toText.setFillColor(sf::Color(selected == "symbol" ? selectedColor : textColor));
    toText.setString(L"to");
    toText.setPosition(textSize * 13 + 3 * paddingSize + 2 * borderSize, 2 * paddingSize + borderSize);
    window.draw(toText);

    drawNumberField(window);
    drawTextField(window);

    window.display();
}

void ChangeSymbol::clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y) {
    if (x < textSize * 13) {
        selected = "number";
    }
    else {
        selected = "symbol";
    }
    return;
}

void ChangeSymbol::eventProcessing(sf::RenderWindow& window) {
    sf::Event event;
    static bool isMousePressed = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            change = 0;
            symbol = L'\0';
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                change = 0;
                symbol = L'\0';
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (selected == "number") {
                    change /= 10;
                }
                else if (selected == "symbol") {
                    symbol = L'\0';
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (selected == "number") {
                    change = 0;
                }
                else if (selected == "symbol") {
                    symbol = L'\0';
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                selected = "number";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                selected = "symbol";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                if (selected == "number" && change < 255) {
                    ++change;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                if (selected == "number" && change > 0) {
                    --change;
                }
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (selected == "number") {
                if (event.text.unicode >= L'0' && event.text.unicode <= L'9') {
                    if (change * 10 + event.text.unicode - '0' > 255) {
                        change = 255;
                    }
                    else {
                        change = change * 10 + event.text.unicode - '0';
                    }
                }
            }
            else if (selected == "symbol") {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    symbol = event.text.unicode;
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
    return;
}

std::pair<uint8_t, wchar_t> ChangeSymbol::call() {
    sf::RenderWindow window(sf::VideoMode(textSize * 12 + textFieldWidth + numFieldWidth + 3 * paddingSize + 4 * borderSize,
        textFieldHeight + 2 * (paddingSize + borderSize)), "Change symbol...", sf::Style::Close);
    window.setActive();

    onStart(window);
    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }
    return std::pair <uint8_t, wchar_t>(std::max(change - 1, 0), symbol);
}



void ReplaceString::onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/minecraft.ttf");
    sf::Image icon;
    icon.loadFromFile("resourses/icon.png");
    window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void ReplaceString::drawNumberFields(sf::RenderWindow& window) {
    sf::RectangleShape startBorder, endBorder;

    startBorder.setOutlineThickness(borderSize);
    startBorder.setOutlineColor(sf::Color(selected == "startLine" ? selectedColor : textColor));
    startBorder.setSize(sf::Vector2f(numFieldWidth, numFieldHeight));
    startBorder.setPosition(window.getSize().x - paddingSize - borderSize - numFieldWidth, 2 * numFieldHeight + 3 * paddingSize + 5 * borderSize);
    startBorder.setFillColor(sf::Color(backgroundColor));

    endBorder.setOutlineThickness(borderSize);
    endBorder.setOutlineColor(sf::Color(selected == "endLine" ? selectedColor : textColor));
    endBorder.setSize(sf::Vector2f(numFieldWidth, numFieldHeight));
    endBorder.setPosition(window.getSize().x - paddingSize - borderSize - numFieldWidth, 3 * numFieldHeight + 4 * paddingSize + 7 * borderSize);
    endBorder.setFillColor(sf::Color(backgroundColor));

    window.draw(startBorder);
    window.draw(endBorder);

    sf::Text startText, endText;

    startText.setFont(font);
    startText.setCharacterSize(textSize);
    startText.setFillColor(sf::Color(selected == "startLine" ? selectedColor : textColor));
    startText.setString(std::to_wstring(startLine));
    startText.setPosition(window.getSize().x - borderSize - numFieldWidth, 2 * numFieldHeight + 4 * paddingSize + 5 * borderSize);

    endText.setFont(font);
    endText.setCharacterSize(textSize);
    endText.setFillColor(sf::Color(selected == "endLine" ? selectedColor : textColor));
    endText.setString(std::to_wstring(endLine));
    endText.setPosition(window.getSize().x - borderSize - numFieldWidth, 3 * numFieldHeight + 5 * paddingSize + 7 * borderSize);

    window.draw(startText);
    window.draw(endText);

    return;
}

void ReplaceString::drawLeftFill(sf::RenderWindow& window) {
    sf::RectangleShape leftFill;

    leftFill.setOutlineThickness(0);
    leftFill.setSize(sf::Vector2f(paddingSize, 2 * (textFieldHeight + borderSize) + paddingSize));
    leftFill.setPosition(0, paddingSize + borderSize);
    leftFill.setFillColor(sf::Color(backgroundColor));

    window.draw(leftFill);

    return;
}

void ReplaceString::drawTextFields(sf::RenderWindow& window) {
    sf::RectangleShape fromBorder, toBorder;

    fromBorder.setOutlineThickness(borderSize);
    fromBorder.setOutlineColor(sf::Color(selected == "from" ? selectedColor : textColor));
    fromBorder.setSize(sf::Vector2f(textFieldWidth, textFieldHeight));
    fromBorder.setPosition(paddingSize + borderSize, paddingSize + borderSize);
    fromBorder.setFillColor(sf::Color(backgroundColor));

    toBorder.setOutlineThickness(borderSize);
    toBorder.setOutlineColor(sf::Color(selected == "to" ? selectedColor : textColor));
    toBorder.setSize(sf::Vector2f(textFieldWidth, textFieldHeight));
    toBorder.setPosition(paddingSize + borderSize, 2 * paddingSize + 3 * borderSize + numFieldHeight);
    toBorder.setFillColor(sf::Color(backgroundColor));

    window.draw(fromBorder);
    window.draw(toBorder);

    sf::Text fromText, toText;

    fromText.setFont(font);
    fromText.setCharacterSize(textSize);
    fromText.setFillColor(sf::Color(selected == "from" ? selectedColor : textColor));
    fromText.setString(from);
    sf::FloatRect bounds = fromText.getLocalBounds();
    fromText.setPosition(2 * paddingSize + borderSize, 2 * paddingSize + borderSize);
    if (bounds.width > textSpace) {
        fromText.setPosition(2 * paddingSize + borderSize + textSpace - bounds.width, 2 * paddingSize + borderSize);
    }

    toText.setFont(font);
    toText.setCharacterSize(textSize);
    toText.setFillColor(sf::Color(selected == "to" ? selectedColor : textColor));
    toText.setString(to);
    bounds = toText.getLocalBounds();
    toText.setPosition(2 * paddingSize + borderSize, 3 * (paddingSize + borderSize) + numFieldHeight);
    if (bounds.width > textSpace) {
        toText.setPosition(2 * paddingSize + borderSize + textSpace - bounds.width, 3 * (paddingSize + borderSize) + numFieldHeight);
    }

    window.draw(fromText);
    window.draw(toText);
    drawLeftFill(window);

    return;
}

void ReplaceString::display(sf::RenderWindow& window) {
    window.clear(sf::Color(backgroundColor));

    sf::Text startText, endText;

    startText.setFont(font);
    startText.setCharacterSize(textSize);
    startText.setFillColor(sf::Color(selected == "startLine" ? selectedColor : textColor));
    startText.setString(L"Replace from line");
    startText.setPosition(paddingSize, 2 * numFieldHeight + 4 * paddingSize + 5 * borderSize);
    window.draw(startText);

    endText.setFont(font);
    endText.setCharacterSize(textSize);
    endText.setFillColor(sf::Color(selected == "endLine" ? selectedColor : textColor));
    endText.setString(L"Replace to line");
    endText.setPosition(paddingSize, 3 * numFieldHeight + 5 * paddingSize + 7 * borderSize);
    window.draw(endText);

    drawNumberFields(window);
    drawTextFields(window);

    window.display();
}

void ReplaceString::clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y) {
    if (y < window.getSize().y / 4) {
        selected = "from";
    }
    else if (y >= window.getSize().y / 4 && y < window.getSize().y / 2) {
        selected = "to";
    }
    else if (y >= window.getSize().y / 2 && y < window.getSize().y / 4 * 3) {
        selected = "startLine";
    }
    else {
        selected = "endLine";
    }
    return;
}

void ReplaceString::eventProcessing(sf::RenderWindow& window) {
    sf::Event event;
    static bool isMousePressed = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            startLine = 0;
            endLine = 0;
            from = L"";
            to = L"";
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                startLine = 0;
                endLine = 0;
                from = L"";
                to = L"";
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (selected == "startLine") {
                    startLine /= 10;
                }
                else if (selected == "endLine") {
                    endLine /= 10;
                }
                else if (selected == "from") {
                    if (from.size() > 0) {
                        from.pop_back();
                    }
                }
                else if (selected == "to") {
                    if (to.size() > 0) {
                        to.pop_back();
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                if (selected == "startLine") {
                    startLine = 0;
                }
                else if (selected == "endLine") {
                    endLine = 0;
                }
                else if (selected == "from") {
                    from = L"";
                }
                else if (selected == "to") {
                    to = L"";
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (selected == "endLine") {
                    selected = "startLine";
                }
                else if (selected == "startLine") {
                    selected = "to";
                }
                else if (selected == "to") {
                    selected = "from";
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (selected == "from") {
                    selected = "to";
                }
                else if (selected == "to") {
                    selected = "startLine";
                }
                else if (selected == "startLine") {
                    selected = "endLine";
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
                if (selected == "startLine" && startLine < 255) {
                    ++startLine;
                }
                else if (selected == "endLine" && endLine < 255) {
                    ++endLine;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
                if (selected == "startLine" && startLine > 0) {
                    --startLine;
                }
                else if (selected == "endLine" && endLine > 0) {
                    --endLine;
                }
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (selected == "startLine") {
                if (event.text.unicode >= L'0' && event.text.unicode <= L'9') {
                    if (startLine * 10 + event.text.unicode - '0' > 256) {
                        startLine = 256;
                    }
                    else {
                        startLine = startLine * 10 + event.text.unicode - '0';
                    }
                }
            }
            else if (selected == "endLine") {
                if (event.text.unicode >= L'0' && event.text.unicode <= L'9') {
                    if (endLine * 10 + event.text.unicode - '0' > 256) {
                        endLine = 256;
                    }
                    else {
                        endLine = endLine * 10 + event.text.unicode - '0';
                    }
                }
            }
            else if (selected == "from") {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    from += event.text.unicode;
                }
            }
            else if (selected == "to") {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    to += event.text.unicode;
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
    return;
}

std::pair<std::pair<uint8_t, uint8_t>, std::pair<std::wstring, std::wstring>> ReplaceString::call() {
    sf::RenderWindow window(sf::VideoMode(textFieldWidth + 2 * (borderSize + paddingSize),
        2 * (numFieldHeight + textFieldHeight) + 5 * paddingSize + 8 * borderSize), "Replace string", sf::Style::Close);
    window.setActive();

    onStart(window);
    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }
    return std::pair<std::pair<uint8_t, uint8_t>, std::pair<std::wstring, std::wstring>>(std::pair<uint8_t, uint8_t>(std::max((int)startLine, 1) - 1, std::max((int)endLine, 1) - 1), std::pair<std::wstring, std::wstring>(from, to));
}



std::pair<uint8_t, std::wstring> ModifyWindow::insertSubstring() {
    InsertSubstring IS;
    return IS.call();
}

std::pair<uint8_t, wchar_t> ModifyWindow::changeSymbol() {
    ChangeSymbol CS;
    return CS.call();
}

std::pair<std::pair<uint8_t, uint8_t>, std::pair<std::wstring, std::wstring>> ModifyWindow::replaceSubstr() {
    ReplaceString RS;
    return RS.call();
}