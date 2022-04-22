/*
Peter Vanderhyde
Final Project
12/09/2020
*/
# pragma once
#include <iostream>
#include "Node.h"

bool insert_node(Node* n, std::string letters, int frequency);
void postorder(Node* n);


class HuffmanTree {
public:
	HuffmanTree() {
		root = nullptr;
	}

	HuffmanTree(Node* n) {
		root = n;
	}

	/* Gives me an error at the end of the program for some reason */
	//~HuffmanTree() {
	//	postorder(root);
	//}

	void insert(std::string letters, int frequency) {
		if (root) {
			insert_node(root, letters, frequency);
		}
		else {
			root = new Node{ letters, frequency };
		}
	}

	Node* get_root() {
		return root;
	}

private:
	Node* root;
};

bool insert_node(Node* n, std::string letters, int frequency) {
	if (!n) {
		return false;
	}
	if (frequency <= n->frequency) {
		if (!insert_node(n->left, letters, frequency)) {
			n->left = new Node{ letters, frequency };
		}
	}
	else {
		if (!insert_node(n->right, letters, frequency)) {
			n->right = new Node{ letters, frequency };
		}
	}
	return true;
}

void postorder(Node* n) {
	if (!n) {
		return;
	}
	postorder(n->left);
	postorder(n->right);
	delete n;
}

void pprint(Node* n, int depth = 0) {
	if (!n) {
		return;
	}
	std::string spaces = "";
	for (int i = 0; i < depth; i++) {
		spaces += "   ";
	}

	pprint(n->right, depth + 1);
	std::cout << spaces << "(" << n->letters << ", " << n->frequency << ")\n";
	pprint(n->left, depth + 1);
}