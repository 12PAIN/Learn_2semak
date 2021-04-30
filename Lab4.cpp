#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>


using namespace std;

struct Node {
	//Серия данных
	char* seria;

	//След. узел
	struct Node* next;

};

//Первый узел
struct Node* first;

//Для удобной работы передаем наши данные через структуры
struct Data {

	string name;
	int cost;
	bool availability;
	float weight;

};

//Возвращает сериализованные данные
char* returnSeria(struct Data);

//Десереализует данные и возвращает их
Data unSeria(char*);

//Выстаскивает первый
bool pop(struct Data & data);

//Вытаскивает все
bool pop_all();

//Поставить эл-т списка в конец(реализации очереди)
bool push_back(struct Data);

//Печать
void print();

//Ввод с файла
void fileInsert();

//Функия вытаскивания с корзины
void finding(string index);

//Создание файла с сериализованными данными
void queueFileCreation();

//Очистка файла
void clearFile();



int main()
{
	//Я русский
	setlocale(LC_ALL, "rus");

	//Как кнопка выхода маршрутке
	bool exit = 0;

	//Тут всё просто: повторяещееся меню
	do {
		cout << "\nМеню:\n";
		cout << "1. Посмотреть корзину\n";
		cout << "2. Добавить новый товар в корзину\n";
		cout << "3. Вытащить товар их корзины\n";
		cout << "4. Очистить корзину\n";
		cout << "0. Выход\n";
		cout << "-1. Считать корзину из файла\n";
		cout << "-2. Создание файла корзины\n";
		cout << "-3. Очистка файла\n";

		short int ch;

		cin >> ch;

		switch (ch)
		{

		case 1: {
			print();
			break;
		}

		case 2: {
			struct Data data;

			cout << "\nВведите имя товара="; cin >> data.name;
			cout << "\nВведите цену="; cin >> data.cost;
			cout << "\nВведите наличие товара="; cin >> data.availability;
			cout << "\nВведите вес товара="; cin >> data.weight;

			//Вводим данные и пихаем их
			push_back(data);
			break;
		}

		case 3: {

			cout << "\nВведите что искать:\n";
			string index;

			cin >> index;
			//Тут мы вводим текстом цифру или название товара, если подойдет хоть что-то - удалим

			finding(index);

			break;
		}

		case 4: {
			//Удоли всё
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
			queueFileCreation();
			break;
		}

		case -3: {
			clearFile();
			break;
		}


		default:
			cout << "\nПункт меню выбран неправильно, повторите!\n";
			break;
		}



	} while (exit != 1);


	//Очистка памяти
	pop_all();

	return 0;
}

bool push_back(struct Data data) {

	struct Node* temp;

	temp = first;

	bool exist = 0;

	//Полученные данные сериализуем
	char* new_seria = returnSeria(data);

	if (first != NULL) {

		temp = first;

		//Идём в конец
		while (temp->next != NULL) {
			temp = temp->next;
		}

		//Создаем "последний" узел заново и выделяем память
		struct Node* last;
		last = new Node();

		//Восстанавливаем связь
		temp->next = last;

		//Присваиваем последнему узлу данные
		temp->next->seria = new_seria;



		cout << "\nТовар " << data.name << " стоимостью " << data.cost << " записан!\n";


	}
	else {
		// В случае если мы создаём первый эл-т
		struct Node* temp;
		//Выделение памяти
		temp = new Node();

		temp->seria = new_seria;

		temp->next = NULL;
		first = temp;
		cout << "\nТовар " << data.name << " стоимостью " << data.cost << " записан!\n";

	}
	return 1;
};

bool push_back(char* new_seria) {

	struct Node* temp;

	temp = first;

	bool exist = 0;

	if (first != NULL) {

		temp = first;

		//Идём в конец
		while (temp->next != NULL) {
			temp = temp->next;
		}

		//Создаем "последний" узел заново и выделяем память
		struct Node* last;
		last = new Node();

		//Восстанавливаем связь
		temp->next = last;

		//Присваиваем последнему узлу данные
		temp->next->seria = new_seria;


		cout << "\nТовар записан!\n";


	}
	else {
		// В случае если мы создаём первый эл-т
		struct Node* temp;
		//Выделение памяти
		temp = new Node();

		temp->seria = new_seria;

		temp->next = first;
		first = temp;
		cout << "\nТовар записан!\n";

	}
	return 1;
};

