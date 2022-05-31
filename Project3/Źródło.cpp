//Ca³oœæ kodu
#include <iostream>
#include <string>
using namespace std;


struct node
{
	int data;
	node* next;
};

node* head;

void addFront(node*& head, int d)
{
	node* n = new node;
	n->data = d;
	n->next = head;
	head = n;
}

void showList(node* head)
{
	node* pom = head;
	while (pom->next)
	{
		cout << pom->data << " -> ";
		pom = pom->next;
	}
	cout << pom->data << " -> " << pom->next << endl << endl;
}

void addPosition(node*& head, int d, int pos)
{
	if (pos < 1) {
		cout << "Invalid index. Try 1, 2, 3 ..." << endl;
	} 
	else if (pos == 1) 
	{
		addFront(head, d);
		return;
	}
	else {
		node* n = new node;
		n->data = d;

		node* pom;
		pom = head;

		int i = 1;
		while (i < pos - 1) {
			if ((pom->next) == nullptr) {
				if ((pos - (i - 1)) > 0)
				{
					cout << "Index out of bounds. Try " << i + 1 << " or less." << endl;
					return;
				}

			}
			pom = pom->next;
			i++;
		}

		n->next = pom->next;
		pom->next = n;
	}
	return;
}

void addBack(node*& head, int d)
{
	node* n = new node;
	n->data = d;
	n->next = NULL;

	if (!head)
	{
		head = n;
		return;
	};

	node* pom = head;

	while (pom->next)
	{
		pom = pom->next;
	};

	pom->next = n;
	return;
}

void deleteFront(node*& head)
{
	node* pom;

	if (head)
	{
		pom = head;
		head = head->next;
		delete pom;
	}
}

void deleteBack(node*& head)
{
	node* pom;
	pom = head;
	while (pom->next->next)
		pom = pom->next;
	delete pom->next;

	pom->next = NULL;
	return;
}

void deleteMiddle(node*& head, int nrEl)
{
	if (nrEl < 1)
	{
		cout << "There's no such a node. Try 1, 2, 3 ..." << endl;
	}
	else if (nrEl == 1)
	{
		deleteFront(head);
	}
	else
	{
		nrEl = nrEl - 1;
		int i = 1;
		node* pom;
		pom = head;
		while (i < nrEl)
		{	
			if ((pom->next->next) == nullptr)
			{
				if ((nrEl - (i-1)) > 0)
				{
					cout << "Index out of bounds. Try " << i+1 << " or less. I didn't delete any node. Linked list remains unchanged." << endl;
				}
				return;
			}
				
			pom = pom->next;
			i++;
		}
		/* // niepotrzebnie drugi raz sprawdzanie nullptr
		if (!(pom->next == nullptr)) {
			node* tmp = pom->next->next;
			delete pom->next;

			pom->next = tmp;
		}*/

		node* tmp = pom->next->next;
		delete pom->next;

		pom->next = tmp;
		
	}
	return;
}

/*
Zadanie dodatkowe podzieliæ listê na pó³ i wyœwietliæ dwie listy
na pó³ po prostu pierwsze 5 el i drugie 5 el
albo co drugi element
Zadanie napisaæ szukanie w liœcie jakiegoœ elementu po wartoœci
*/


int main1()
{
	std::cout << "Hello World!\n";

	addFront(head, 2);
	addFront(head, 3);
	addFront(head, 4);
	addFront(head, 5);
	addFront(head, 6);
	addBack(head, 10);
	addBack(head, 11);
	addBack(head, 12);
	addBack(head, 13);
	addBack(head, 14);

	showList(head);

	deleteFront(head);
	showList(head);

	deleteFront(head);
	showList(head);

	deleteBack(head);
	showList(head);

	deleteBack(head);
	showList(head);

	cout << "Delete middle" << endl;
	deleteMiddle(head, 7);
	showList(head);

	cout << "Add position" << endl;
	addPosition(head, 99, 8);
	showList(head);

	system("pause");
	return 0;
}