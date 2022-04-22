/*
Peter Vanderhyde
Final Project
12/09/2020
*/
#pragma once
#include <iostream>

struct Node {
	Node(std::string letters, int frequency, Node* next = nullptr,
		Node* left = nullptr, Node* right = nullptr)
		: letters{ letters }, frequency{ frequency }, next{ next },
		left{ left }, right{ right } {}

	std::string letters;
	int frequency;
	Node* next, * left, * right;
};