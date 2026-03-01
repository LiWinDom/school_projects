#include <iostream>
//#include <random>

//std::mt19937 gen(61);
//std::uniform_int_distribution<int16_t> dist;

struct Node {
	int data;
	//Node* prev = nullptr;
	Node* next = nullptr;
};

Node* start = nullptr;

/*void sort(Node*& s, const size_t& elemNum) {
	if (s == nullptr || s->next == nullptr) return;

	Node* cur = s;
	for (size_t i = 0; i < elemNum / 2; ++i) {
		cur = cur->next;
	}
	cur->prev->next = nullptr;
	cur->prev = nullptr;

	sort(s, elemNum / 2);
	sort(cur, elemNum - elemNum / 2);

	Node* curL = s, *curR = cur;
	if (curL->data < curR->data) {
		s = curL;
		curL = curL->next;
	}
	else {
		s = curR;
		curR = curR->next;
	}
	cur = s;
	while (curL != nullptr && curR != nullptr) {
		if (curL->data < curR->data) {
			curL->prev = cur;
			cur->next = curL;
			cur = curL;
			curL = curL->next;
		}
		else {
			curR->prev = cur;
			cur->next = curR;
			cur = curR;
			curR = curR->next;
		}
	}
	if (curL != nullptr) {
		curL->prev = cur;
		cur->next = curL;
		cur = curL;
		curL = curL->next;
	}
	if (curR != nullptr) {
		curR->prev = cur;
		cur->next = curR;
		cur = curR;
		curR = curR->next;
	}

	return;
}*/

void print(Node* s) {
	while (s != nullptr) {
		std::cout << s->data << ' ';
		s = s->next;
	}
	return;
}

void rotat(Node* s) {
	if (s == nullptr) return;
	if (s->next == nullptr) {
		start = s;
		return;
	}
	rotat(s->next);
	s->next = nullptr;
	Node* cr = start;
	while (cr->next != nullptr) {
		cr = cr->next;
	}
	cr->next = s;
	return;
}

/*bool check(Node*& s) {
	if (s == nullptr || s->next == nullptr) return true;

	int past = s->data;
	Node* cur = s->next;
	while (cur != nullptr) {
		if (past > cur->data) {
			return false;
		}
		past = cur->data;
		cur = cur->next;
	}
	return true;
}

void clear(Node*& start) {
	Node* cur = start, *del;
	while (cur != nullptr) {
		del = cur;
		cur = cur->next;
		delete del;
	}
	return;
}*/

int main() {
	/*while (true) {
		Node* start = nullptr;
		Node* cur = nullptr;
		int n;
		std::cout << "Enter number of random elements (0 to exit): ";
		std::cin >> n;
		if (n < 1) {
			return 0;
		}

		std::cout << "Generating array...";
		for (int i = 0; i < n; ++i) {
			Node* q = new Node;
			q->data = dist(gen);
			if (start != nullptr) {
				start->prev = q;
				q->next = start;
			}
			start = q;
		}

		std::cout << " Done" << std::endl << "Sorting array...";
		sort(start, n);
		std::cout << " Done" << std::endl << "Checking sort...";
		if (!check(start)) {
			std::cout << " Something went wrong";
			return 0;
		}
		std::cout << " OK!" << std::endl << "Clearing data...";
		clear(start);
		std::cout << " Done" << std::endl << std::endl;
	}*/

	Node* cur = nullptr;
	int num;
	std::cin >> num;
	while (num != 0) {
		if (start == nullptr) {
			start = new Node;
			cur = start;
		}
		else {
			cur->next = new Node;
			cur = cur->next;
		}
		cur->data = num;
		std::cin >> num;
	}

	rotat(start);
	print(start);

	return 0;
}