#include <iostream>

#include "Huffman.h"
#include "IO.h"

Huffman huf;
Huffman::Tree tree;
Huffman::Table table;
IO io;

void getline(std::string& text) {
	char symbol;
	std::cin.get(symbol);
	while (symbol != '\n') {
		text += symbol;
		std::cin.get(symbol);
	}
	return;
}

void saveDialogue(std::string& text) {
	std::cout << "Save decoded message to file: ";
	std::string fileName;
	getline(fileName);
	io.saveText(fileName, text);
	return;
}

void loadDialogue(std::string& text) {
	std::cout << "1) Load text from file" << std::endl;
	std::cout << "2) Enter text" << std::endl;
	std::cout << "Select: ";

	char choice;
	std::cin >> choice;
	std::cout << std::endl;
	char symbol;
	std::cin.get(symbol);

	if (choice == '1') {
		std::cout << "Enter file name: ";
		std::string fileName;
		getline(fileName);
		io.loadText(fileName, text);
	}
	else if (choice == '2') {
		std::cout << "Enter text: ";
		getline(text);
	}
	else {
		std::cout << "Invalid entered!" << std::endl;
	}
	return;
}

void saveEncoded(const std::string& text) {
	std::cout << "Save encoded message to file: ";

	std::string fileName;
	getline(fileName);
	io.saveEncoded(fileName, text);
	return;
}

void loadEncoded(std::string& text) {
	std::cout << "Load encoded message from file: ";

	std::string fileName;
	getline(fileName);
	io.loadEncoded(fileName, text);
	return;
}

void loadTree() {
	std::cout << "Load tree from file: ";

	std::string fileName;
	getline(fileName);
	io.loadTree(fileName, tree);
	return;
}

void loadTable() {
	std::cout << "Load table from file: ";

	std::string fileName;
	getline(fileName);
	io.loadTable(fileName, table);
	return;
}

void saveTree() {
	std::cout << "Save tree to file: ";

	std::string fileName;
	getline(fileName);
	io.saveTree(fileName, tree);
	return;
}

void saveTable() {
	std::cout << "Save table to file: ";

	std::string fileName;
	getline(fileName);
	io.saveTable(fileName, table);
	return;
}

void moreThings() {
	while (true) {
		std::cout << "More:" << std::endl;
		std::cout << "0) Back" << std::endl;
		std::cout << "1) Generate tree and table from text" << std::endl;
		std::cout << "2) Encode text with table" << std::endl;
		std::cout << "3) Decode text with tree" << std::endl;
		std::cout << "Select: ";

		char choice;
		std::cin >> choice;
		std::cout << std::endl;
		char symbol;
		std::cin.get(symbol);

		if (choice == '0') {
			break;
		}
		else if (choice == '1') {
			try {
				std::string text;
				loadDialogue(text);
				huf.generate(text, tree, table);
				saveTree();
				saveTable();
				tree.clear();
				table.clear();
				std::cout << "OK!" << std::endl;
			}
			catch (IO::Exception ex) {
				std::cout << ex.description << std::endl;
			}
		}
		else if (choice == '2') {
			try {
				std::string text;
				loadDialogue(text);
				loadTable();
				text = huf.encode(text, table);
				saveEncoded(text);
				table.clear();
				std::cout << "OK!" << std::endl;
			}
			catch (IO::Exception ex) {
				std::cout << ex.description << std::endl;
			}
		}
		else if (choice == '3') {
			try {
				std::string text;
				loadEncoded(text);
				loadTree();
				text = huf.decode(text, tree);
				saveDialogue(text);
				tree.clear();
				std::cout << "OK!" << std::endl;
			}
			catch (IO::Exception ex) {
				std::cout << ex.description << std::endl;
			}
		}
		else {
			std::cout << "Invalid entered!" << std::endl;
		}
		std::cout << std::endl;
	}
}

void mainMenu() {
	while (true) {
		std::cout << "Main menu:" << std::endl;
		std::cout << "0) Exit program" << std::endl;
		std::cout << "1) Encode text" << std::endl;
		std::cout << "2) Decode .hfm file" << std::endl;
		std::cout << "3) More..." << std::endl;
		std::cout << "Select: ";

		char choice;
		std::cin >> choice;
		std::cout << std::endl;
		char symbol;
		std::cin.get(symbol);

		if (choice == '0') {
			break;
		}
		else if (choice == '1') {
			std::string text;
			loadDialogue(text);
		}
		else if (choice == '2') {
			std::cout << "Not finished now, sorry" << std::endl;
		}
		else if (choice == '3') {
			moreThings();
		}
		else {
			std::cout << "Invalid entered!" << std::endl;
		}
		std::cout << std::endl;
	}
}

int main() {
	mainMenu();
	return 0;
}
