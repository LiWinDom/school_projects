#pragma once
#include <algorithm>
#include <string>
#include <fstream>

#include "Huffman.h"

class IO
{
public:
	struct Exception {
		Exception(const std::string& description);

		std::string description;
	};

	void loadText(const std::string& fileName, std::string& text);

	void saveText(const std::string& fileName, const std::string& text);

    void loadTable(const std::string& fileName, Huffman::Table& table);

    void loadEncoded(const std::string& fileName, std::string& text);

    void loadTree(const std::string& fileName, Huffman::Tree& tree);

	void saveTree(const std::string& fileName, Huffman::Tree tree);

	void saveTable(const std::string& fileName, Huffman::Table table);

	void saveEncoded(const std::string& fileName, const std::string& text);

private:
	void saveNode(Huffman::Node* node, std::vector<char>& letters, std::vector<std::pair<uint8_t, uint8_t>>& vertexes);
};

