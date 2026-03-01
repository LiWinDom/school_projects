#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Larez {
	std::vector<std::string> elems;
};

std::vector<Larez> aaa;

void printLarez(int num) {
	for (int i = 0; i < aaa[num].elems.size(); ++i) {
		std::string elem = aaa[num].elems[i];
		if (elem[0] == '_') {
			printLarez(elem[1] - '0');
		}
		else {
			std::cout << elem << ' ';
		}
	}

	return;
}

int main() {
	std::string fileName;
	std::ifstream file;

	std::cout << "File name: ";
	std::cin >> fileName;
	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "File \"" << fileName << "\" cannot be open";
		return 1;
	}

	while (!file.eof()) {
		Larez larez;
		size_t num;
		char kostyl;

		file >> num;
		file.get(kostyl);
		aaa.resize(std::max(num + 1, aaa.size()));

		while (file.peek() != '\n' && !file.eof()) {
			std::string elem;
			file >> elem;
			larez.elems.push_back(elem);
		}

		aaa[num] = larez;
	}

	file.close();

	for (int i = 1; i < aaa.size(); ++i) {
		std::cout << "Larez #" << i << ": ";
		printLarez(i);
		std::cout << '\n';
	}

	return 0;
}