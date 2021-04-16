#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>


using namespace std;

struct data {

	int groupcode;
	string groupname;
	string name;
	int startprice;
	int quantity;
	int soldprice;
	int solded;

};

struct Node {

	struct data data;

	struct Node* next;

};

struct Node* first;

bool pop();
bool pop_all();
bool push_back(struct data data);
void print();
Node* peek();
void fileInsert();
void sell(struct data data);
void queueFileCreation();
void report();

int total, profit = 0;

int main()
{

	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {
		cout << "\nМеню:\n";
		cout << "1. Поступление товара\n";
		cout << "2. Считать товары из файла\n";
		cout << "3. Продажа товара\n";
		cout << "4. Отчёт\n";
		cout << "5. Просмотреть склад\n";
		cout << "0. Выход\n";
		cout << "-1. Создание файла очереди\n";

		short int ch;

		cin >> ch;

		switch (ch)
		{

		case 1: {
			
			struct data data;

			cout << "Введите код группы:"; cin >> data.groupcode;
			cout << "Введите имя группы:"; cin >> data.groupname;
			cout << "Введите имя:"; cin >> data.name;
			do {
				cout << "Введите закупочную стоимость товара:"; cin >> data.startprice;
				if (data.startprice <= 0) cout << "\nВы ввели неверную закупочную стоимость";
			} while (data.startprice <= 0);
			do {
				cout << "Введите количество товара:"; cin >> data.quantity;
				if (data.quantity <= 0) cout << "\nВы ввели неверное количество товара";
			} while (data.quantity <= 0);
			do {
				cout << "Введите цену продажи товара:"; cin >> data.soldprice;
				if (data.startprice >= data.soldprice) cout << "\nВы ввели неверную цену продажи";
			} while (data.startprice >= data.soldprice);

			push_back(data);


			break;
		}

		case 2: {
			fileInsert();
			break;
		}

		case 3: {
			struct data data;
			cout << "\nВведите что продавать:\n";
			cout << "Введите код группы:"; cin >> data.groupcode;
			cout << "Введите имя:"; cin >> data.name;
			do {
				cout << "Введите количество товара:"; cin >> data.quantity;
				if (data.quantity <= 0) cout << "\nВы ввели неверное количество товара";
			} while (data.quantity <= 0);

			sell(data);

			break;
		}
	
		case 4: {

			report();

			break;
		}

		case 5: {

			print();
			break;
		}

		case 0: {
			exit = 1;
			break;
		}

		case -1: {
			queueFileCreation();
			break;
		}


		default:
			cout << "\nПункт меню выбран неправильно, повторите!\n";
			break;
		}



	} while (exit != 1);



	pop_all();

	return 0;
}

void print() {

	struct Node* temp;

	// проверка на пустой стек
	if (first == NULL) {
		cout << "\nОчередь пуста!\n" << endl;
	}
	else {

		temp = first;

		cout << "\nТекущая очередь: \n";
		while (temp != NULL) {
			// печать данных узла
			cout << "\nГруппа: " << temp->data.groupcode;
			cout << "\nНазвание группы: " << temp->data.groupname;
			cout << "\nНазвание: " << temp->data.name;
			cout << "\nЗакупочная стоимость: " << temp->data.startprice << " рублей";
			cout << "\nРозничная стоимость: " << temp->data.soldprice << " рублей";
			cout << "\nШтук в наличии: " << temp->data.quantity;
			cout << endl;

			// переходим к следующему узлу очередт
			temp = temp->next;
		}

	}

};

void report() {

	int quantity_all = 0, net_worth = 0;

	struct Node* temp = first;

	while (temp != NULL) {
		quantity_all += temp->data.quantity;
		net_worth += temp->data.startprice * temp->data.quantity;
		temp = temp->next;
	}

	cout << "\nОбщее количество товара на складе: " << quantity_all;
	cout << "\nОбщая стоимость товаров на складе: " << net_worth << " рублей";
	cout << "\nОборот склада(до вычета себестоимости): " << total << " рублей";
	cout << "\nПрибыль склада: " << profit << " рублей";




}

bool pop() {

	struct Node* temp;

	if (first == NULL) {
		return 0;
	}
	else {
		temp = first;

		first = first->next;

		temp->next = NULL;

		free(temp);
	}


	return 1;
};

