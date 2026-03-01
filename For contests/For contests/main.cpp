#include <iostream>
#include <vector>

class Rectangle {
public:
	Rectangle(double width, double height) : _width(width), _height(height) {}

	double getWidth() const { return _width; }

	double getHeight() const { return _height; }


	double getArea() const { return _width * _height; };

	void printWidth() const {
		std::cout << _width;
	}

	void printHeight() const {
		std::cout << _height;
	}

private:
	 double _width, _height;
};

int main() {
	size_t n;
	std::cout << "Number of Rectangles: ";
	std::cin >> n;
	std::vector<Rectangle> rectangles;

	double limit;
	std::cout << "Area limit: ";
	std::cin >> limit;

	for (size_t i = 0; i < n; ++i) {
		double width, height;
		std::cout << "Width and height of rectangle #" << i << ": ";
		std::cin >> width >> height;
		rectangles.push_back(Rectangle(width, height));
	}
	std::cout << std::endl;

	for (auto rect : rectangles) {
		if (rect.getArea() <= limit) continue;
		std::cout << "Rectangle width: " << rect.getWidth() << ", height: " << rect.getHeight() << ", area: " << rect.getArea() << std::endl;
	}
	return 0;
}
