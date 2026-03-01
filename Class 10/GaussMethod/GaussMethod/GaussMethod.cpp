#include <iostream>
#include <vector>

int main() {
	while (true) {
		std::cout << "Enter matrix size (w, h). 0 to exit: ";
		uint16_t width, height;
		std::cin >> width;
		if (width == 0) break;
		std::cin >> height;
		if (height == 0) break;

		std::cout << "Enter matrix (double supported)" << std::endl;
		std::vector<std::vector<double>> matrix(height, std::vector<double>(width, 0));
		for (int16_t i = 0; i < height; ++i) {
			for (uint16_t j = 0; j < width; ++j) {
				std::cin >> matrix[i][j];
			}
		}
	}

	return 0;
}