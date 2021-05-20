#include <iostream>
#include <cstdlib>
#include "funcs.h"

using namespace std;

void menu() {
	
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {

		cout << "\nВведите с клавиатуры выбранный пункт:\n\n";
		cout << "0. Напечатать список\n";
		cout << "1. Добавить элемент\n";
		cout << "2. Удалить элемент\n";
		cout << "3. Текущий элемент\n";
		cout << "4. Упорядочить элементы\n";
		cout << "5. Очистить список\n";
		cout << "6. Выгрузить в файл\n";
		cout << "7. Загрузить из файла\n";
		cout << "-1. Выход\n";
		cout << "Введите число-> ";

		int choice;

		cin >> choice;

		switch (choice) {

		case 0: {
			print();
			break;
		}

		case 1 : {

			push();

			cout << "\nЭлемент добавлен!\n";
			print();

			break;
		}

		case 2: {
			if (remove() != 1) {
				print();
			}
			break;
		}

		case 3: {
			showC();
			break;
		}

		case 4: {
			sort();
			break;
		}

		case 5: {
			clear();
			break;
		}

		case 6: {
			cout << "\nВведите 1, если хотите перезаписать файл(если нет, то введите 0)->"; int choice; cin >> choice;
			fileCreate(choice);
			break;
		}
		
		case 7: {
			readFile();
			print();
			break;
		}

		case -1: {
			exit = 1;
			break;
		}

		default: {
			cout << "\nВыбран неверный пункт! Повторите!\n";
			break;
		}

		}



	} while (exit != 1);

	clear();
}