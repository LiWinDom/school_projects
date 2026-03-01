#include "Huffman.h"

Huffman::Node::Node(const uint64_t& frequency) {
	this->frequency = frequency;
	return;
}

Huffman::Node::Node(const char& symbol, const uint64_t& frequency) {
	this->symbol = symbol;
	this->frequency = frequency;
	return;
}


void Huffman::Tree::generate(const std::vector<uint64_t>& frequencyArray) {
	uint8_t counter = 0;

	for (uint8_t i = 0; i < 128 && i < frequencyArray.size(); ++i) {
		if (frequencyArray[i] > 0) {
			Huffman::Node* cur = new Node(i, frequencyArray[i]);
			cur->number = counter++;
			if (this->start == nullptr) {
				this->start = cur;
				continue;
			}

			// Searching position
			Huffman::Node* q = this->start;
			while (q->next != nullptr && q->next->frequency < cur->frequency) {
				q = q->next;
			}
			if (q == this->start) {
				cur->next = this->start;
				this->start = cur;
			}
			else {
				cur->next = q->next;
				q->next = cur;
			}
		}
	}

	while (this->start->next != nullptr) {
		Huffman::Node* left = this->start;
		Huffman::Node* right = left->next;
		this->start = right->next;

		Huffman::Node* vert = new Huffman::Node(left->frequency + right->frequency);
		vert->number = counter++;
		left->next = nullptr;
		right->next = nullptr;
		vert->left = left;
		vert->right = right;

		if (this->start == nullptr) {
			this->start = vert;
			break;
		}

		// Searching position
		Huffman::Node* q = this->start;
		while (q->next != nullptr && q->next->frequency < vert->frequency) {
			q = q->next;
		}
		if (q == this->start) {
			vert->next = this->start;
			this->start = vert;
		}
		else {
			vert->next = q->next;
			q->next = vert;
		}
	}
	return;
}

uint8_t Huffman::Tree::countSymbols() {
	return this->countSymbols(this->start);
}

void Huffman::Tree::clear() {
	this->clear(this->start);
	this->start = nullptr;
	return;
}

uint8_t Huffman::Tree::countSymbols(const Huffman::Node* node) {
	if (node == nullptr) return 0;
	if (node->left == nullptr) return 1;
	return this->countSymbols(node->left) + this->countSymbols(node->right);
}

void Huffman::Tree::clear(const Node* node) {
	if (node == nullptr) return;
	this->clear(node->left);
	this->clear(node->right);
	delete node;
	return;
}


void Huffman::Table::generate(const Tree& tree) {
	this->generateNode(tree.start);
	return;
}

std::string Huffman::Table::get(const char& symbol) {
	return this->table[symbol];
}

void Huffman::Table::set(const char& symbol, const std::string& code) {
	this->table[symbol] = code;
	return;
}

bool Huffman::Table::exist(const char& symbol) {
	return this->table.count(symbol) > 0;
}

uint8_t Huffman::Table::size() {
	return this->table.size();
}

void Huffman::Table::clear() {
	this->table.clear();
	return;
}

void Huffman::Table::generateNode(const Huffman::Node* node, const std::string& buf) {
	if (node == nullptr) return;
	if (node->left == nullptr) {
		this->table[node->symbol] = buf;
		return;
	}
	this->generateNode(node->left, buf + "0");
	this->generateNode(node->right, buf + "1");
	return;
}


void Huffman::generate(const std::string& text, Huffman::Tree& tree, Huffman::Table& table) {
	std::vector<uint64_t> frequencyArray(128, 0);
	for (uint64_t i = 0; i < text.size(); ++i) {
		if (text[i] > 127) continue;
		++frequencyArray[text[i]];
	}
	tree.generate(frequencyArray);
	table.generate(tree);
	return;
}

std::string Huffman::encode(const std::string& text, Huffman::Table table) {
	std::string encoded = "";
	for (uint64_t i = 0; i < text.size(); ++i) {
		encoded += table.get(text[i]);
	}
	return encoded;
}

std::string Huffman::decode(const std::string& binary, const Huffman::Tree& tree) {
	std::string decoded = "";
	Huffman::Node* q = tree.start;

	for (uint64_t i = 0; i < binary.size(); ++i) {
		if (binary[i] == '0') q = q->left;
		else q = q->right;
		if (q->left == nullptr) {
			decoded += q->symbol;
			q = tree.start;
		}
	}
	return decoded;
}