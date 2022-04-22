/*
Peter Vanderhyde
Final Project
12/09/2020
*/
#pragma once
#include <iostream>
#include "Node.h"

class PriorityQueue {
protected:

	Node* head;

public:
	PriorityQueue()
		:head{ nullptr } {}

	~PriorityQueue() {
		while (!empty()) {
			Node* deleteMe = head;
			head = head->next;
			delete deleteMe;
		}
	}

	bool empty() const {
		return head == nullptr;
	}

	void insert(Node* n) {
		if (empty()) {
			n->next = nullptr;
			head = n;
		}
		else if (n->frequency < head->frequency) {
			n->next = head;
			head = n;
		}
		else {
			Node* tmp = head;
			while (tmp->next && n->frequency >= tmp->next->frequency) {
				tmp = tmp->next;
			}
			n->next = tmp->next;
			tmp->next = n;
		}
	}

	void remove() {
		if (!empty()) {
			head = head->next;
		}
		else {
			throw std::runtime_error("Attempted to remove from an empty list!");
		}
	}

	Node* get_head() {
		return head;
	}

	friend std::ostream& operator<<(std::ostream& os, const PriorityQueue& queue) {
		Node* current = queue.head;
		while (current) {
			os << "(" << current->letters << ", " << current->frequency << ")" << " -> ";
			current = current->next;
		}
		return os << " nullptr";
	}
};