char* returnSeria(struct Data data) {

	//Получаем размер нашей строки
	size_t s = data.name.size();

	//Задание байтных размеров всей серии по отдельным типам
	int n0 = sizeof(size_t);
	int n1 = s;
	int n2 = sizeof(int);
	int n3 = sizeof(bool);
	int n4 = sizeof(float);

	//Общий размер серии
	int n = n0 + n1 + n2 + n3 + n4;

	//Динамическое выделение новой памяти под нашу серию(удаляется потом в pop)
	char* new_seria = new char[n];

	//Преобразование наших данных в битовый вид
	char* d0 = reinterpret_cast<char*>(&s);
	char* d1 = const_cast<char*>(data.name.c_str());
	char* d2 = reinterpret_cast<char*>(&data.cost);
	char* d3 = reinterpret_cast<char*>(&data.availability);
	char* d4 = reinterpret_cast<char*>(&data.weight);

	//Запись серии целиком
	for (int i = 0; i < n0; i++) new_seria[i] = d0[i];
	for (int i = 0; i < n1; i++) new_seria[i + n0] = d1[i];
	for (int i = 0; i < n2; i++) new_seria[i + n0 + n1] = d2[i];
	for (int i = 0; i < n3; i++) new_seria[i + n0 + n1 + n2] = d3[i];
	for (int i = 0; i < n4; i++) new_seria[i + n0 + n1 + n2 + n3] = d4[i];

	//Возврат серии
	return new_seria;
}

Data unSeria(char* seria) {

	//Вычисляем размер полученной серии
	int n0, n1, n2, n3, n4;
	n0 = sizeof(size_t);
	n2 = sizeof(int);
	n3 = sizeof(bool);
	n4 = sizeof(float);

	//Выясняем размер строки
	size_t p = *reinterpret_cast<size_t*>(seria);
	n1 = p;

	struct Data data;
	//Записываем строку
	string temp(seria + n0, p);

	//И переписываем в нашу структуру
	data.name = temp;
	
	//Получаем данные из серии
	data.cost = *reinterpret_cast<int*>(seria + n0 + n1);//<-Это смещение откуда читать данные
	data.availability = *reinterpret_cast<bool*>(seria + n0 + n1 + n2);
	data.weight = *reinterpret_cast<float*>(seria + n0 + n1 + n2 + n3);

	//Возвращаем данные
	return data;

}

void print() {

	struct Node* temp;

	// проверка на пустоту
	if (first == NULL) {
		cout << "\nКорзина пустая\n" << endl;
	}
	else {

		temp = first;

		cout << "\nТекущая корзина: \n";
		while (temp != NULL) {
			// печать данных узла
			Data data;
			data = unSeria(temp->seria);

			cout << "\nНазвание: " << data.name;
			cout << "\nСтоимость: " << data.cost << " рублей";
			cout << "\nВ наличии? " << (data.availability == true ? "Да" : "Нет");
			cout << "\nВес: " << data.weight << " кг" << endl;

			// переходим к следующему узлу стека
			temp = temp->next;
		}

	}

};

bool pop(struct Data & data) {

	struct Node* temp;

	// проверка на пустой стек
	if (first == NULL) {
		return 0;
	}
	else {

		// верхнее значение помещаем в temp
		temp = first;

		//Создаём копию данных
		data = unSeria(temp->seria);

		// в вершину стека кладем следующий узел сверху
		first = first->next;

		// разрушаем связь для удаляемого узла
		temp->next = NULL;

		//Удаляем поле данных
		delete[] temp->seria;

		// освобождаем память верхнего узла
		free(temp);
	}


	return 1;
};

bool pop_all() {
	//Если не пустой, удаляем всё
	struct Data data;
	if (first != NULL) {
		while (pop(data) != 0);// эта фигня вернёт потом 0 когда очередь будет пустая
		cout << "\nКорзина очищена!\n";
	}
	else {
		//А если удалять нечего, ничего не удаляем, логично правда
		cout << "\nКорзина пуста!\n";
	}
	return 1;
};

void fileInsert() {
	//Открываем файл
	ifstream fin("Queue.dat", ios::binary);

	//Создаём переменную под серию, но память не выделяем
	char* new_seria;
	int n;
	while (!fin.eof()) {
		//Тут мы читаем сколько в целом символов в нашей серии
		if (fin.read((char*)&n, sizeof(int))) {
			//Выделяем память
			char* seria = new char[n];

			//Считываем серию
			fin.read(seria, n);

			//Записываем
			push_back(seria);
		}
	}

	//Закрываем файл
	fin.close();
}

