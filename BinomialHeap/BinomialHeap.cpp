#include "BinomialHeap.h"

Heap* BinomialHeap::createBinHeap() {
	Heap* heap = new Heap;
	heap->head = nullptr;
	return heap;
}

Node* BinomialHeap::createNode(int key) {
	Node* node = new Node;
	node->key = key;
	node->child = nullptr;
	node->parent = nullptr;
	node->sibling = nullptr;
	node->degree = 0;
	return node;
}

void BinomialHeap::linkHeaps(Node* y, Node* z) {
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

Node* BinomialHeap::mergeHeaps(Heap* H1, Heap* H2) {
	if (H1->head == nullptr)
		return H2->head;
	if (H2->head == nullptr)
		return H1->head;
	Node* H = nullptr;
	Node* P1 = H1->head;
	Node* P2 = H2->head;
	if (P1->degree <= P2->degree) {
		H = H1->head;
	}
	else if (P1->degree > P2->degree) {
		H = H2->head;
	}
	while (P1 != nullptr && P2 != nullptr) {
		if (P1->degree < P2->degree) {
			P1 = P1->sibling;
		}
		else if (P1->degree == P2->degree) {
			Node* T = P1->sibling;
			P1->sibling = P2;
			P1 = T;
		}
		else {
			Node* T = P2->sibling;
			P2->sibling = P1;
			P2 = T;
		}
	}
	return H;
}

Heap* BinomialHeap::unionHeaps(Heap* H1, Heap* H2) {
	Heap* H = createBinHeap();
	H->head = mergeHeaps(H1, H2);
	H1->head = nullptr;
	H2->head = nullptr;
	if (H->head == nullptr) {
		cout << "Heap is empty (union operation)" << endl;
		return nullptr;
	}

	Node* prev_x = nullptr;
	Node* x = H->head;
	Node* next_x = x->sibling;
	while (next_x != nullptr)
	{
		if ((x->degree != next_x->degree) || ((next_x->sibling != nullptr)
			&& (next_x->sibling)->degree == x->degree))
		{
			prev_x = x;
			x = next_x;
		}
		else
		{
			if (x->key <= next_x->key)
			{
				x->sibling = next_x->sibling;
				linkHeaps(next_x, x);
			}
			else {
				if (prev_x == nullptr)
					H->head = next_x;
				else
					prev_x->sibling = next_x;
				linkHeaps(x, next_x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
	return H;
}

void BinomialHeap::insert(Heap* H, int x) {
	Node* node = createNode(x);
	Heap* _H = createBinHeap();
	_H->head = node;
	*(H) = *(unionHeaps(H, _H));
}

Node* BinomialHeap::findNode(Heap* H, int k) {
	Node* x = H->head;
	if (x == nullptr) {
		cout << "Heap is empty (search operation)";
		return nullptr;
	}
	Node* p = nullptr;
	if (x->key == k) {
		p = x;
		return p;
	}
	if (x->child != nullptr && p == nullptr) {
		Heap* T = createBinHeap();
		T->head = x->child;
		p = findNode(T, k);
	}
	if (x->sibling != nullptr && p == nullptr) {
		Heap* T = createBinHeap();
		T->head = x->sibling;
		p = findNode(T, k);
	}
	return p;
}

Node* BinomialHeap::findMinimum(Heap* heap) {
	Node* y = nullptr;
	Node* x = heap->head;
	int min = INT_MAX;
	while (x != nullptr) {
		if (x->key < min) {
			min = x->key;
			y = x;
		}
		x = x->sibling;
	}
	return y;
}

Node* BinomialHeap::revertHeap(Node* H) {
	if (H->sibling != nullptr) {
		Node* head = revertHeap(H->sibling);
		(H->sibling)->sibling = H;
		return head;
	}
	else {
		return H;
	}
}

Node* BinomialHeap::extractMin(Heap* H) {
	if (H->head == nullptr) {
		cout << "Heap is empty (extractMin operation)" << endl;
		return nullptr;
	}
	Node* x = H->head;
	Node* prev_x = nullptr;

	//finding min
	int min = H->head->key;
	Node* tmp = H->head;
	while (tmp->sibling != nullptr) {
		if (tmp->sibling->key < min) {
			min = tmp->sibling->key;
			prev_x = tmp;
			x = tmp->sibling;
		}
		tmp = tmp->sibling;
	}
	//if single node
	if (prev_x == nullptr && x->sibling == nullptr)
		H->head = nullptr;
	//if has not prev node
	else if (prev_x == nullptr)
		H->head = x->sibling;
	//just remove
	else
		prev_x->sibling = x->sibling;
	Heap* _H = createBinHeap();
	if (x->child != nullptr) {
		_H->head = revertHeap(x->child);
		x->child->sibling = nullptr;
	}
	*(H) = *(unionHeaps(_H, H));
	return x;
}

void BinomialHeap::deleteNode(Heap* H, int k){
	Node* x = findNode(H, k);
	if (x != nullptr) {
		decreaseKey(H, k, INT_MIN);
		extractMin(H);
	}
}

void BinomialHeap::decreaseKey(Heap* H, int old_k, int k) {
	Node* x = findNode(H, old_k);
	if (x == nullptr) {
		cout << "Key doesn't exits" << endl;
		return;
	}
	if (k > x->key) {
		cout << "New key more than current key" << endl;
		return;
	}
	x->key = k;
	Node* y = x;
	Node* z = y->parent;
	while (z != nullptr && y->key < z->key) {
		swap(y->key, z->key);
		y = z;
		z = y->parent;
	}
}

void BinomialHeap::display(Heap* H) {
	Node* head = H->head;
	while (head) {
		cout << head->key << " ";
		Heap* heap = createBinHeap();
		heap->head = head->child;
		display(heap);
		head = head->sibling;
	}
}