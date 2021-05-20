#pragma once
#include "funcs.h"
using namespace std;

int col_el = 0;

struct Data {
	string name;
	int cost;
	float weight;
	bool adult;
};

struct list {
	struct Data data;

	struct list* next;
	struct list* prev;
};

struct list* first;
struct list* C;
struct list* last;


int getN(int left, int right) {

	float new_n;

	do{
	
		cin >> new_n;
		if (((int)new_n) - new_n != 0 || new_n < left || new_n > right) cout << "\n������� �������� �����! ��������� �������\n";
	} while (((int)new_n) - new_n != 0 || new_n < left || new_n > right);


	return (int)new_n;
}

bool move_next() {

	if (first != NULL && last != NULL && C == NULL) C = first;

	if (first != NULL && last != NULL && C->next != NULL) {
		C = C->next;
		return 0;
	}
	else {
		return 1;
	}
};

bool move_prev() {

	if (first != NULL && last != NULL && C == NULL) C = first;

	if (first != NULL && last != NULL && C->prev != NULL) {
		C = C->prev;
		return 0;
	}
	else {
		return 1;
	}
};

void print() {

	if (first != NULL && last != NULL) {
		
		struct list* temp = first;

		while (temp != NULL){
			cout << "\n���: " << temp->data.name << endl;
			cout << "���������: " << temp->data.cost << endl;
			cout << "���: " << temp->data.weight << endl;
			cout << "�������:" << (temp->data.adult == 1 ? "��������" : "���������") << endl;
			temp = temp->next;
		}

	}
	else {
		cout << "\n������ ����!\n";
	}
}

bool push_next(struct Data new_data) {

	if (first != NULL && last != NULL) {
		//���� � ��� �� ������ ������� �������
		if (C == NULL) {
			C = first;
		}

		//������ ��� ���������, ���� ��� ����� ����, ������ ��� ���� ����� ��������� �����
		list* temp = new list(); //������ ����� ����
		list* temp1 = C->next; //��������� �����

		//���������� ������
		temp->data = new_data;

		if (C == last) last = temp; //� ������, ���� �� ��������� � �����, �� ����� �������� ��������� �� last

		//��������������� ����� � �������
		C->next = temp;
		temp->prev = C;

		//������������ ����� �� ����������
		move_next();

		//��������������� ����� � �������
		C->next = temp1;
		temp->prev = C;

	}
	else {
		struct list* temp = new list();
		temp->data = new_data;
		temp->next = first;
		temp->prev = last;
		first = temp;
		last = temp;
	}
	col_el++;
	return 0;

}

bool push_back(struct Data new_data) {

	if (first != NULL && last != NULL) {

		list* temp = new list(); //������ ����� ����

		//���������� ������
		temp->data = new_data;

		//������ ����� � ���������
		temp->next = NULL;
		last->next = temp;
		temp->prev = last;

		last = temp; //� ������, ���� �� ��������� � �����, �� ����� �������� ��������� �� last
	}
	else {
		struct list* temp = new list();
		temp->data = new_data;
		temp->next = first;
		temp->prev = last;
		first = temp;
		last = temp;
	}
	C = last;
	col_el++;
	return 0;
	
}

bool push_forward(struct Data new_data) {

	if (first != NULL && last != NULL) {

		list* temp = new list(); //������ ����� ����

		//���������� ������
		temp->data = new_data;

		//������ ����� � ������
		temp->prev = NULL;
		temp->next = first;
		first->prev = temp;

		first = temp; //������ ��-� ������
	}
	else {
		struct list* temp = new list();
		temp->data = new_data;
		temp->next = first;
		temp->prev = last;
		first = temp;
		last = temp;
	}
	C = first;
	col_el++;
	return 0;

}

void fileCreate(int choice) {
	
	if (first != NULL && last != NULL) {

		if (choice == 1) {

			ofstream fout("list.txt", ios::trunc);

			struct list* temp = first;

			while (temp != NULL) {
				fout << temp->data.name << " ";
				fout << temp->data.cost << " ";
				fout << temp->data.weight << " ";
				fout << temp->data.adult << endl;
				temp = temp->next;
			}

			fout.close();
		}
		else {
			ofstream fout("list.txt", ios::app);

			struct list* temp = first;

			while (temp != NULL) {
				fout << temp->data.name << " ";
				fout << temp->data.cost << " ";
				fout << temp->data.weight << " ";
				fout << temp->data.adult << endl;
				temp = temp->next;
			}

			fout.close();
		}
	}
	else {
		cout << "\n������ ����!\n";
	}

	

}

void readFile() {
	
	ifstream fin("list.txt");

	if (!fin) {
		cout << "\n������! ����� �� ����������!\n";
		return;
	}

	struct Data data;

	while (fin >> data.name >> data.cost >> data.weight >> data.adult) {
		push_back(data);
	}
	C = first;
	fin.close();
	cout << "\n���� ������\n";
}