void queueFileCreation() {

	//Нужная переменная для выхода
	bool exit = 0;

	//Открываем файл на вывод
	ofstream fout("Queue.dat", ios::app | ios::binary);

	do {
		
		//Меню, да
		unsigned short int ch;
		cout << "\n\n1. Внести новый элемент";
		cout << "\n0. Выход\n\n->";
		cin >> ch;

		if (ch == 0) exit = 1;// Если введём на выход цифру, то всё в шоколаде
		if (ch == 1) {

			Data data;

			//А ты введи и отойди
			cout << "\nВведите поле name="; cin >> data.name;
			cout << "Введите поле cost="; cin >> data.cost;
			cout << "Введите поле availability="; cin >> data.availability;
			cout << "Введите поле weight="; cin >> data.weight;

			//Возвращаем серию
			char* seria = returnSeria(data);

			//Тут часть из десериализации, но это нужно чтобы записать длину одной серии
			int n0, n1, n2, n3, n4, n;
			n0 = sizeof(size_t);
			n2 = sizeof(int);
			n3 = sizeof(bool);
			n4 = sizeof(float);

			//Вычисляем длину строки
			size_t p = *reinterpret_cast<size_t*>(seria);
			n1 = p;

			//Ну и длину этой серии
			n = n0 + n1 + n2 + n3 + n4;

			//Записываем длину
			fout.write((char*)&n, sizeof(int));

			// Записываем серию
			fout.write(seria, n);

			//Ну и память очищаем сразу, тк у нас выделяется память в функции сериализации
			delete[] seria;

		}


	} while (exit != 1);//Выходим, не задерживаем

	fout.close();//Файл закрой, данные не трать

}

void clearFile() {

	fstream file("Queue.dat", ofstream::out | ofstream::trunc);//Открываем файл на вывод, одновременно его очищая

	file.close();//Сразу закрываем. Congrats вы очистили файл


}

void finding(string index) {

	//Тут вообще всё на костылях так сказать, я не знаю как по другому, но оно прекрасно работает
	
	//Тут я запоминаю первый типа, чтобы вечно по кругу не ходить
	char* first_seria;
	bool check = 0;

	//Если не пустой идём убивать
	if (first != NULL) {
		
		

		//Тут нужно чтобы записать в них переделанную строку
		int index_int;
		float index_float;

		//А это для движения по списку
		struct Node* temp;
		int count = 0;
		temp = first;

		while (temp != NULL) {
			temp = temp->next;
			count++;
		}
		
		temp = first;

		//Преобразуем строку в значения 
		index_int = atoi(index.c_str());
		index_float = atof(index.c_str());

		//Вот это 1) для того чтобы записать, вытащили ли мы вообще
		//2) для задания отставания на 1 узел списка
		bool once = 0;

		//Данные данные, грязные C++ данные
		struct Data data;



		for (int i = 0; i < count; i++) {

			data = unSeria(temp->seria); // Десериализуем, получаем данные из узла

			if (index == data.name || index_float == data.weight || index_int == data.cost) { // Ищем совпадения

				//Тут если нашлось то выведет один раз только, а не кучу раз
				if (once == 0) {
					cout << "\nНайденые товары:\n";
					once = 1;
				}

				cout << "\nНазвание: " << data.name;
				cout << "\nСтоимость: " << data.cost << " рублей";
				cout << "\nВес: " << data.weight << " кг";
				cout << "\nВ наличии? " << (data.availability == true ? "Да" : "Нет");
				cout << endl;

				//Удаление из списка
				temp = first->next;
				
				pop(data);
				count--;

				cout << "\nТовар удален из корзины\n"; // Вроде логично

			}
			else {
				// А если не нашлось то ты ИдиИиИиИ вперёд по списку
				if (temp != NULL) {

					struct Data new_data;
					pop(new_data);
					push_back(new_data);

				}

			}

		}

		//Выводим информационный текст(если не было удалено, или если было)
		if (once == 0) {
			cout << "\nТаких товаров не найдено\n";
		}
		else {
			cout << "\nТовары, подходящие по критерию поиска удалены\n";
		}

	}
	else { //А вот это если тебе делать нехер и ты запустил эту функцию при пустом списке

		cout << "\nКорзина пуста\n";

	}

}
