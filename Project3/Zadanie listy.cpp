#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
int counter = 0;

struct president
{
	int ordinal_number = ++counter;
	string name;
	string surname;
	int starting_date;
	int end_date;
	int term_of_office;
	string party;

	president* next;
};

president* head;
president* partyHead;

struct twoTermPresident
{
	string name;
	string surname;
	int starting_date;
	int end_date;

	twoTermPresident* next;
};

twoTermPresident* doubles;

president* newNode(string tab[5], int spaces)
{
	president* p = new president;
	int i = 0;
	if (spaces == 4)
	{
		p->name = tab[i] + ' ' + tab[i + 1];
		i++;
	}
	else if (spaces == 3)
	{
		p->name = tab[i];
	}
	else
	{
		cout << "Something went wrong" << endl;
	}
	p->surname = tab[++i];
	i++;
	p->starting_date = stoi(tab[i].substr(0, 4));
	p->end_date = stoi(tab[i].substr(5, 4));
	p->term_of_office = p->end_date - p->starting_date;
	p->party = tab[++i];
	p->next = nullptr;

	return p;
}

void addNodeBack(president*& head, president* newPres)
{
	if (!head)
	{
		head = newPres;
		return;
	};

	president* tmp = head;

	while (tmp->next)
	{
		tmp = tmp->next;
	};

	tmp->next = newPres;
	return;
}

void showList(president* head)
{
	president* tmp = head;
	while (tmp->next)
	{
		cout << tmp->ordinal_number << " " << tmp->name << " " << tmp->surname << " " << tmp->starting_date << "-" << tmp->end_date << " " << tmp->party << " " << tmp->term_of_office << endl;
		tmp = tmp->next;
	}

	cout << tmp->ordinal_number << " " << tmp->name << " " << tmp->surname << " " << tmp->starting_date << "-" << tmp->end_date << " " << tmp->party << " " << tmp->term_of_office << endl;
}

twoTermPresident* twoTerms(president*& head)
{
	if (!head)
	{
		cout << "List is empty!" << endl;
		return NULL;
	}
	
	president* tmp;
	tmp = head;


	while (tmp->next)
	{
		if (tmp->term_of_office >= 8)
		{
			//tworzê nowy wêze³
			twoTermPresident* p = new twoTermPresident;
			p->name = tmp->name;
			p->surname = tmp->surname;
			p->starting_date = tmp->starting_date;
			p->end_date = tmp->end_date;

			//dodajê nowy wêze³ z przodu listy two terms president
			p->next = doubles;
			doubles = p;

		}
		tmp = tmp->next;
	};

	return doubles;
}

void showTwoTerms(twoTermPresident* doubles)
{
	twoTermPresident* tmp = doubles;
	while (tmp->next)
	{
		cout << tmp->name << " " << tmp->surname << " " << tmp->starting_date << "-" << tmp->end_date << endl;
		tmp = tmp->next;
	}

	cout << tmp->name << " " << tmp->surname << " " << tmp->starting_date << "-" << tmp->end_date << endl;
}

void editPresident(president* head, int president_no)
{
	if (!head)
	{
		cout << "List is empty!" << endl;
	}

	president* tmp;
	tmp = head;
	string s;
	int x;

	while (tmp->next)
	{
		if (tmp->ordinal_number == president_no)
		{
			cout << "Current value as name: " << tmp->name << " ";
			cout << "Please enter new value: ";
			cin >> s;
			tmp->name = s;

			cout << "Current value as surname: " << tmp->surname << " ";
			cout << "Please enter new value: ";
			cin >> s;
			tmp->surname = s;

			cout << "Current value as start of term: " << tmp->starting_date << " ";
			cout << "Please enter new value: ";
			cin >> x;
			tmp->starting_date = x;

			cout << "Current value as end of term: " << tmp->end_date << " ";
			cout << "Please enter new value: ";
			cin >> x;
			tmp->end_date = x;

			tmp->term_of_office = tmp->end_date - tmp->starting_date;

			cout << "Current value as party: " << tmp->party << " ";
			cout << "Please enter new value: ";
			cin >> s;
			tmp->party = s;



			cout << "Changes were made!" << endl;
			cout << "Current record: " << endl;
			cout << tmp->ordinal_number << " " << tmp->name << " " << tmp->surname << " " << tmp->starting_date << "-" << tmp->end_date << " " << tmp->party << " " << tmp->term_of_office << endl;

			break;
		}
		tmp = tmp->next;
	}

}

president* listAccordingToParty(president* head, string party)
{
	if (!head)
	{
		cout << "List is empty!" << endl;
	}

	president* tmp;
	tmp = head;
	counter = 0;

	while (tmp->next)
	{
		if (tmp->party == party)
		{
			president* p = new president;
			p->name = tmp->name;
			p->surname = tmp->surname;
			p->starting_date = tmp->starting_date;
			p->end_date = tmp->end_date;
			p->term_of_office = tmp->term_of_office;
			p->party = tmp->party;

			p->next = NULL;

			if (!partyHead)
			{
				partyHead = p;
			}
			else {
				addNodeBack(partyHead, p);
			}


		}
		tmp = tmp->next;
	}
	if(partyHead)
		showList(partyHead);
	return partyHead;
}


int main2()
{
	fstream newfile;
	/* //Zapisywanie do pliku
	newfile.open("presidents.txt", ios::out); //otwieram plik w trybie zapisywania
	if (newfile.is_open())
	{
		newfile << "Zapisuje do pliku\n";
		newfile.close();
	}
	*/
	//otwieranie pliku w trybie do odczytywania danych
	newfile.open("presidents.txt", ios::in);
	if (newfile.is_open())
	{
		string tp, w;
		istringstream iss;
		int spaces;

		while (getline(newfile, tp))
		{
			string tab[5];
			iss.clear();
			iss.str(tp);
			spaces = count(tp.begin(), tp.end(), ' ');
			
			for (int i =0; i<=spaces; i++)
			{
				iss >> w;
				tab[i] = w;
			}
			
			addNodeBack(head, newNode(tab, spaces));

		}
		newfile.close();
	}

	showList(head);

	cout << endl << endl;
	cout << "Two terms presidents: " << endl;
	twoTerms(head);
	showTwoTerms(doubles);

	cout << endl << endl;
	editPresident(head, 2);

	cout << endl << endl;
	cout << "Showing edited list: " << endl;
	showList(head);

	cout << endl << endl;
	cout << "Showing list according to party: " << endl;
	listAccordingToParty(head, "Republican");
	showList(partyHead);

	cout << endl << endl;
	system("pause");
	return 0;
}