#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <map>

class Huffman
{
public:
	struct Node {
		Node(const uint64_t& frequency);

		Node(const char& symbol, const uint64_t& frequency);

		char symbol = 0;
		uint64_t frequency = 0;
		Huffman::Node* left = nullptr, * right = nullptr;
		Huffman::Node* next = nullptr;
		uint16_t number = 0;
	};

	struct Tree {
	public:
		void generate(const std::vector<uint64_t>& frequencyArray);

		uint8_t countSymbols();

		void clear();

		Huffman::Node* start = nullptr;

	private:
		void clear(const Node* node);

		uint8_t countSymbols(const Node* node);
	};

	struct Table {
	public:
		void generate(const Huffman::Tree& tree);

		std::string get(const char& symbol);

		void set(const char& symbol, const std::string& code);

		bool exist(const char& symbol);

		uint8_t size();

		void clear();
	private:
		void generateNode(const Huffman::Node* node, const std::string& buf = "");

	private:
		std::map<char, std::string> table;
	};

	void generate(const std::string& text, Tree& tree, Table& table);

	std::string encode(const std::string& text, Table table);

	std::string decode(const std::string& text, const Tree& tree);
};

