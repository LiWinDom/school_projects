#include "Button.h"

Button::Button(const uint16_t& x, const uint16_t& y, const uint16_t& width, const uint16_t& height, const std::string& text) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->text = text;
        font.loadFromFile("resourses/minecraft.ttf");
    }

void Button::draw(sf::RenderWindow& window) {
        sf::RectangleShape border;
        sf::Text textText;

        border.setOutlineThickness(borderSize);
        border.setOutlineColor(sf::Color(selected ? selectedColor : textColor));
        border.setSize(sf::Vector2f(width - 2 * borderSize, height - 2 * borderSize));
        border.setPosition(x + borderSize, y + borderSize);
        border.setFillColor(sf::Color(backgroundColor));

        textText.setFont(font);
        textText.setCharacterSize(textSize);
        textText.setFillColor(sf::Color(selected ? selectedColor : textColor));
        textText.setString(text);
        sf::FloatRect bounds = textText.getLocalBounds();
        textText.setPosition(std::floor(x + (width - 2 * borderSize) / 2 - bounds.width / 2), std::floor(y + (height - 2 * borderSize) / 2 - bounds.height / 2));

        window.draw(border);
        window.draw(textText);

        return;
    }

bool Button::on(const uint16_t& curX, const uint16_t& curY) {
    if (curX >= x && curX <= x + width && curY >= y && curY <= y + height) {
        return selected = true;
    }
    return selected = false; 
}