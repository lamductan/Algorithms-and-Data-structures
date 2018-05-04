// C++ Implementation for Singly Linked List
// Author: Duc Tan Lam
// Date: 06/21/2017

#include <iostream>
using namespace std;

typedef struct node* ref;

struct node {
    int key;
    ref next;
};

ref getNode(int k) {
    ref p = new node;
    p->key = k;
    p->next = NULL;
    return p;
}

ref addHead(ref& head, int k) {
    ref p = getNode(k);
    p->next = head;
    head = p;
    return p;
}

void delList(ref& head) {
    while (head) {
        ref temp = head;
        head = head->next;
        delete temp;
    }
}

// Insertion Sort for Singly Linked List
void insertionSort(ref& head) {
    ref dummyHead = new node;
    dummyHead->next = head;

    for(ref p = head->next, prev = head; p;) {
        ref q = dummyHead;
        while (q->next != p && q->next->key < p->key)
            q = q->next;

        if (q->next != p) {
            prev->next = p->next;
            p->next = q->next;
            q->next = p;

            p = prev->next;
        }
        else {
            prev = p;
            p = p->next;
        }
    }
    head = dummyHead->next;
    delete dummyHead;
}

// Selection Sort for Singly Linked List
void selectionSort(ref& head) {
    ref dummyHead = new node;
    dummyHead->next = head;

    ref t = new node;
    t->next = NULL;
    ref dummyNewHead = t;
    while (dummyHead->next)
    {
        int minValue = dummyHead->next->key;
        ref prevMinNode = dummyHead, minNode = dummyHead->next;
        for(ref p1 = dummyHead->next, p2 = p1->next; p2; p1 = p1->next, p2 = p2->next)
            if (p2->key < minValue) {
                minValue = p2->key;
                prevMinNode = p1;
                minNode = p2;
            }
        prevMinNode->next = minNode->next;
        t->next = minNode;
        t = minNode;
        t->next = NULL;
    }
    head = dummyNewHead->next;
    delete dummyHead;
    delete dummyNewHead;
}

/* Quick Sort for Singly Linked List */
// Partition: pivot is head
void Partition(ref head, ref& h1, ref& t1, ref& h2, ref& t2, ref& h3, ref& t3) {
    int pivot = head->next->key;

    h1 = new node;
    h2 = new node;
    h3 = new node;
    h1->next = h2->next = h3->next = NULL;
    t1 = h1, t2 = h2, t3 = h3;

    ref temp;
    for(ref p = head->next; p;)
    {
        temp = p->next;
        if (p->key < pivot)
            t1->next = p, t1 = p;
        else if (p->key > pivot)
            t2->next = p, t2 = p;
        else
            t3->next = p, t3 = p;
        p->next = NULL;
        p = temp;
    }
}

void QuickSort(ref& head, ref& tail) {
    if (head->next == NULL || head->next->next == NULL)
        return;

    ref h1, h2, h3, t1, t2, t3;
    Partition(head, h1, t1, h2, t2, h3, t3);

    QuickSort(h1, t1);
    QuickSort(h2, t2);

    if (h2->next) {
        t3->next = h2->next;
        tail = t2;
    }
    else tail = t3;

    if (h1->next) {
        t1->next = h3->next;
        head->next = h1->next;
    }
    else
        head->next = h3->next;

    delete h1;
    delete h2;
    delete h3;
}

void quickSort(ref& head) {
    ref dummyHead = new node;
    dummyHead->next = head;
    ref tail = head;
    while (tail->next)
        tail = tail->next;

    QuickSort(dummyHead, tail);

    head = dummyHead->next;
    delete dummyHead;
}
/* End of Quick Sort for Singly Linked List */

/* Merge Sort for Singly Linked List */
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
}

void mergeList(ref &p1, ref &p2) {
    if (p2->key < p1->key) {
        ref t = p1;
        p1 = p2, p2 = t;
    }
    ref h = p1, q = p1->next, r = p2;
    while (q && r) {
        if (q->key < r->key) {
            h->next = q;
            h = q;
            q = q->next;
        }
        else {
            h->next = r;
            h = r;
            r = r->next;
        }
    }
    while (q) {
        h->next = q;
        h = q;
        q = q->next;
    }
    while (r) {
        h->next = r;
        h = r;
        r = r->next;
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
/* End of Merge Sort for Singly Linked List */


void printList(ref head) {
    cout << "List" << endl;
    ref p = head;
    while (p) {
        cout << p->key << " ";
        p = p->next;
    }
    cout << endl << endl;
}

void printListToFile(ref head) {
    freopen("output.txt", "w", stdout);
    ref p = head;
    while (p) {
        cout << p->key << endl;
        p = p->next;
    }
    fclose(stdout);
}

int main() {
    freopen("input2.txt", "r", stdin);
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

    cout << "Linked List after Merge Sort:" << endl;
    mergeSort(head, n);
    printList(head);
    //printListToFile(head);

    delList(head);
    return 0;
}


