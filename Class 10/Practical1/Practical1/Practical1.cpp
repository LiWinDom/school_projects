#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

//visible options
const uint16_t window_width = 1280;
const uint16_t window_height = 720;
const uint32_t background_color = 0xffffffff;
const uint32_t main_cell_color = 0x000000ff;
const uint32_t second_cell_color = 0xc0c0c0ff;
uint32_t fill_color = 0xe94183ff;
bool animations = true;
bool draw_lines = true;
const double animation_coefficient = 5.0;

uint8_t frame_buffer[window_height][window_width][3];
uint8_t sizes[] = {1, 5, 10, 25, 50, 100, 175};
uint8_t cur_size_index = 3;
double cur_size = 1000;
std::pair<double, double> cur_shift = {0, 0};
std::pair<double, double> need_shift = {0, 0};
double animation_speed = 5.0;

void SetPixel(const uint16_t& x, const uint16_t& y, const uint32_t& color) {
    uint8_t red_component = color >> 24;
    uint8_t green_component = color >> 16;
    uint8_t blue_component = color >> 8;
    uint8_t alpha_component = color;

    frame_buffer[x][y][0] = red_component;
    frame_buffer[x][y][1] = green_component;
    frame_buffer[x][y][2] = blue_component;

    return;
}

void FillScreen(const uint32_t& color) {
    for (uint16_t i = 0; i < window_height; ++i) {
        for (uint16_t j = 0; j < window_width; ++j) {
            SetPixel(i, j, color);
        }
    }

    return;
}

class Line {
private:
    double coefficients[2];
    bool inv;
public:
    Line(const double& k, const double& a, const bool& invert = false) {
        coefficients[0] = k;
        coefficients[1] = a;
        inv = invert;
    }

    bool OnLeft(const double& x, const double& y) {
        if (inv) return y * coefficients[0] + coefficients[1] < x;
        return x * coefficients[0] + coefficients[1] < y;
    }

    bool OnRight(const double& x, const double& y) {
        if (inv) return y * coefficients[0] + coefficients[1] > x;
        return x * coefficients[0] + coefficients[1] > y;
    }
};

class Circle {
private:
    double pos[2];
    double r;
public:
    Circle(const double& x, const double& y, const double& radius) {
        pos[0] = x;
        pos[1] = y;
        r = radius;
    }

    bool Inside(const double& x, const double& y) {
        return (x - pos[0]) * (x - pos[0]) + (y - pos[1]) * (y - pos[1]) <= r * r;
    }

    bool Outside(const double& x, const double& y) {
        return (x - pos[0]) * (x - pos[0]) + (y - pos[1]) * (y - pos[1]) > r * r;
    }
};

class Square {
private:
    std::pair<double, double> pos[2];
public:
    Square(const double& x1, const double& y1, const double& x2, const double& y2) {
        pos[0].first = x1;
        pos[0].second = y1;
        pos[1].first = x2;
        pos[1].second = y2;
    }

    bool Inside(const double& x, const double& y) {
        return (x >= std::min(pos[0].first, pos[1].first)) && (x <= std::max(pos[0].first, pos[1].first)) &&
            (y >= std::min(pos[0].second, pos[1].second)) && (y <= std::max(pos[0].second, pos[1].second));
    }

    bool Outside(const double& x, const double& y) {
        return (x < std::min(pos[0].first, pos[1].first)) || (x > std::max(pos[0].first, pos[1].first)) ||
            (y < std::min(pos[0].second, pos[1].second)) || (y > std::max(pos[0].second, pos[1].second));
    }
};

class Diamond {
private:
    double pos[2];
    double diagonal_sizes[2];
public:
    Diamond(const double& x, const double& y, const double& halfx_size, const double& halfy_size) {
        pos[0] = x;
        pos[1] = y;
        diagonal_sizes[0] = halfx_size;
        diagonal_sizes[1] = halfy_size;
    }

    bool Inside(const double& x, const double& y) {
        return std::abs(x - pos[0]) / diagonal_sizes[0] + std::abs(y - pos[1]) / diagonal_sizes[1] <= 1;
    }

