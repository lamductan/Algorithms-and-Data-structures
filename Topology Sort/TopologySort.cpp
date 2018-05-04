#include <bits/stdc++.h>
using namespace std;

typedef struct leader* lref;
typedef struct trailer* tref;

struct leader
{
	int key;
	int count;
	lref next;
	tref trail;
};

struct trailer
{
	lref id;
	tref next;
};

lref addList(lref &head, lref &tail, int w) {
	lref h = head;
	tail->key = w;
	while (h->key != w) h = h->next;
	if (h == tail) {
		tail = new leader;
		h->count = 0;
		h->trail = NULL;
		h->next = tail;
	}
	return h;
}

int main() {
	lref head = new leader;
	lref tail = head;
	int x, y;
	freopen("in.txt", "r", stdin);
	cin >> x;

	lref p, q;
	tref t;
	while (x) {
		cin >> y;
		p = addList(head, tail, x);
		q = addList(head, tail, y);
		t = new trailer;
		t->id = q;
		t->next = p->trail;
		p->trail = t;
		q->count++;
		cin >> x;
	}

	p = head;
	head = NULL;
	while (p != tail) {
		q = p;
		p = p->next;
		if (q->count == 0) {
			q->next = head;
			head = q;
		}
	}

	//Sap xep
	q = head;
	while (q) {
		cout << q->key << endl;
		t = q->trail;
		q = q->next;
		while (t) {
			p = t->id;
			p->count--;
			if (p->count == 0) {
				p->next = q;
				q = p;
			}
			t = t->next;
		}
	}

	return 0;
}