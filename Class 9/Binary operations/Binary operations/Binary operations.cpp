#include <iostream>
#include <string>

void prt(int ln, std::string past = "") {
	if (ln == 0) {
		std::cout << past + '\n';
		return;
	}
	prt(ln - 1, past + '0');
	prt(ln - 1, past + '1');

	return;
}

int main() {
	int a;
	std::cin >> a;
	prt(a);

	return 0;
}