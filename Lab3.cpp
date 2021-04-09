#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Node {

	string name;
	int cost;
	bool availability;
	float weight;

    struct Node* next;

};

struct Node* first;

bool pop();
bool pop_all();
bool push_forward(string name, int cost, bool availability, float weight);
bool push_back(string name, int cost, bool availability, float weight);
void print();
void peek();
void fileInsert();
void stackFileCreation();

int main()
{
 
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {
		cout << "\nМеню:\n";
		cout << "1. Посмотреть корзину\n";
		cout << "2. Добавить новый товар в корзину\n";
		cout << "3. Вытащить товар их корзины\n";
		cout << "4. Очистить корзину\n";
		cout << "0. Выход\n";
		cout << "-1. Считать корзину из файла\n";
		cout << "-2. Создание файла корзины\n";

		short int ch;

		cin >> ch;

		switch (ch)
		{

		case 1: {
			print();
			break;
		}

		case 2: {
			string name;
			int cost;
			bool availability;
			float weight;

			cout << "\nВведите имя товара="; cin >> name;
			cout << "\nВведите цену="; cin >> cost;
			cout << "\nВведите наличие товара="; cin >> availability;
			cout << "\nВведите вес товара="; cin >> weight;

			push_forward(name, cost, availability, weight);
			break;
		}

		case 3: {

			break;
		}

		case 4: {

			pop_all();
			break;
		}
		
		case 0: {
			exit = 1;
			break;
		}

		case -1: {
			fileInsert();
			break;
		}

		case -2: {
			stackFileCreation();
			break;
		}


		default:
			cout << "\nПункт меню выбран неправильно, повторите!\n";
			break;
		}

		

	} while (exit != 1);
	


    return 0;
}

void print() {

	struct Node* temp;

	// проверка на пустой стек
	if (first == NULL) {
		cout << "\nКорзина пустая\n" << endl;
	}
	else {
		
		temp = first;

		cout << "\nТекущая корзина: \n";
		while (temp != NULL) {
			// печать данных узла
			cout << "\nНазвание: " << temp->name;
			cout << "\nСтоимость: " << temp->cost << " рублей";
			cout << "\nВес: " << temp->weight << " кг";
			cout << "\nВ наличии? " << (temp->availability == true ? "Да" : "Нет");
			cout << endl;

			// переходим к следующему узлу стека
			temp = temp->next;
		}
		
	}

};

bool pop() {

	struct Node* temp;

	// проверка на пустой стек
	if (first == NULL) {
		return 0;
	}
	else {
		// верхнее значение помещаем в temp
		temp = first; 

		// в вершину стека кладем следующий узел сверху
		first = first->next; 

		// разрушаем связь для удаляемого узла
		temp->next = NULL;

		cout << "\nТовар " << temp->name << " удален" << endl;

		// освобождаем память верхнего узла
		free(temp);
	}


    return 1;
};

bool pop_all() {

	if (first != NULL) {
		while (pop() != 0);
		cout << "\nКорзина очищена!\n";
	}
	else {
		cout << "\nКорзина пуста!\n";
	}
	return 1;
};

void peek() {
	
	// проверка на пустой стек
	if (first == NULL) cout << "\nСтэк пустой" << endl;
	//Если не пустой
	else { 
		cout << "\nВерх корзины:";
		cout << "\nНазвание: " << first->name;
		cout << "\nСтоимость: " << first->cost << " рублей";
		cout << "\nВес: " << first->weight << " кг";
		cout << "\nВ наличии? " << (first->availability == 1 ? "Да" : "Нет");
	}
	
}

bool push_forward(string name, int cost, bool availability, float weight) {

    struct Node* temp;
    
    temp = new Node();
	// Запись данных
    temp->name = name;
	temp->cost = cost;
	temp->availability = availability;
	temp->weight = weight;


	// Делаем верхним этот узел
    temp->next = first;//Тот, что был верхним, окажется под ним
    first = temp;

	cout << "\nМяч " << name << " стоимостью " << cost << " записан\n";

    return 1;
};

bool push_back(string name, int cost, bool availability, float weight) {

	struct Node* temp;

	temp = new Node();

	temp = first;

	//Перемещаемся в конец
	while (temp->next != NULL) {
		temp = temp->next;
	}

	//Создаем "последний" узел заново
	struct Node* last;

	last = new Node();

	//Восстанавливаем связь
	temp->next = last;

	//Присваиваем последнему узлу данные
	
	temp->next->name = name;
	temp->next->cost = cost;
	temp->next->availability = availability;
	temp->next->weight = weight;

	cout << "\nМяч " << name << " стоимостью " << cost << " записан в конец\n";
	
	return 1;
};

void fileInsert() {
	
	ifstream fin("Stack File.txt");

	string name;
	int cost;
	bool availability;
	float weight;

	while (getline(fin,name) && fin >> cost >> availability >> weight) {
		push_forward(name, cost, availability, weight);
	}

	fin.close();
}

void stackFileCreation() {

	bool exit = 0;

	ofstream fout("Stack File.txt", ios::ate);

	do {
		unsigned short int ch;
		cout << "\n1. Внести новый элемент\n";
		cout << "\n0. Выход\n";
		cin >> ch;

		if (ch == 0) exit = 1;
		if (ch == 1) {

			string name;
			int cost;
			bool availability;
			float weight;

			cout << "\nВведите поле name="; getline(cin, name);
			cout << "\nВведите поле cost="; cin >> cost;
			cout << "\nВведите поле availability="; cin >> availability;
			cout << "\nВведите поле weight="; cin >> weight;

			fout << name << " " << cost << " " << availability << " " << weight << endl;

		}


	} while (exit != 1);

}