#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct node
{
	string key;
	node* next;
};
node* getNode(string k)
{
	node* x = new node;
	x->key = k;
	x->next = NULL;
	return x;
}
node * CreatePeopleCircle(int n)
{
	int Num_of_people=n;
	vector<string> people;
	people.resize(Num_of_people);
	cout << "Give the names of soldiers:" << endl;
	for (int i = 0; i < Num_of_people; i++)
	{
		string tmp;
		cin >> tmp;
		people[i] =tmp;
	}
	node * p_head = NULL;
	node * p;
	for (int i = 0; i < Num_of_people; i++)
	{
		node * tmp = getNode(people[i]);
		if (p_head == NULL)
		{
			p_head = tmp;
			p = tmp;
		}
		else
		{
			p->next = tmp;
			tmp->next = p_head;
			p = tmp;
		}
	}
	return p_head;
}
void Display(node* p_head, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << p_head->key << " ";
		p_head = p_head->next;
	}
	cout << endl;
}
void Survive(node * p_head, int n, int skip)
{
	int count = n;
	string x;
	cout << "Input the person you want to start the game:";
	cin >> x;
	node * p = p_head, *start;
	for (; ; p=p->next)
	{
		if (p->key == x)
		{
			start = p;
			break;
		}
	}

	while (count != 1)
	{
		for (int i = 0; i < skip-1; i++)
		{
			start = start->next;
		}
		node * deadPerson = start->next;
		start->next = start->next->next;
		start = start->next;
		cout << "The person has been killed is:"<<deadPerson->key<<endl;
		delete deadPerson;
		count--;
	}
	cout << endl;
	cout << "The survivor is:" << start->key << endl;
}
int main(void)
{
	int n;
	cout << "Give the number of soldiers:";
	cin >> n;
	node* head = CreatePeopleCircle(n);
	Display(head, n);
	int skip;
	cout << "Give the skipped number:";
	cin >> skip;
	Survive(head, n, skip);
}