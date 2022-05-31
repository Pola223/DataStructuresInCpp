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
	if (root == NULL) return root; //Gdy pusty w�ze�
	else if (index < root->index) root->left = Delete(root->left, index);  //Index mniejszy od tego kt�rego szukam czyli id� do lewego poddrzewa
	else if (index > root->index) root->right = Delete(root->right, index); //Index wi�kszy od tego kt�rego szukam czyli id� do prawego poddrzewa
	// Mam ten index, kt�rego szukam. Mog� si� wzi�� za kasowanie	
	else {
		// W�ze� nie ma dzieci
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		// W�ze� ma tylko jedno dziecko (prawe) 
		else if (root->left == NULL) {
			struct student *temp = root;
			root = root->right;
			delete temp;
		}
		// W�ze� ma tylko jedno dziecko (lewe) 
		else if (root->right == NULL) {
			struct student *temp = root;
			root = root->left;
			delete temp;
		}
		// W�ze� ma dwoje dzieci. Trzeba poszuka� najmniejszego z wi�szych w�z��w i zamieni� danymi, po czym usun�� ten z kt�rego bra�am dane
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

// Funkcja do znalezienia student�w, kt�rzy nie zdali (tzn wi�cej ni� jedna dw�ja) i zapisania ich do listy
void FindFails(student *root) {
	if (root == NULL) return; //Je�li puste drzewo to wracam

	if (root->left)   //Je�li drzewo ma lewe dziecko to tam najpierw szukam tych co nie zdali
		FindFails(root->left); 

	//Tutaj sprawdzam czy student kt�ry jest w tym w�le zda� czy nie zda�
	int fails = 0;
	for (int i = 0; i < 4; i++)
	{
		if (root->grades[i] < 3) //Licz� ile ma dw�j
			fails++; 
	}
	if (fails > 1)  // Je�li student ma wi�cej ni� jedn� dw�j� to nie zda� i musz� go usun��. Czyli dodaj� go do listy do usuni�cia
	{
		failedId* f = new failedId;
		f->id = root->index;
		f->next = NULL;
		if (!head)   //Je�li jeszcze nikogo nie ma na li�cie
			head = f; 
		else   // Dodaj� kolejnego nie zdanego do pocz�tku listy
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

//funkcja pomocnicza - wy�wietla list�. Sprawdza�am ni� czy wszyscy studenci mi si� dodali do listy
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
	cout << "Pokaz drzewo w kolejno�ci in-order " << endl;
	showTree(root);
	cout << "\n";

	// Usuwam studentow
	root = Delete(root, 43);
	root = Delete(root, 12);

	cout << "Pokaz drzewo po usuieciu dwoch studentow po indexie: " << endl;
	showTree(root);

	//Tworzy list� student�w, kt�rzy oblali
	FindFails(root);

	cout << "Lista id studentow ktorzy oblali: " << endl;
	showList(head); // Dla sprawdzenia to tylko
	cout << endl;

	//Usuwam studentow ktorzy oblali po id ktore mia�am zapisane w li�cie
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