bool remove() {
	if (first != NULL) {
		cout << "\t��� �������?\n";
		cout << "\t1. � �����\n";
		cout << "\t2. � ������\n";
		cout << "\t3. �� ������� k\n";
		cout << "\t������� ��� ������� ->";

		int choice; cin >> choice;

		if (choice == 1) {
			remove_back();
			cout << "\n������� �����!\n";
		}
		else if (choice == 2) {
			remove_forward();
			cout << "\n������� �����!\n";
		}
		else if (choice == 3) {
			cout << "\t\t������� k �� 1 �� " << col_el << " =";
			int k;
			k = getN(1, col_el);

			if (k == 1) {
				remove_forward();
				return 0;
			}
			if (k == col_el) {
				remove_back();
				return 0;
			}

			if (first != NULL) {
				struct list* temp = C;
				if (C != NULL) temp = C;
				C = first;

				for (int i = 1; i < k - 1; i++) {
					C = C->next;
				}

				//���� �� ������� �������, ������� ��� �������(������ ������(���� �� ������ �����, ���� �� ������, ���� �� ���������,���� �� ������ ���������)
				if (temp == C->next && temp != first) temp = temp->prev;
				if (temp == C->next && temp == first && temp->next != NULL) temp = temp->next;
				if (temp == C->next && temp == last && temp->prev != NULL) temp = temp->prev;
				if (temp == C->next && temp == first && temp == last) temp = NULL;
				
				remove_next();

				cout << "\n������� �����!\n";

				if (temp != NULL) C = temp;

			}


			

		}
		else {
			cout << "\n������!������ �� ������!\n";
			return 1;
		}
	}
	else {
		cout << "\n������!������ ����!\n";
		return 1;
	}

	return 0;

}

void clear() {
	if (first != NULL && last != NULL) {
		while (first != NULL) {
			remove_forward();
		}
		cout << "\n������ ������\n";
	}
	else {
		cout << "\n������ ����!\n";
	}
}

void showC() {

	
	if (first != NULL) {
		if (C == NULL) C = first;

		cout << "\n���: " << C->data.name << endl;
		cout << "���������: " << C->data.cost << endl;
		cout << "���: " << C->data.weight << endl;
		cout << "�������:" << (C->data.adult == 1 ? "��������" : "���������") << endl;
	}
	else {
		cout << "\n������ ����!\n";
	}


}

void remove_next() {

	list* temp = C->next;

	C->next = temp->next;
	temp->next->prev = C;

	temp->next = NULL;
	temp->prev = NULL;

	free(temp);
	col_el--;

}

void remove_forward() {

	
	list* temp = first;

	if (temp == last) {
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
		first = NULL;
		last = NULL;
		return;
	}

	first = first->next;
	first->prev = NULL;
	temp->next = NULL;
	temp->prev = NULL;

	free(temp);
	col_el--;
}

void remove_back() {

	list* temp = last;

	if (temp == first) {
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
		first = NULL;
		last = NULL;
		return;
	}

	last = last->prev;
	last->next = NULL;
	temp->prev = NULL;
	temp->next = NULL;

	free(temp);
	col_el--;
}

void push() {
	struct Data data;
	cout << "\n\t������� ����� ������:\n";
	cout << "\t���: "; cin >> data.name;
	cout << "\t���������: "; cin >> data.cost;
	cout << "\t���: "; cin >> data.weight;
	cout << "\t��������? (������� 1 ���� ��): "; cin >> data.adult;

	cout << "\n\t���� ��������?\n";
	cout << "\t1. � �����\n";
	cout << "\t2. � ������\n";
	cout << "\t3. �� ������� k\n";
	cout << "\t������� ���� �������� ->";

	int choice; cin >> choice;

	if (choice == 1) {
		push_back(data);
	}
	else if (choice == 2) {
		push_forward(data);
	}
	else if (choice == 3) {
		cout << "\t\t������� k �� 1 �� " << col_el+1 << " =";
		int k;
		k = getN(1, col_el + 1);

		if (k == 1) {
			push_forward(data);
			return;
		}

		if (first != NULL) {
			C = first;

			for (int i = 1; i < k-1; i++) {
				C = C->next;
			}

			push_next(data);

		}
		else {
			push_back(data);
		}



	}
	else {
		cout << "\n������, �������� � �����!\n";
		push_back(data);
	}
	
}

void sort() {

	if (first != NULL) {
		cout << "\n�������� ����, �� ������ �����������:\n";
		cout << "\n1. ���\n";
		cout << "\n2. ���������\n";
		cout << "\n������� ����� -> ";
		int choice; cin >> choice;

		switch (choice) {

		case 1: {

			C = first;
			list* temp = first;

			for (int i = 0; i < col_el; i++) {
				for (int j = 0; j < col_el; j++) {
					if (C == temp) continue;
					if(strcmp(temp->data.name.c_str(), C->data.name.c_str()) > 0) {
						swap(temp->data, C->data);
					}
					if(temp->next != NULL) temp = temp->next;
					
				}
				temp = first;
				C = C->next;
				
			}
			

			C = first;
			break;
		}

		case 2: {
			C = first;
			list* temp = first;

			for (int i = 0; i < col_el; i++) {
				for (int j = 0; j < col_el; j++) {
					if (C == temp) continue;
					if (temp->data.cost > C->data.cost) {
						swap(temp->data, C->data);
					}
					if (temp->next != NULL) temp = temp->next;

				}
				temp = first;
				C = C->next;

			}


			C = first;


			break;
		}

		default: {
			cout << "\n������, ������ ������������ �����!\n";
			break;
		}

		}



	}
	else {
		cout << "\n������ ������!\n";
	}


}

