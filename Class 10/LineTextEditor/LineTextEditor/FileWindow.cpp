#include "FileWindow.h"

void FileWindow::onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/minecraft.ttf");
    sf::Image icon;
    icon.loadFromFile("resourses/icon.png");
    window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    return;
}

void FileWindow::drawPath(sf::RenderWindow& window) {
    sf::Text pathText;

    pathText.setFont(font);
    pathText.setCharacterSize(textSize);
    pathText.setFillColor(sf::Color(selectedColor));
    pathText.setString(path);
    sf::FloatRect bounds = pathText.getLocalBounds();
    pathText.setPosition(2 * paddingSize + borderSize, 2 * paddingSize + borderSize);
    if (bounds.width > textSpace) {
        pathText.setPosition(2 * paddingSize + borderSize + textSpace - bounds.width, 2 * paddingSize + borderSize);
    }

    window.draw(pathText);

    return;
}

void FileWindow::drawLeftFill(sf::RenderWindow& window) {
    sf::RectangleShape leftFill;

    leftFill.setOutlineThickness(0);
    leftFill.setSize(sf::Vector2f(paddingSize, fieldHeight));
    leftFill.setPosition(0, paddingSize + borderSize);
    leftFill.setFillColor(sf::Color(backgroundColor));

    window.draw(leftFill);

    return;
}

void FileWindow::display(sf::RenderWindow& window) {
    window.clear(sf::Color(backgroundColor));

    sf::RectangleShape border;

    border.setOutlineThickness(borderSize);
    border.setOutlineColor(sf::Color(selectedColor));
    border.setSize(sf::Vector2f(fieldWidth, fieldHeight));
    border.setPosition(paddingSize + borderSize, paddingSize + borderSize);
    border.setFillColor(sf::Color(backgroundColor));

    window.draw(border);
    drawPath(window);
    drawLeftFill(window);

    window.display();
}

void FileWindow::eventProcessing(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            path = L"";
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                path = L"";
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (path.size() > 0) {
                    path.pop_back();
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                path = L"";
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                path += event.text.unicode;
            }
        }
    }
    return;
}

std::wstring FileWindow::openFile() {
    sf::RenderWindow window(sf::VideoMode(fieldWidth + 2 * (paddingSize + borderSize), fieldHeight + 2 * (paddingSize + borderSize)), "Open file...", sf::Style::Close);

    window.setActive();

    onStart(window);
    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }

    return path;
}

std::wstring FileWindow::saveFile() {
    sf::RenderWindow window(sf::VideoMode(fieldWidth + 2 * (paddingSize + borderSize), fieldHeight + 2 * (paddingSize + borderSize)), "Save as...", sf::Style::Close);

    window.setActive();

    onStart(window);
    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }

    return path;
}