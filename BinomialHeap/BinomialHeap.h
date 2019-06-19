#pragma once
#include <list> 
#include <iostream>

using namespace std;

struct Node {
	int key = NULL, degree = 0;
	Node *child, *sibling, *parent;
};

struct Heap {
	Node* head;
};

class BinomialHeap {
public:
	BinomialHeap() {}
	Heap* createBinHeap();
	Node* createNode(int key);
	Node* mergeHeaps(Heap* H1, Heap* H2);
	Heap* unionHeaps(Heap* H1, Heap* H2);
	Node* findNode(Heap* H, int k);
	Node* findMinimum(Heap* H);
	Node* extractMin(Heap* H);
	Node* revertHeap(Node* H);
	void linkHeaps(Node* y, Node* z);
	void decreaseKey(Heap*H, int old_k, int k);
	void insert(Heap* H, int x);
	void deleteNode(Heap* H, int k);

	void display(Heap* H);
};
