#include "IO.h"

IO::Exception::Exception(const std::string& description) {
	this->description = description;
	return;
}


void IO::loadText(const std::string& fileName, std::string& text) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
	}

	text = "";
	char symbol;
	while (file.get(symbol)) {
		text += symbol;
	}
	file.close();
	return;
}

void IO::saveText(const std::string& fileName, const std::string& text) {
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
	}

	for (uint64_t i = 0; i < text.size(); ++i) {
		file << text[i];
	}
	file.close();
	return;
}

void IO::loadTable(const std::string& fileName, Huffman::Table& table) {
    std::ifstream file(fileName, std::ios_base::binary);
    if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
    }

    uint8_t n;
    file.read((char*)&n, sizeof(uint8_t));

    for (uint8_t i = 0; i < n; ++i) {
        char symbol;
        uint8_t length;
        file.read((char*)&symbol, sizeof(char));
        file.read((char*)&length, sizeof(uint8_t));

        std::string code;
        uint8_t byteCode;
        file.read((char*)&byteCode, sizeof(uint8_t));
        for (int j = 0; j < length; ++j) {
            code += std::to_string((byteCode >> j) & 1);
        }
        table.set(symbol, code);
    }
    file.close();
    return;
}

void IO::loadEncoded(const std::string& fileName, std::string& text) {
    std::ifstream file(fileName, std::ios_base::binary);
    if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
    }

    uint32_t size;
    file.read((char*)&size, sizeof(int));
    while (size > 0) {
        uint8_t byte;
        file.read((char*)&byte, sizeof(uint8_t));
        for (int i = 0; i < 8 && size > 0; ++i) {
            text += std::to_string((byte >> i) & 1);
            --size;
        }
    }
    file.close();
    return;
}

void IO::loadTree(const std::string& fileName, Huffman::Tree& tree) {
    std::ifstream file(fileName, std::ios_base::binary);
    if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
    }

    uint8_t leaves;
    file.read((char*)&leaves, sizeof(uint8_t));

    std::vector<Huffman::Node*> vertexes;
    for (uint8_t i = 0; i < leaves; ++i) {
        char symbol;
        file.read((char*)&symbol, sizeof(char));
        vertexes.push_back(new Huffman::Node(symbol, 0));
    }

    for (int i = 0; i < leaves - 1; ++i) {
        uint8_t left;
        uint8_t right;
        file.read((char*)&left, sizeof(uint8_t));
        file.read((char*)&right, sizeof(uint8_t));
        Huffman::Node* vertex = new Huffman::Node(0);
        vertex->left = vertexes[left];
        vertex->right = vertexes[right];
        vertexes.push_back(vertex);
    }
    file.close();
    tree.start = vertexes[2 * leaves - 2];
    return;
}

void IO::saveTree(const std::string& fileName, Huffman::Tree tree) {
    std::ofstream file(fileName, std::ios_base::binary);
    if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
    }

    uint8_t symbols = tree.countSymbols();
    file.write((char*)&symbols, sizeof(uint8_t));

    std::vector<char> letters(symbols, 0);
    std::vector<std::pair<uint8_t, uint8_t>> vertexes(symbols * 2 - 1, std::pair<uint8_t, uint8_t>(0, 0));
    this->saveNode(tree.start, letters, vertexes);
    for (uint8_t i = 0; i < letters.size(); ++i) {
        file.write((char*)&letters[i], sizeof(char));
    }
    for (uint16_t i = symbols; i < vertexes.size(); ++i) {
        file.write((char*)&vertexes[i].first, sizeof(char));
        file.write((char*)&vertexes[i].second, sizeof(char));
    }
    file.close();
    return;
}

void IO::saveTable(const std::string& fileName, Huffman::Table table) {
    std::ofstream file(fileName, std::ios_base::binary);
    if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
    }

    uint8_t size = table.size();
    file.write((char*)&size, sizeof(uint8_t));

    for (uint8_t i = 0; i < 128; ++i) {
        if (table.exist(i)) {
            file.write((char*)&i, sizeof(char));
            std::string code = table.get(i);
            uint8_t sz = code.size();
            file.write((char*)&sz, sizeof(char));
            uint8_t byte = 0;
            for (uint8_t j = 0; j < sz; ++j) {
                byte |= (code[j] - '0') << j;
            }
            file.write((char*)&byte, sizeof(char));
        }
    }
    file.close();
    return;
}

void IO::saveEncoded(const std::string& fileName, const std::string& text) {
    std::ofstream file(fileName, std::ios_base::binary);
    if (!file.is_open()) {
        throw IO::Exception("Failed to open the file (" + fileName + ")");
    }

    uint32_t length = text.size();
    file.write((char*)&length, sizeof(int));
    for (int32_t i = 0; i <= length / 8; ++i) {
        uint8_t byte = 0;
        for (uint8_t j = 0; j < 8 && j + i * 8 < length; ++j) {
            byte |= (text[i * 8 + j] - '0') << j;
        }
        file.write((char*)&byte, sizeof(uint8_t));
    }
    file.close();
    return;
}

void IO::saveNode(Huffman::Node* node, std::vector<char>& letters, std::vector<std::pair<uint8_t, uint8_t>>& vertexes) {
    if (node == nullptr) return;
    if (node->left == nullptr) {
        letters[node->number] = node->symbol;
        return;
    }
    vertexes[node->number] = std::pair<uint8_t, uint8_t>(node->left->number, node->right->number);
    this->saveNode(node->left, letters, vertexes);
    this->saveNode(node->right, letters, vertexes);
    return;
}
