#include <iostream>
#include <string> 
using namespace std;

struct student {
	int index;
	string name;
	string surname;
	int grades[4];

	struct student *left;
	struct student *right;
};

struct failedId {
	int id;

	struct failedId *next = NULL;
};

failedId* head;


void showTree(student *root) {
	if (root == NULL) return;

	showTree(root->left);      
	cout << "Nr albumu: " << root->index << " imie i nazwisko: " << root->name << " " << root->surname << " oceny:";
	for (int i = 0; i < 4; i++)
	{
		cout << " " << root->grades[i];
	}
	cout << endl;
	showTree(root->right);     
}


student* FindMin(student* root)
{
	while (root->left != NULL) root = root->left;
	return root;
}


struct student* Delete(struct student *root, int index) {
	if (root == NULL) return root; //Gdy pusty wêze³
	else if (index < root->index) root->left = Delete(root->left, index);  //Index mniejszy od tego którego szukam czyli idê do lewego poddrzewa
	else if (index > root->index) root->right = Delete(root->right, index); //Index wiêkszy od tego którego szukam czyli idê do prawego poddrzewa
	// Mam ten index, którego szukam. Mogê siê wzi¹æ za kasowanie	
	else {
		// Wêze³ nie ma dzieci
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		// Wêze³ ma tylko jedno dziecko (prawe) 
		else if (root->left == NULL) {
			struct student *temp = root;
			root = root->right;
			delete temp;
		}
		// Wêze³ ma tylko jedno dziecko (lewe) 
		else if (root->right == NULL) {
			struct student *temp = root;
			root = root->left;
			delete temp;
		}
		// Wêze³ ma dwoje dzieci. Trzeba poszukaæ najmniejszego z wiêszych wêz³ów i zamieniæ danymi, po czym usun¹æ ten z którego bra³am dane
		else {
			struct student *temp = FindMin(root->right);
			root->index = temp->index;
			root->name = temp->name;
			root->surname = temp->surname;
			for (int i = 0; i < 4; i++)
			{
				root->grades[i] = temp->grades[i];
			}
			root->right = Delete(root->right, temp->index);
		}
	}
	return root;
}

// Funkcja do znalezienia studentów, którzy nie zdali (tzn wiêcej ni¿ jedna dwója) i zapisania ich do listy
void FindFails(student *root) {
	if (root == NULL) return; //Jeœli puste drzewo to wracam

	if (root->left)   //Jeœli drzewo ma lewe dziecko to tam najpierw szukam tych co nie zdali
		FindFails(root->left); 

	//Tutaj sprawdzam czy student który jest w tym wêŸle zda³ czy nie zda³
	int fails = 0;
	for (int i = 0; i < 4; i++)
	{
		if (root->grades[i] < 3) //Liczê ile ma dwój
			fails++; 
	}
	if (fails > 1)  // Jeœli student ma wiêcej ni¿ jedn¹ dwójê to nie zda³ i muszê go usun¹æ. Czyli dodajê go do listy do usuniêcia
	{
		failedId* f = new failedId;
		f->id = root->index;
		f->next = NULL;
		if (!head)   //Jeœli jeszcze nikogo nie ma na liœcie
			head = f; 
		else   // Dodajê kolejnego nie zdanego do pocz¹tku listy
		{
			f->next = head;
			head = f;
		}
	}

	if (root->right)   //Szukam nie zdanych w prawym poddrzewie
		FindFails(root->right);

}


student* Insert(student *root, char index, string name, string surname, int grades[4]) {
	if (root == NULL) {
		root = new student();
		root->index = index;
		root->name = name;
		root->surname = surname;
		for (int i =0; i<4; i++)
			root->grades[i] = grades[i];
		
		root->left = root->right = NULL;
	}
	else if (index <= root->index)
		root->left = Insert(root->left, index, name, surname, grades);
	else
		root->right = Insert(root->right, index, name, surname, grades);
	return root;
}

//funkcja pomocnicza - wyœwietla listê. Sprawdza³am ni¹ czy wszyscy studenci mi siê dodali do listy
void showList(failedId* head)
{
	failedId* tmp = head;
	while (tmp->next)
	{
		cout << " " << tmp->id;
		tmp = tmp->next;
	}
	cout << " " << tmp->id;
}

int main() {
	student* root = NULL;
	int zal[4] = { 5, 5, 5, 5 };
	int nzal[4] = { 2, 2, 3, 3 };
	root = Insert(root, 40, "Jakub", "ABC", zal);
	root = Insert(root, 29, "Wojtek", "ABC", nzal);
	root = Insert(root, 35, "Sylwia", "ABC", nzal);
	root = Insert(root, 45, "Paulina", "ABC", zal);
	root = Insert(root, 30, "Dawid", "ABC", zal);
	root = Insert(root, 43, "Dawid", "ABC", zal);
	root = Insert(root, 12, "Michal", "ABC", nzal);
	root = Insert(root, 56, "Olaf", "ABC", nzal);

	//Wyslwielam drzewo
	cout << "Pokaz drzewo w kolejnoœci in-order " << endl;
	showTree(root);
	cout << "\n";

	// Usuwam studentow
	root = Delete(root, 43);
	root = Delete(root, 12);

	cout << "Pokaz drzewo po usuieciu dwoch studentow po indexie: " << endl;
	showTree(root);

	//Tworzy listê studentów, którzy oblali
	FindFails(root);

	cout << "Lista id studentow ktorzy oblali: " << endl;
	showList(head); // Dla sprawdzenia to tylko
	cout << endl;

	//Usuwam studentow ktorzy oblali po id ktore mia³am zapisane w liœcie
	failedId* ptr = head;
	while (ptr->next)
	{
		root = Delete(root, ptr->id);
		ptr = ptr->next;
	}
	root = Delete(root, ptr->id);
	
	cout << endl << "showTree after deleting failed students: " << endl;
	showTree(root);

	system("pause");
	return 0;
}