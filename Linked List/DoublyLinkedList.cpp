// C++ Implementation for Doubly Linked List
// Author: Duc Tan Lam
// Date: 06/21/2017

#include <iostream>
#define left prev
#define right next
using namespace std;

typedef struct node* ref;

struct node {
	int key;
	ref prev;
	ref next;
	int len;
	ref inext;
};

ref getNode(int k) {
	ref p = new node;
	p->key = k;
	p->prev = p->next = NULL;
	return p;
}

ref addHead(ref& head, int k) {
	ref p = getNode(k);
	p->next = head;
	if (head)
		head->prev = p;
	head = p;
	return p;
}

ref findTail(ref head) {
	ref tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	return tail;
}

void swapNode(ref &head, ref &tail, ref &p, ref &q) {
	ref dummyHead = new node;
	ref dummyTail = new node;
	dummyHead->next = head;
	head->prev = dummyHead;
	tail->next = dummyTail;
	dummyTail->prev = tail;

	ref qPrev = q->prev;
	ref qNext = q->next;

	p->prev->next = q;
	p->next->prev = q;
	q->prev = p->prev;
	q->next = p->next;

	qPrev->next = p;
	qNext->prev = p;
	p->prev = qPrev;
	p->next = qNext;

	head = dummyHead->next;
	tail = dummyTail->prev;
	tail->next = NULL;
	head->prev = NULL;
	delete dummyHead;
	delete dummyTail;
}

// Insertion Sort for Doubly Linked List
void insertionSort(ref &head, ref &tail) {
	ref dummyHead = new node;
	ref dummyTail = new node;
	dummyHead->next = head;
	head->prev = dummyHead;
	tail->next = dummyTail;
	dummyTail->prev = tail;

	for (ref p = head->next; p != dummyTail;) {
		ref q = dummyHead;
		while (q->next != p && q->next->key < p->key)
			q = q->next;

		if (q->next != p) {
			ref temp = p->next;
			p->prev->next = p->next;
			p->next->prev = p->prev;

			q->next->prev = p;
			p->next = q->next;
			q->next = p;
			p->prev = q;

			p = temp;
		}
		else
			p = p->next;
	}

	head = dummyHead->next;
	tail = dummyTail->prev;
	tail->next = NULL;
	head->prev = NULL;
	delete dummyHead;
	delete dummyTail;
}

void insertToTail(ref &tail, ref &p) {
    tail->prev->next = p;
    p->prev = tail->prev;
    p->next = tail;
    tail->prev = p;
}

void joinTwoNode(ref &p, ref &q) {
    p->next = q;
    q->prev = p;
}

// Selection Sort for Doubly Linked List
void selectionSort(ref &head, ref &tail) {
    ref dummyHead = new node;
	ref dummyTail = new node;
	dummyHead->next = head;
	head->prev = dummyHead;
	tail->next = dummyTail;
	dummyTail->prev = tail;

	ref dummyNewHead = new node;
	ref dummyNewTail = new node;
	dummyNewHead->next = dummyNewTail;
	dummyNewTail->prev = dummyNewHead;

    while (dummyHead->next != dummyTail)
    {
        int minValue = dummyHead->next->key;
        ref minNode = dummyHead->next;
        for(ref p = dummyHead->next->next; p != dummyTail; p = p->next)
            if (p->key < minValue) {
                minValue = p->key;
                minNode = p;
            }
        joinTwoNode(minNode->prev, minNode->next);

        insertToTail(dummyNewTail, minNode);
    }

	head = dummyNewHead->next;
	tail = dummyNewTail->prev;
	tail->next = NULL;
	head->prev = NULL;
	delete dummyHead;
	delete dummyTail;
}

/* Quick Sort for Doubly Linked List */
// Partition: pivot is head
void Partition(ref head, ref tail, ref& h1, ref& t1, ref& h2, ref& t2, ref& h3, ref& t3) {
    int pivot = head->next->key;

    h1 = new node;
    h2 = new node;
    h3 = new node;
    t1 = new node;
    t2 = new node;
    t3 = new node;

    joinTwoNode(h1, t1);
    joinTwoNode(h2, t2);
    joinTwoNode(h3, t3);

    ref temp;
    for(ref p = head->next; p != tail;)
    {
        temp = p->next;
        if (p->key < pivot)
            insertToTail(t1, p);
        else if (p->key > pivot)
            insertToTail(t2, p);
        else
            insertToTail(t3, p);
        p = temp;
    }
}

void QuickSort(ref& head, ref& tail) {
    if (head->next == tail || head->next->next == tail)
        return;

    ref h1, h2, h3, t1, t2, t3;
    Partition(head, tail, h1, t1, h2, t2, h3, t3);

    QuickSort(h1, t1);
    QuickSort(h2, t2);

    if (h2->next != t2) {
        joinTwoNode(t3->prev, h2->next);
        joinTwoNode(t2->prev, tail);
    }
    else joinTwoNode(t3->prev, tail);

    if (h1->next != t1) {
        joinTwoNode(t1->prev, h3->next);
        joinTwoNode(head, h1->next);
    }
    else
        joinTwoNode(head, h3->next);

    delete h1;
    delete h2;
    delete h3;
    delete t1;
    delete t2;
    delete t3;
}