    bool Outside(const double& x, const double& y) {
        return std::abs(x - pos[0]) / diagonal_sizes[0] + std::abs(y - pos[1]) / diagonal_sizes[1] > 1;
    }
};

class Parabola {
private:
    double coefficients[3];
    bool inv;
public:
    Parabola(const double& a, const double& x, const double& y, const bool& invert = false) {
        coefficients[0] = a;
        if (invert) {
            coefficients[1] = -2 * y * a;
            coefficients[2] = (coefficients[1] * coefficients[1] + 4 * a * x) / (4 * a);
        }
        else {
            coefficients[1] = -2 * x * a;
            coefficients[2] = (coefficients[1] * coefficients[1] + 4 * a * y) / (4 * a);
        }
        inv = invert;
    }

    bool Inside(const double& x, const double& y) {
        if (inv) {
            if (coefficients[0] > 0) return y * y * coefficients[0] + y * coefficients[1] + coefficients[2] <= x;
            else return y * y * coefficients[0] + y * coefficients[1] + coefficients[2] >= x;
        }
        else {
            if (coefficients[0] > 0) return x * x * coefficients[0] + x * coefficients[1] + coefficients[2] <= y;
            else return x * x * coefficients[0] + x * coefficients[1] + coefficients[2] >= y;
        }
    }

    bool Outside(const double& x, const double& y) {
        if (inv) {
            if (coefficients[0] > 0) return y * y * coefficients[0] + y * coefficients[1] + coefficients[2] > x;
            else return y * y * coefficients[0] + y * coefficients[1] + coefficients[2] < x;
        }
        else {
            if (coefficients[0] > 0) return x * x * coefficients[0] + x * coefficients[1] + coefficients[2] > y;
            else return x * x * coefficients[0] + x * coefficients[1] + coefficients[2] < y;
        }
    }
};

void RandomColor() {
    uint8_t r_color = std::rand();
    uint8_t g_color = std::rand();
    uint8_t b_color = std::rand();
    fill_color = (r_color << 24) + (g_color << 16) + (b_color << 8) + 255;

    return;
}

void DrawMainLines() {
    if (!draw_lines) return;
    if (animations) {
        double intpart;
        std::pair<double, double> x_last, x, x_next;
        x_last.second = std::modf(std::abs((-1 - window_width / 2.0) / cur_size + cur_shift.first), &intpart);
        x_last.first = intpart;
        x.second = std::modf(std::abs((-window_width / 2.0) / cur_size + cur_shift.first), &intpart);
        x.first = intpart;
        for (uint16_t j = 0; j < window_width; ++j) {
            x_next.second = std::modf(std::abs((j + 1 - window_width / 2.0) / cur_size + cur_shift.first), &intpart);
            x_next.first = intpart;
            
            if (x.first == 0 && x.second <= x_last.second && x.second < x_next.second) {
                for (uint16_t i = 0; i < window_height; ++i) {
                    SetPixel(i, j, main_cell_color);
                }
            }
            x_last = x;
            x = x_next;
        }

        std::pair<double, double> y_last, y, y_next;
        y_last.second = std::modf(std::abs((-1 - window_height / 2.0) / cur_size + cur_shift.second), &intpart);
        y_last.first = intpart;
        y.second = std::modf(std::abs((-window_height / 2.0) / cur_size + cur_shift.second), &intpart);
        y.first = intpart;
        for (uint16_t i = 0; i < window_height; ++i) {
            y_next.second = std::modf(std::abs((i + 1 - window_height / 2.0) / cur_size + cur_shift.second), &intpart);
            y_next.first = intpart;

            if (y.first == 0 && y.second <= y_last.second && y.second < y_next.second) {
                for (uint16_t j = 0; j < window_width; ++j) {
                    SetPixel(i, j, main_cell_color);
                }
            }
            y_last = y;
            y = y_next;
        }
    }
    else {
        for (uint16_t i = 0; i < window_height; ++i) {
            double y = (i - window_height / 2.0) / sizes[cur_size_index] + cur_shift.second;
            if (y == 0) {
                for (uint16_t j = 0; j < window_width; ++j) {
                    SetPixel(i, j, main_cell_color);
                }
            }
        }
        for (uint16_t j = 0; j < window_width; ++j) {
            double x = (j - window_width / 2.0) / sizes[cur_size_index] + cur_shift.first;
            if (x == 0) {
                for (uint16_t i = 0; i < window_height; ++i) {
                    SetPixel(i, j, main_cell_color);
                }
            }
        }
    }

    return;
}

