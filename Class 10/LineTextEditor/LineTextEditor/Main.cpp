#include <algorithm>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <codecvt>

#include "Config.h"
#include "Button.h"
#include "FileWindow.h"
#include "InsertWindow.h"
#include "ModifyWindow.h"

FileWindow FW;
InsertWindow IW;
ModifyWindow MW;

static const uint16_t textSpace = (textSize + paddingSize) * showLinesNum - paddingSize;
static const uint16_t editorHeight = textSpace + 2 * paddingSize;
static const uint16_t editorWidth = editorHeight + textSize * 1.5;

sf::Font font;
uint8_t startLine = 0;
uint8_t selectedLine = 0;
std::wstring filePath = L"";
std::wstring* lines[256];

Button OpenButton(editorWidth + 2 * (borderSize + paddingSize), paddingSize, editorWidth / 4, textSize + 2 * (paddingSize + borderSize), "Open");
Button SaveButton(editorWidth + 2 * (borderSize + paddingSize), OpenButton.y + OpenButton.height + paddingSize, editorWidth / 4, textSize + 2 * (paddingSize + borderSize), "Save");
Button SaveAsButton(SaveButton.x + SaveButton.width + paddingSize, OpenButton.y + OpenButton.height + paddingSize, editorWidth / 4, textSize + 2 * (paddingSize + borderSize), "Save as");

