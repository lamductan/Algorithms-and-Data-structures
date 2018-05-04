#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct Node* Ref;
struct Node
{
	int key;
	Ref left;
	Ref right;
};
int increase(int x, int y)
{
	return (x < y);
}
Ref GetNode(int k)
{
	Ref x = new Node;
	x->key = k;
	x->left = x->right = NULL;
	return x;
}
void Add(Ref &r, int k)
{
	if (r == NULL)
		r = GetNode(k);
	else
	{
		if (r->key < k) Add(r->right, k);
		else
		{ 
			if (r->key > k) Add(r->left, k);
			else
			{
				cout << "Value exist" << endl;
				return;
			}
		}
	}
}
void PreOrder(Ref root)
{
	if (root != NULL)
	{
		cout << root->key << " ";
		PreOrder(root->left);
		PreOrder(root->right);

	}
}
void PostOrder(Ref root)
{ 
	if (root)
	{
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->key << " ";
	}
}
void MorrisInOrder(Ref root)
{
	Ref p = root;
	while (p)
	{
		if (p->left == NULL)
		{
			cout << p->key << " ";
			p = p->right;
		}
		else
		{
			Ref tmp = p->left;
			while (tmp->right != NULL && tmp->right != p) tmp = tmp->right;
			if (tmp->right == NULL)
			{
				tmp->right = p;
				p = p->left;
			}
			else
			{
				cout << p->key << " ";
				tmp->right = NULL;
				p = p->right;
			}
		}
	}
}
void MorrisPreOrder(Ref root)
{
	Ref p = root;
	while (p)
	{
		if (p->left == NULL)
		{
			cout << p->key << " ";
			p = p->right;
		}
		else
		{
			Ref tmp = p->left;
			while (tmp->right != NULL && tmp->right != p) tmp = tmp->right;
			if (tmp->right == NULL)
			{
				cout << p->key << " ";
				tmp->right = p;
				p = p->left;
			}
			else
			{
				tmp->right = NULL;
				p = p->right;
			}
		}
	}
}
void Reverse(Ref &from, Ref &to)
{
	if (from == to) return;
	Ref x = from, y = from->right, z;
	while (true)
	{
		z = y->right;
		y->right = x;
		x = y;
		y = z;
		if (x == to) break;
	}
}
void MorrisPostOrder(Ref root)
{
	Ref dummy = new Node;
	dummy->left = root;
	dummy->right = NULL;
	Ref p = dummy, tmp;
	while (p)
	{
		if (p->left == NULL) p = p->right;
		else
		{
			tmp = p->left;
			while (tmp->right != NULL && tmp->right != p) tmp = tmp->right;
			if (tmp->right == NULL)
			{
				tmp->right = p;
				p = p->left;
			}
			else
			{
				Reverse(p->left, tmp);
				Ref t = tmp;
				while (t != p->left)
				{
					cout << t->key << " ";
					t = t->right;
				}
				cout << t->key << " ";
				Reverse(tmp, p->left);
				tmp->right = NULL;
				p = p->right;
			}
		}
	}
}
void BuildCNPCBHT(Ref& root, int*a, int l, int r)
{
	int mid = (l + r )/ 2;
	if (l < r)
	{
		int x = a[mid];
		Add(root, x);
		BuildCNPCBHT(root, a, l, mid);
		BuildCNPCBHT(root, a, mid + 1, r);
	}
}
void main()
{ 
	int a1[] = { 20, 92, 23, 72, 6, 57, 40, 21, 31, 99 };
	int a[] = { 6, 20, 21, 23, 31, 40, 57, 72, 92, 99 };
	int b[] = { 5,2, 7, 6, 9 };
	int n = 5;
	Ref root = NULL;
	for (int i = 0; i < n; i++)
	{
		Add(root, b[i]);
	}
	//PostOrder(root);
	//cout << endl;
	//MorrisPostOrder(root);
	root = NULL;
	BuildCNPCBHT(root, a, 0, 9);
	PreOrder(root);
	PostOrder(root);
}