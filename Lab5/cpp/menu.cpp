#include <iostream>
#include <cstdlib>
#include "funcs.h"

using namespace std;

void menu() {
	
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {

		cout << "\n������� � ���������� ��������� �����:\n\n";
		cout << "0. ���������� ������\n";
		cout << "1. �������� �������\n";
		cout << "2. ������� �������\n";
		cout << "3. ������� �������\n";
		cout << "4. ����������� ��������\n";
		cout << "5. �������� ������\n";
		cout << "6. ��������� � ����\n";
		cout << "7. ��������� �� �����\n";
		cout << "-1. �����\n";
		cout << "������� �����-> ";

		int choice;

		cin >> choice;

		switch (choice) {

		case 0: {
			print();
			break;
		}

		case 1 : {

			push();

			cout << "\n������� ��������!\n";
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
			cout << "\n������� 1, ���� ������ ������������ ����(���� ���, �� ������� 0)->"; int choice; cin >> choice;
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
			cout << "\n������ �������� �����! ���������!\n";
			break;
		}

		}



	} while (exit != 1);

	clear();
}