Button InsertButton(OpenButton.x, SaveAsButton.y + 2 * (SaveAsButton.height + paddingSize), editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Insert lines");
Button DeleteButton(OpenButton.x, InsertButton.y + InsertButton.height + paddingSize, editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Delete line");

Button InsertSubstrButton(OpenButton.x, DeleteButton.y + 2 * (DeleteButton.height + paddingSize), editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Insert substring");
Button ChangeSymbolButton(OpenButton.x, InsertSubstrButton.y + InsertSubstrButton.height + paddingSize, editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Change symbol");
Button ReplaceSubstrButton(OpenButton.x, ChangeSymbolButton.y + ChangeSymbolButton.height + paddingSize, editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Replace substr");

Button RemoveZerosButton(OpenButton.x, ReplaceSubstrButton.y + 2 * (DeleteButton.height + paddingSize), editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Remove leading 0");
Button LeaveIncreasingButton(OpenButton.x, RemoveZerosButton.y + RemoveZerosButton.height + paddingSize, editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Leave increasing");
Button ReplaceStarsButton(OpenButton.x, LeaveIncreasingButton.y + LeaveIncreasingButton.height + paddingSize, editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Replace * with +");
Button RemoveInBracketsButton(OpenButton.x, ReplaceStarsButton.y + ReplaceStarsButton.height + paddingSize, editorWidth / 2 + paddingSize, textSize + 2 * (paddingSize + borderSize), "Remove all in {}");
std::vector<Button*> buttons = { &OpenButton, &SaveButton, &SaveAsButton,
                                 &InsertButton, &DeleteButton,
                                 &InsertSubstrButton, &ChangeSymbolButton, &ReplaceSubstrButton,
                                 &RemoveZerosButton, &LeaveIncreasingButton, &ReplaceStarsButton, &RemoveInBracketsButton };

void insertLines(const uint8_t& startFrom, std::vector<std::wstring>& insertLines) {
    for (uint8_t i = 0; i < insertLines.size(); ++i) {
        sf::Text textText;

        textText.setFont(font);
        textText.setCharacterSize(textSize);
        textText.setString(insertLines[i]);
        sf::FloatRect bounds = textText.getLocalBounds();
        if (bounds.width > textSpace) {
            for (uint16_t j = insertLines[i].size() - 1; j > 0; --j) {
                textText.setString(insertLines[i].substr(0, j));
                bounds = textText.getLocalBounds();
                if (bounds.width <= textSpace) {
                    std::wstring original = insertLines[i];
                    insertLines[i] = original.substr(0, j);
                    insertLines.insert(insertLines.begin() + i + 1, original.substr(j, original.size() - j));
                    break;
                }
            }
        }
        for (uint8_t j = 255; j > (int)i + startFrom; --j) {
            *lines[j] = *lines[j - 1];
        }
        *lines[i + startFrom] = insertLines[i];
        if (i + startFrom == 255) break;
    }
    return;
}

void deleteLine(const uint8_t& lineNum) {
    for (uint8_t i = lineNum; i < 255; ++i) {
        *lines[i] = *lines[i + 1];
    }
    *lines[255] = L"";

    return;
}

bool load(const std::wstring& path) {
    std::ifstream file;
    std::vector<std::wstring> loaded(256, L"");

    file.open(path);
    if (!file.is_open()) {
        std::ofstream temp;
        temp.open(path);
        if (!temp.is_open()) {
            return false;
        }
        temp.close();
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;

    for (uint8_t i = 0;; ++i) {
        std::string curLine;
        std::getline(file, curLine, '\n');
        loaded[i] = convert.from_bytes(curLine);
        if (i == 255) break;
    }
    file.close();

    insertLines(0, loaded);

    return true;
}

bool save(const std::wstring& path) {
    std::ofstream file;
    file.open(path);
    if (!file.is_open()) {
        return false;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;

    file << convert.to_bytes(*lines[0]);
    for (uint8_t i = 1;; ++i) {
        file << '\n' << convert.to_bytes(*lines[i]);
        if (i == 255) break;
    }
    file.close();

    return true;
}

void removeZeros(const uint8_t& lineNum) {
    uint8_t strt = 0;
    bool isNum = true;

    for (uint8_t i = 0; i < lines[lineNum]->size(); ++i) {
        if ((*lines[lineNum])[i] == L' ' || i == lines[lineNum]->size() - 1) {
            if (i == lines[lineNum]->size() - 1) {
                ++i;
            }
            if (!isNum || i == 0) {
                goto newNum;
            }

            for (uint8_t j = strt; j < i - 1; ++j) {
                if ((*lines[lineNum])[strt] == L'0') {
                    lines[lineNum]->erase(strt, 1);
                }
                else {
                    break;
                }
            }
            i = strt;
            newNum:
            isNum = true;
            strt = i + 1;
        }
        else if (!isNum || (*lines[lineNum])[i] < L'0' || (*lines[lineNum])[i] > L'9') {
            isNum = false;
        }
    }
    return;
}

void leaveIncreasing(const uint8_t& lineNum) {
    uint8_t strt = 0;
    bool isNum = true;

    for (uint8_t i = 0; i < lines[lineNum]->size(); ++i) {
        if ((*lines[lineNum])[i] == L' ' || i == lines[lineNum]->size() - 1) {
            if (i == lines[lineNum]->size() - 1) {
                ++i;
            }
            if (!isNum || i == 0) {
                goto newNum;
            }


            if (strt + 1 == i) {
                lines[lineNum]->erase(strt, 1);
                --i;
                goto newNum;
            }
            for (uint8_t j = strt + 1; j < i; ++j) {
                if ((*lines[lineNum])[j] <= (*lines[lineNum])[j - 1]) {
                    lines[lineNum]->erase(strt, i - strt);
                    i = strt;
                    break;
                }
            }
        newNum:
            isNum = true;
            strt = i + 1;
        }
        else if (!isNum || (*lines[lineNum])[i] < L'0' || (*lines[lineNum])[i] > L'9') {
            isNum = false;
        }
    }
    return;
}

void replaceStars(const uint8_t& lineNum) {
    int16_t strt = -1;

    for (uint8_t i = 0; i < lines[lineNum]->size(); ++i) {
        if ((*lines[lineNum])[i] != L'*' || i == lines[lineNum]->size() - 1) {
            if (i - strt == 1) {
                ++strt;
                continue;
            }
            if (i == lines[lineNum]->size() - 1) {
                ++i;
            }
            strt += 1;
            uint8_t sz = i - strt;
            lines[lineNum]->erase(strt, sz);

            for (uint8_t j = 0; j < sz / 2; ++j) {
                lines[lineNum]->insert(strt, L"+");
            }
            i = strt + sz / 2;
            strt = i;
        }
    }
    return;
}

void removeBrackets(const uint8_t& lineNum) {
    int16_t strt = -1;

    for (uint8_t i = 0; i < lines[lineNum]->size(); ++i) {
        if ((*lines[lineNum])[i] == L'{') {
            strt = i;
        }
        else if ((*lines[lineNum])[i] == L'}' && strt > -1) {
            lines[lineNum]->erase(strt, i - strt + 1);
            i = strt;
            strt = -1;
        }
    }
    return;
}

void onStart(sf::RenderWindow& window) {
    font.loadFromFile("resourses/minecraft.ttf");
    sf::Image icon;
    icon.loadFromFile("resourses/icon.png");
    window.setIcon(52, 52, icon.getPixelsPtr());
    window.setVerticalSyncEnabled(true);

    for (uint8_t i = 0;; ++i) {
        lines[i] = new std::wstring();
        if (i == 255) break;
    }
    return;
}

void drawLines(sf::RenderWindow& window) {
    for (uint8_t i = 0; i < showLinesNum; ++i) {
        uint8_t actualLine = i + startLine;
        sf::Text lineNumText, lineText;

        lineNumText.setFont(font);
        lineNumText.setCharacterSize(std::floor(textSize / 2));
        lineNumText.setFillColor(sf::Color(actualLine == selectedLine ? selectedLineNumTextColor : textColor));
        lineNumText.setString(std::to_string(actualLine + 1) + ' ');
        sf::FloatRect bounds = lineNumText.getLocalBounds();
        lineNumText.setPosition(std::floor(paddingSize * 3 + textSize * 1.5 - bounds.width), (i * (textSize + paddingSize)) + paddingSize * 2 + borderSize + textSize / 3);

        lineText.setFont(font);
        lineText.setCharacterSize(textSize);
        lineText.setFillColor(sf::Color(actualLine == selectedLine ? selectedColor : textColor));
        lineText.setString(*lines[actualLine]);
        lineText.setPosition(std::floor(paddingSize * 3 + textSize * 1.5), (i * (textSize + paddingSize)) + paddingSize * 2 + borderSize);

        window.draw(lineNumText);
        window.draw(lineText);
    }

    return;
}

void drawButtons(sf::RenderWindow& window) {
    for (uint8_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->draw(window);
    }

    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(backgroundColor));

    sf::RectangleShape border;

    border.setOutlineThickness(borderSize);
    border.setOutlineColor(sf::Color(selectedColor));
    border.setSize(sf::Vector2f(editorWidth, editorHeight));
    border.setPosition(paddingSize + borderSize, paddingSize + borderSize);
    border.setFillColor(sf::Color(backgroundColor));

    window.draw(border);
    drawLines(window);
    drawButtons(window);
    window.display();

    return;
}

void clickEvent(sf::RenderWindow& window, uint16_t x, uint16_t y) {
    if (OpenButton.on(x, y)) {
        std::wstring opn = FW.openFile();
        window.setActive();
        if (opn != L"") {
            if (load(opn)) {
                filePath = opn;
                window.setTitle(filePath);
                startLine = 0;
                selectedLine = 0;
            }
        }
    }
    else if (SaveButton.on(x, y)) {
        if (filePath == L"") {
            std::wstring sv = FW.saveFile();
            window.setActive();
            if (sv != L"") {
                if (save(sv)) {
                    filePath = sv;
                    window.setTitle(filePath);
                }
            }
        }
        else {
            save(filePath);
        }
    }
    else if (SaveAsButton.on(x, y)) {
        std::wstring sv = FW.saveFile();
        window.setActive();
        if (sv != L"") {
            if (save(sv)) {
                filePath = sv;
                window.setTitle(filePath);
            }
        }
    }
    else if (InsertButton.on(x, y)) {
        std::pair <uint8_t, std::vector<std::wstring>> insert;

        insert = IW.insertLines();
        insertLines(insert.first, insert.second);

        window.setActive();
    }
    else if (DeleteButton.on(x, y)) {
        deleteLine(selectedLine);
    }
    else if (InsertSubstrButton.on(x, y)) {
        std::pair <uint8_t, std::wstring> insert;

        insert = MW.insertSubstring();
        std::wstring original = *lines[selectedLine];
        deleteLine(selectedLine);
        original.insert(std::min((size_t)insert.first, original.size()), insert.second);
        std::vector<std::wstring> ins;
        ins.push_back(original);
        insertLines(selectedLine, ins);

        window.setActive();
    }
    else if (ChangeSymbolButton.on(x, y)) {
        std::pair <uint8_t, wchar_t> change;

        change = MW.changeSymbol();
        if (change.second != '\0') {
            std::wstring str = *lines[selectedLine];
            str[std::min(str.size() - 1, (size_t)change.first)] = change.second;
            *lines[selectedLine] = str;
        }

        window.setActive();
    }
    else if (ReplaceSubstrButton.on(x, y)) {
        std::pair<std::pair<uint8_t, uint8_t>, std::pair<std::wstring, std::wstring>> replace;
        std::vector<std::wstring> newLines;

        replace = MW.replaceSubstr();
        if (replace.second.first != L"" && replace.second.first != replace.second.second) {
            for (uint8_t i = replace.first.first; i <= (int)replace.first.second; ++i) {
                newLines.push_back(*lines[replace.first.first]);
                deleteLine(replace.first.first);

                while (true) {
                    size_t start_pos = newLines[i - replace.first.first].find(replace.second.first);
                    if (start_pos == std::string::npos) {
                        break;
                    }
                    newLines[i - replace.first.first].replace(start_pos, replace.second.first.size(), replace.second.second);
                }

                if (i == 255) break;
            }
            insertLines(replace.first.first, newLines);
        }

        window.setActive();
    }
    else if (RemoveZerosButton.on(x, y)) {
        removeZeros(selectedLine);
    }
    else if (LeaveIncreasingButton.on(x, y)) {
        leaveIncreasing(selectedLine);
    }
    else if (ReplaceStarsButton.on(x, y)) {
        replaceStars(selectedLine);
    }
    else if (RemoveInBracketsButton.on(x, y)) {
        removeBrackets(selectedLine);
    }
    return;
}

void eventProcessing(sf::RenderWindow& window) {
    sf::Event event;
    static bool isMousePressed = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        else if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (selectedLine == 0) {
                    selectedLine = 255;
                    startLine = 256 - showLinesNum;
                }
                else {
                    --selectedLine;
                    startLine = std::min(startLine, selectedLine);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (selectedLine == 255) {
                    selectedLine = 0;
                    startLine = 0;
                }
                else {
                    ++selectedLine;
                    startLine = std::max((int)startLine, (int)selectedLine - showLinesNum + 1);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                deleteLine(selectedLine);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    std::wstring opn = FW.openFile();
                    window.setActive();
                    if (opn != L"") {
                        if (load(opn)) {
                            filePath = opn;
                            window.setTitle(filePath);
                            startLine = 0;
                            selectedLine = 0;
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || filePath == L"") {
                        std::wstring sv = FW.saveFile();
                        window.setActive();
                        if (sv != L"") {
                            if (save(sv)) {
                                filePath = sv;
                                window.setTitle(filePath);
                            }
                        }
                    }
                    else {
                        save(filePath);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    std::pair <uint8_t, std::vector<std::wstring>> insert;

                    insert = IW.insertLines();
                    insertLines(insert.first, insert.second);

                    window.setActive();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    deleteLine(selectedLine);
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x > window.getSize().x || mousePos.y > window.getSize().y) continue;
        for (uint8_t i = 0; i < buttons.size(); ++i) {
            buttons[i]->on(mousePos.x, mousePos.y);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isMousePressed) {
            clickEvent(window, mousePos.x, mousePos.y);
            isMousePressed = true;
        }
        if (event.type == sf::Event::MouseButtonReleased) isMousePressed = false;
    }

    return;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(editorWidth + 4 * paddingSize + editorWidth / 2 + 2 * borderSize, editorHeight + 2 * (paddingSize + borderSize)), "Line Text Editor [1.0]", sf::Style::Close);

    onStart(window);

    while (window.isOpen()) {
        eventProcessing(window);
        display(window);
    }

    return 0;
}