void sell(struct data data) {

	if (first != NULL) {
		
		struct Node* temp = first;
		struct Node* temp1 = first;


		bool once_sell = 0, first_execute = 0;
		do{
			
			if (temp->data.groupcode == data.groupcode && temp->data.name == data.name) {
				if (temp->data.quantity >= data.quantity) {
					temp->data.quantity -= data.quantity;
					total += data.quantity * temp->data.soldprice;
					profit += temp->data.quantity * ( temp->data.soldprice - temp->data.startprice);
				}
				else {
					cout << "\nНедостаточно товара на складе\n";
					cout << "\nПродать остаток?\n";
					cout << "\nВведите 1 если да, любое друго число если нет";
					unsigned short int ch;
					cin >> ch;

					if (ch == 1) {
						
						
						total += temp->data.quantity * temp->data.soldprice;
						profit += temp->data.quantity * (temp->data.soldprice - temp->data.startprice);
						temp->data.quantity = 0;
						cout << "\nОстатки товара" << data.name << " проданы\n";
					}

				}

				once_sell = 1;

				if (temp->data.quantity == 0) {
					if (temp == first) {
						temp = temp->next;
						temp1 = temp1->next;
						pop();
					}
					else {
						
						temp1->next = temp->next;
						free(temp);
						temp = temp1->next;
						
					}



				}

			}
			
			if (first_execute == 1 && temp1 != NULL) {
				temp1 = temp1->next;
			}
			first_execute = 1;
			if(temp != NULL)temp = temp->next;
			

			

		} while (temp != NULL);


		if (once_sell == 1) {
			cout << "\nТовар " << data.name << " продан в количестве " << data.quantity << "\n";
		}
		else {
			cout << "\nТакого товара на складе нет\n";
		}

	}
	else {

		cout << "\nОчередь пуста\n";

	}

}

bool pop_all() {

	if (first != NULL) {
		while (pop() != 0);
		cout << "\nОчередь очищена!\n";
	}
	else {
		cout << "\nОчередь пуста!\n";
	}
	return 1;
};

Node* peek() {

	// проверка на пустой стек
	if (first == NULL) cout << "\nСтэк пустой" << endl;
	//Если не пустой
	else {
		return first;
	}

}

bool push_back(struct data data) {

	struct Node* temp;

	temp = first;

	bool exist = 0;

	//Перемещаемся в конец
	if (first != NULL) {
		do{
			if (temp->data.groupcode == data.groupcode && temp->data.name == data.name) {
				exist = 1;
				break;
			}
			else temp = temp->next;
		} while (temp != NULL);


		if (exist == 0) {
			temp = first;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			//Создаем "последний" узел заново
			struct Node* last;
			last = new Node();

			//Восстанавливаем связь

			temp->next = last;
			//Присваиваем последнему узлу данные

			temp->next->data.groupcode = data.groupcode;
			temp->next->data.groupname = data.groupname;
			temp->next->data.name = data.name;
			temp->next->data.startprice = data.startprice;
			temp->next->data.quantity = data.quantity;
			temp->next->data.soldprice = data.soldprice;

			cout << "\nТовар " << data.name << " оптовой стоимостью " << data.startprice << " записан в количестве " << data.quantity << " \n";
		}
		else {
			temp->data.quantity += data.quantity;
			cout << "\nКоличество товара " << data.name << " пополнено " << data.quantity << " штуками\n";
		}

	}
	else {
		struct Node* temp;

		temp = new Node();

		temp->data.groupcode = data.groupcode;
		temp->data.groupname = data.groupname;
		temp->data.name = data.name;
		temp->data.startprice = data.startprice;
		temp->data.quantity = data.quantity;
		temp->data.soldprice = data.soldprice;

		temp->next = first;
		first = temp;
		cout << "\nТовар " << data.name << " оптовой стоимостью " << data.startprice << " записан в количестве " << data.quantity << " \n";
	}

	return 1;
};

void fileInsert() {

	ifstream fin("Stack File.txt");

	struct data data;

	while (fin >> data.groupcode >> data.groupname >> data.name >> data.startprice >> data.quantity >> data.soldprice) {
		push_back(data);
	}

	fin.close();
}

void queueFileCreation() {

	bool exit = 0;

	ofstream fout("Stack File.txt", ios::ate);

	do {
		unsigned short int ch;
		cout << "\n1. Внести новый элемент\n";
		cout << "\n0. Выход\n";
		cin >> ch;

		if (ch == 0) exit = 1;
		if (ch == 1) {

			struct data data;

			cout << "Введите код группы:"; cin >> data.groupcode;
			cout << "Введите имя группы:"; cin >> data.groupname;
			cout << "Введите имя:"; cin >> data.name;
			do {
				cout << "Введите закупочную стоимость товара:"; cin >> data.startprice;
				if (data.startprice <= 0) cout << "\nВы ввели неверную закупочную стоимость";
			} while (data.startprice <= 0);
			do {
				cout << "Введите количество товара:"; cin >> data.quantity;
				if (data.quantity <= 0) cout << "\nВы ввели неверное количество товара";
			} while (data.quantity <= 0);
			do {
				cout << "Введите цену продажи товара:"; cin >> data.soldprice;
				if (data.startprice >= data.soldprice) cout << "\nВы ввели неверную цену продажи";
			} while (data.startprice >= data.soldprice);

			fout << data.groupcode << " " << data.groupname << " " << data.name << " " << data.startprice << " " << data.quantity << " " << data.soldprice << endl;

		}


	} while (exit != 1);

	fout.close();

}