void quickSort(ref& head, ref &tail) {
    ref dummyHead = new node;
    ref dummyTail = new node;
    joinTwoNode(dummyHead, head);
    joinTwoNode(tail, dummyTail);

    QuickSort(dummyHead, dummyTail);

    head = dummyHead->next;
	tail = dummyTail->prev;
	tail->next = NULL;
	head->prev = NULL;
	delete dummyHead;
	delete dummyTail;
}
/* End of Quick Sort for Doubly Linked List */

/* Merge Sort for Doubly Linked List */
ref nodeAt(ref head, int n) {
    ref p = head;
    while (n-- && p) p = p->next;
    return p;
}

void split(ref &p, ref &p2, int n) {
    int n1 = n/2, n2 = n - n1;
    ref t = nodeAt(p, n1 - 1);
    p2 = t->next;
    t->next = NULL;
    p2->prev = NULL;
}

void mergeList(ref &p1, ref &p2) {
    if (p2->key < p1->key) {
        ref t = p1;
        p1 = p2, p2 = t;
    }
    ref h = p1, q = p1->next, r = p2;
    while (q && r) {
        if (q->key < r->key)
            joinTwoNode(h, q), h = q, q = q->next;
        else
            joinTwoNode(h, r), h = r, r = r->next;
    }
    while (q) {
        joinTwoNode(h, q), h = q, q = q->next;
    }
    while (r) {
        joinTwoNode(h, r), h = r, r = r->next;
    }
    h->next = NULL;
}

void mergeSort(ref &head, int n) {
    if (head == NULL || head->next == NULL)
        return;
    else {
        ref p;
        int n1 = n/2, n2 = n - n1;
        split(head, p, n);
        mergeSort(head, n1);
        mergeSort(p, n2);
        mergeList(head, p);
    }
}
/* End of Merge Sort for Doubly Linked List

/* Create a completely balanced search tree */
ref nodeAt(ref head, ref tail, int n) {
    ref p = head;
    while (n-- && p != tail->next) p = p->next;
    return p;
}

ref makeCBST1(ref head, ref tail, int n) {
    if (n == 0)
        return NULL;
    int n1 = n/2, n2 = n - n1 - 1;
    ref r = nodeAt(head, tail, n1);
    ref hl = nodeAt(head, tail, 0);
    ref tl = nodeAt(head, tail, n1 - 1);
    ref hr = nodeAt(head, tail, n1 + 1);
    ref tr = nodeAt(head, tail, n - 1);
    r->prev = makeCBST1(hl, tl, n1);
    r->next = makeCBST1(hr, tr, n2);
    return r;
}

ref makeCBST(ref head, ref tail, int n) {
    quickSort(head, tail);
    return makeCBST1(head, tail, n);
}

void preorder(ref r) {
    if (r == NULL)
        return;
    cout << r->key << " ";
    preorder(r->prev);
    preorder(r->next);
}

void postorder(ref r) {
    if (r == NULL)
        return;
    postorder(r->prev);
    postorder(r->next);
    cout << r->key << " ";
}

void inorder(ref r) {
    if (r == NULL)
        return;
    inorder(r->prev);
    cout << r->key << " ";
    inorder(r->next);
}

void delList(ref& head) {
	while (head) {
		ref temp = head;
		head = head->next;
		delete temp;
	}
}

void printList(ref head) {
	cout << "List" << endl;
	ref p = head;
	while (p) {
		cout << p->key << " ";
		p = p->next;
	}
	cout << endl << endl;
}

void printList(ref head, ref tail) {
	cout << "List" << endl;
	ref p = head;
	while (p != tail) {
		cout << p->key << " ";
		p = p->next;
	}
	cout << endl << endl;
}

ref findNode(ref head, int k) {
	ref p = head;
	while (p)
		if (p->key == k) return p;
		else p = p->next;
		return NULL;
}

void printListReverse(ref tail) {
	cout << "List (reverse)" << endl;
	ref p = tail;
	while (p) {
		cout << p->key << " ";
		p = p->prev;
	}
	cout << endl << endl;
}


int lis(ref &head, ref &tail) {
    for(ref p = head; p; p = p->next) {
        p->len = 1;
        p->inext = NULL;
    }
    for(ref p = tail->prev; p; p = p->prev) {
        for(ref q = p->next; q; q = q->next) {
            if ((p->key > q->key) && (p->len <= q->len)) {
                p->inext = q;
                p->len = q->len + 1;
            }
        }
    }
    for (ref p = head; p; p = p->next)
        if (p->len > head->len)
            head = p;
    cout << head->len << endl;
    ref p;
    for(p = head; p->inext; p = p->inext)
        cout << p->key << " ";
    cout << p->key;
    tail = p;
    return head->len;
}

int main() {
	freopen("lis.txt", "r", stdin);
	int n, k;
	ref head = NULL;
	cin >> n;
	int m = n;
	while (m--) {
		cin >> k;
		addHead(head, k);
	}
	fclose(stdin);
	printList(head);

	ref tail = findTail(head);
	lis(head, tail);
	cout << endl;

//	cout << "Linked List after Merge Sort:" << endl;
//    mergeSort(head, n);
//    printList(head);

//	ref tail = findTail(head);
//
//	ref root = makeCBST(head, tail, n);
//	preorder(root);
//	cout << endl;
//	inorder(root);
//	cout << endl;
//	postorder(root);
//	cout << endl;

	return 0;
}