void DrawSecondLines() {
    if (!draw_lines || cur_size_index <= 0) return;
    if (animations) {
        double intpart;
        std::pair<double, double> x_last, x, x_next;
        x_last.second = std::modf(std::abs((-1 - window_width / 2.0) / cur_size + cur_shift.first), &intpart);
        x_last.first = intpart;
        x.second = std::modf(std::abs((-window_width / 2.0) / cur_size + cur_shift.first), &intpart);
        x.first = intpart;
        for (uint16_t j = 0; j < window_width; ++j) {
            x_next.second = std::modf(std::abs((j + 1 - window_width / 2.0) / cur_size + cur_shift.first), &intpart);
            x_next.first = intpart;

            if (x.second <= x_last.second && x.second < x_next.second) {
                for (uint16_t i = 0; i < window_height; ++i) {
                    SetPixel(i, j, second_cell_color);
                }
            }
            x_last = x;
            x = x_next;
        }

        std::pair<double, double> y_last, y, y_next;
        y_last.second = std::modf(std::abs((-1 - window_height / 2.0) / cur_size + cur_shift.second), &intpart);
        y_last.first = intpart;
        y.second = std::modf(std::abs((-window_height / 2.0) / cur_size + cur_shift.second), &intpart);
        y.first = intpart;
        for (uint16_t i = 0; i < window_height; ++i) {
            y_next.second = std::modf(std::abs((i + 1 - window_height / 2.0) / cur_size + cur_shift.second), &intpart);
            y_next.first = intpart;

            if (y.second <= y_last.second && y.second < y_next.second) {
                for (uint16_t j = 0; j < window_width; ++j) {
                    SetPixel(i, j, second_cell_color);
                }
            }
            y_last = y;
            y = y_next;
        }
    }
    else {
        for (uint16_t i = 0; i < window_height; ++i) {
            double intpart;
            double y = (i - window_height / 2.0) / sizes[cur_size_index] + cur_shift.second;
            if (modf(y, &intpart) == 0) {
                for (uint16_t j = 0; j < window_width; ++j) {
                    SetPixel(i, j, second_cell_color);
                }
            }
        }
        for (uint16_t j = 0; j < window_width; ++j) {
            double intpart;
            double x = (j - window_width / 2.0) / sizes[cur_size_index] + cur_shift.first;
            if (modf(x, &intpart) == 0) {
                for (uint16_t i = 0; i < window_height; ++i) {
                    SetPixel(i, j, second_cell_color);
                }
            }
        }
    }

    return;
}

void DrawGraphs() {
    Line line1(0.5, 5);
    Line line2((3.0 / 4.0), -2.5);
    Circle circle1(-4, 3.5, 1.5);
    Square square1(-1, 1.5, 1, -1);
    Diamond diamond1(0.5, -2, 1, 2);
    Parabola parablola1(2, 2.5, -2.5);
    Parabola parablola2(1, 2.5, -0.5, true);

    for (uint16_t i = 0; i < window_height; ++i) {
        for (uint16_t j = 0; j < window_width; ++j) {
            double x = (j - window_width / 2.0) / cur_size + cur_shift.first;
            double y = (i - window_height / 2.0) / cur_size + cur_shift.second;

            if ((line1.OnLeft(x, y) && circle1.Outside(x, y) && parablola1.Outside(x, y)) ||
                (line1.OnRight(x, y) && circle1.Inside(x, y)) ||
                (square1.Inside(x, y) && diamond1.Outside(x, y)) ||
                (line2.OnRight(x, y) && parablola1.Outside(x, y) && parablola2.Outside(x, y) && diamond1.Outside(x, y) && y < 0.5) ||
                (parablola1.Inside(x, y) && parablola2.Inside(x, y) && line2.OnRight(x, y))) {
                SetPixel(i, j, fill_color);
            }
        }
    }

    return;
}

