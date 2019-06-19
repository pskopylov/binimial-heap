#include "pch.h"
#include <iostream>
#include "BinomialHeap.h"

int main()
{
	//BinomialHeap bh;
	//Heap* heap = bh.createBinHeap();
	//bh.insert(heap, 9);
	//bh.insert(heap, 11);
	//Heap* heap1 = bh.createBinHeap();
	//bh.insert(heap1, 14);
	//bh.insert(heap1, 6);
	//Heap* heap2 = bh.unionHeaps(heap, heap1);
	//bh.display(heap2);
	//cout << endl;
	////Node* a = bh.binHeapExtractMin(heap2);
	////cout << a->key << endl;
	////bh.display(heap2);
	//bh.decreaseKey(heap2, 14, 4);
	//bh.display(heap2);
	//cout << endl;
	//bh.insert(heap2, 40);
	//bh.insert(heap2, 1);
	//bh.insert(heap2, 15);
	//bh.display(heap2); 
	//cout << endl;
	//bh.deleteNode(heap2, 9);
	//bh.display(heap2);
	BinomialHeap bh;
	Heap* heap = bh.createBinHeap();
	bh.insert(heap, 10);
	bh.insert(heap, 20);
	bh.insert(heap, 30);
	bh.insert(heap, 40);
	bh.insert(heap, 50);
	bh.extractMin(heap);
	bh.insert(heap, 100);
	bh.display(heap);
	/*cout << endl;
	bh.deleteNode(heap, 10);
	bh.display(heap);*/
}