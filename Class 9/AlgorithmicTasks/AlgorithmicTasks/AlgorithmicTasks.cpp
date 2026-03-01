#include <iostream>
#include <queue>

void readCards(std::queue<int>& user) {
	for (int i = 0; i < 5; ++i) {
		int card;
		std::cin >> card;
		user.push(card);
	}
	return;
}

void printCards(std::queue<int> user) {
	while (user.size() != 0) {
		int card = user.front();
		std::cout << card << ' ';
		user.pop();
	}
	std::cout << '\n';
	return;
}

int main() {
	std::queue<int> first, second;

	readCards(first);
	readCards(second);

	for (unsigned long long i = 1; ; ++i) {
		if (i > 1000000) {
			std::cout << "botva";
			break;
		}

		//printCards(first);
		//printCards(second);
		//std::cout << '\n';

		int firstCard = first.front();
		int secondCard = second.front();
		first.pop();
		second.pop();

		if (firstCard > secondCard && (firstCard != 9 || secondCard != 0) || (firstCard == 0 && secondCard == 9)) {
			first.push(firstCard);
			first.push(secondCard);
			if (second.size() == 0) {
				std::cout << "first " << i;
				break;
			}
		}
		else {
			second.push(firstCard);
			second.push(secondCard);
			if (first.size() == 0) {
				std::cout << "second " << i;
				break;
			}
		}
	}

	return 0;
}