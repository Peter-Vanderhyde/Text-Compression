/*
Peter Vanderhyde
Final Project
12/09/2020
*/
#include <iostream>
#include <map>
#include <sstream>
#include <bitset>
#include "Maps.h"
#include "PriorityQueue.h"
#include "HuffmanTree.h"

void print(FrequencyTable table);
void print(HuffmanCodes table);
void build_queue(PriorityQueue& pq, FrequencyTable table);
Node* build_tree(PriorityQueue& pq);
std::string binary(const std::string& text);
std::string encode(const std::string& text, HuffmanCodes codes);
std::string decode(const std::string& encoded, HuffmanTree& tree);
bool is_leaf(Node* n);

int main() {
	try {
		std::string text = "";
		while (text == "") {
			std::cout << "Enter text:\n";
			std::getline(std::cin, text);
		}

		FrequencyTable table = build_frequency_table(text);
		std::cout << "\nFrequency Table:\n";
		print(table);

		PriorityQueue pq;
		build_queue(pq, table);
		std::cout << "\nPriority Queue:\n";
		std::cout << pq << "\n";

		Node* root = build_tree(pq);
		HuffmanTree tree{ root };
		std::cout << "\nHuffman encoding tree:\n";
		pprint(tree.get_root());

		HuffmanCodes codes = build_code_table(tree);
		std::cout << "\nHuffman codes:\n";
		print(codes);

		std::string uncompressed = binary(text);
		std::cout << "\nUncompressed bit sequence:\n" << uncompressed << "\n";

		std::string encoded = encode(text, codes);
		std::cout << "\nEncoded:\n" << encoded << "\n";

		std::string decoded = decode(encoded, tree);
		std::cout << "\nDecoded:\n" << decoded << "\n";

		double uncompressed_length = uncompressed.length();
		double encoded_length = encoded.length();

		std::cout << "\nCompressed to " << encoded_length / uncompressed_length * 100 << "% of original size.\n";
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}

	return 0;
}

void print(FrequencyTable table) {
	std::map<char, int>::iterator it;
	for (it = table.begin(); it != table.end(); it++) {
		std::cout << it->first << ": " << it->second << "\n";
	}
}

void print(HuffmanCodes table) {
	std::map<char, std::string>::iterator it;
	for (it = table.begin(); it != table.end(); it++) {
		std::cout << it->first << ": " << it->second << "\n";
	}
}

void build_queue(PriorityQueue& pq, FrequencyTable table) {
	std::map<char, int>::iterator it;
	for (it = table.begin(); it != table.end(); it++) {
		std::stringstream ss;
		ss << it->first;
		Node* n = new Node{ ss.str(), it->second };
		pq.insert(n);
	}
}

Node* build_tree(PriorityQueue& pq) {
	Node* left = pq.get_head();
	Node* right;
	while (left->next) {
		std::string letters = left->letters;
		int freqs = left->frequency;
		right = left->next;
		letters += right->letters;
		freqs += right->frequency;
		pq.remove();
		pq.remove();
		Node* n = new Node{ letters, freqs };
		n->left = left;
		n->right = right;
		pq.insert(n);
		left = pq.get_head();
	}

	return left;
}

std::string binary(const std::string& text) {
	std::stringstream ss;
	for (char c : text) {
		ss << std::bitset <8>(c);
	}
	return ss.str();
}

std::string encode(const std::string& text, HuffmanCodes codes) {
	std::string encoded;
	for (char c : text) {
		encoded += codes[c];
	}
	return encoded;
}

std::string decode(const std::string& encoded, HuffmanTree& tree) {
	std::string decoded;
	Node* n = tree.get_root();
	for (int i = 0; i < encoded.length(); i++) {
		if (is_leaf(n)) {
			decoded += n->letters;
			n = tree.get_root();
		}
		else if (encoded[i] == '0') {
			n = n->left;
			if (is_leaf(n)) {
				decoded += n->letters;
				n = tree.get_root();
			}
		}
		else if (encoded[i] == '1') {
			n = n->right;
			if (is_leaf(n)) {
				decoded += n->letters;
				n = tree.get_root();
			}
		}
	}
	return decoded;
}

bool is_leaf(Node* n) {
	return (!n->left && !n->right);
}