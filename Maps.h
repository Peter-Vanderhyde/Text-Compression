/*
Peter Vanderhyde
Final Project
12/09/2020
*/
#pragma once
#include <iostream>
#include <map>
#include "HuffmanTree.h"

using FrequencyTable = std::map<char, int>;
using HuffmanCodes = std::map<char, std::string>;

FrequencyTable build_frequency_table(const std::string& text) {
	FrequencyTable table;
	for (char c : text) {
		if (table.find(c) != table.end()) {
			table[c] += 1;
		}
		else {
			table.insert(std::pair<char, int>(c, 1));
		}
	}
	return table;
}

void get_code(HuffmanCodes& table, Node* n, std::string code = "") {
	if (!n->left && !n->right) {
		if (code != "") {
			table.insert(std::pair<char, std::string>(n->letters[0], code));
		}
		else {
			table.insert(std::pair<char, std::string>(n->letters[0], "0"));
		}
	}
	else {
		if (n->left) {
			get_code(table, n->left, code + "0");
		}
		if (n->right) {
			get_code(table, n->right, code + "1");
		}
	}
}

HuffmanCodes build_code_table(HuffmanTree& tree) {
	HuffmanCodes table;
	get_code(table, tree.get_root());
	return table;
}