void AnimationProcess() {
    if (animations) {
        cur_size += (sizes[cur_size_index] - cur_size) / animation_speed;
        cur_shift.first += (need_shift.first - cur_shift.first) / animation_speed;
        cur_shift.second += (need_shift.second - cur_shift.second) / animation_speed;
    }
    else {
        cur_size = sizes[cur_size_index];
        cur_shift = need_shift;
    }

    return;
}

void EventProcess(sf::Window& window) {
    static std::pair<int16_t, int16_t> start_mouse_pos = { -1, -1 };
    sf::Event event;

    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Equal || event.key.code == sf::Keyboard::Add) {
                if (cur_size_index < 6) ++cur_size_index;
            }
            else if (event.key.code == sf::Keyboard::Hyphen || event.key.code == sf::Keyboard::Subtract) {
                if (cur_size_index > 0) --cur_size_index;
            }
            else if (event.key.code == sf::Keyboard::Up) {
                if (cur_size_index >= 3) ++need_shift.second;
                else if (cur_size_index > 0) need_shift.second += 5;
                else need_shift.second += 10;
            }
            else if (event.key.code == sf::Keyboard::Down) {
                if (cur_size_index >= 3) --need_shift.second;
                else if (cur_size_index > 0) need_shift.second -= 5;
                else need_shift.second -= 10;
            }
            else if (event.key.code == sf::Keyboard::Left) {
                if (cur_size_index >= 3) --need_shift.first;
                else if (cur_size_index > 0) need_shift.first -= 5;
                else need_shift.first -= 10;
            }
            else if (event.key.code == sf::Keyboard::Right) {
                if (cur_size_index >= 3) ++need_shift.first;
                else if (cur_size_index > 0) need_shift.first += 5;
                else need_shift.first += 10;
            }
            else if (event.key.code == sf::Keyboard::A) animations = !animations;
            else if (event.key.code == sf::Keyboard::L) draw_lines = !draw_lines;
            else if (event.key.code == sf::Keyboard::C) RandomColor();
        }
        else if (event.type == sf::Event::MouseWheelMoved) {
            if (event.mouseWheel.delta > 0 && cur_size_index < 6) ++cur_size_index;
            else if (event.mouseWheel.delta < 0 && cur_size_index > 0) --cur_size_index;
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition();
            if (start_mouse_pos.first >= 0 && start_mouse_pos.second >= 0) {
                need_shift.first -= (mouse_pos.x - start_mouse_pos.first) / cur_size;
                need_shift.second += (mouse_pos.y - start_mouse_pos.second) / cur_size;
            }
            start_mouse_pos.first = mouse_pos.x;
            start_mouse_pos.second = mouse_pos.y;
        }
        else if (sf::Event::MouseButtonReleased) {
            start_mouse_pos.first = -1;
            start_mouse_pos.second = -1;
            need_shift.first = std::round(need_shift.first);
            need_shift.second = std::round(need_shift.second);
        }
    }
    return;
}

int main() {
    std::srand(std::time(nullptr));
    sf::Window window(sf::VideoMode(window_width, window_height), "Practical 1", sf::Style::Close);
    window.setActive(true);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    double time = 0;
    while (window.isOpen()) {
        std::chrono::duration<double> t = std::chrono::system_clock::now().time_since_epoch();
        if (time > 0) {
            double fps = 1 / (t.count() - time);
            animation_speed = std::abs(animation_coefficient * fps / 60);
            window.setTitle("Practical 1 (x: " + std::to_string((int)std::round(cur_shift.first)) +
                ", y: " + std::to_string((int)std::round(cur_shift.second)) +
                ", " + std::to_string((int)std::round(cur_size)) + " pixels per unit, " +
                std::to_string((int)fps) + " fps)");
        }
        time = t.count();

        glClear(GL_COLOR_BUFFER_BIT);
        FillScreen(background_color);

        EventProcess(window);
        AnimationProcess();

        DrawSecondLines();
        DrawGraphs();
        //DrawSecondLines();
        DrawMainLines();

        glDrawPixels(window_width, window_height, GL_RGB, GL_UNSIGNED_BYTE, &frame_buffer);
        window.display();
    }

    return 0;
}