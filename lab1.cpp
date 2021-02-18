#include <iostream>
#include <math.h>
#include <malloc.h>
#include <fstream>

using namespace std;

void inserting(int*, int , int& );
void adding(int*& , int , int&, int);
void rem_mem_plus(int*& , int& , int& );
void rem_mem_minus(int*& , int& , int& , int );
void deleting(int*&, int& , int& , int );
void clearing(int*& , int& , int& );
void printing(int* , int , int&);
void cut(int* , int & , int& , int , int );
void case_7(int*&, int&, int&, int);
void case_8(int*&, int&, int&, int);
int getN(int left, int right) {

    float n;

    do {
        cout << "Insert int number from "<<left<<" to "<< right<< ":";
        cin >> n;
    } while (n < left && (n - (int)n)!=0 && n > right);

    return n;
}

int main()
{
    int n = 3;

    int* arr = (int*)malloc(n * sizeof(int));

    bool exit = 0;
    int k;

    do{

        int choice;

        cout << "MENU:\n";
        cout << "1.Insert\n";
        cout << "2.Print\n";
        cout << "3.Add\n";
        cout << "4.Delete\n";
        cout << "5.Clear\n";
        cout << "6.Cut\n";
        cout << "7.Case 7 in lab\n";
        cout << "8.Case 8 in lab\n";
        cout << "9.Exit\n";
        cout << "->";

        cin >> choice;

        cout << endl;

        switch (choice) {

        case 1: {

            clearing(arr, n, k);

            ifstream fin("input.txt");

            fin >> k;

            fin.close();

            while (k >= n) {
                rem_mem_plus(arr, n, k);
            }

            inserting(arr, n, k);
            cout << endl;
            break;
        }

        case 2: {
            printing(arr, n, k);
            cout << endl;
            break;
        }

        case 3: {

            while (k >= n) {
                rem_mem_plus(arr, n, k);

            }

            int pos;
            cout << "Which position?\n";
            pos = getN(0, k - 1);


            adding(arr, n, k,pos);
            cout << endl;
            break;
        }

        case 4: {

            cout << "Which element deleting?\n";
            int el;
            el = getN(0, k - 1);

            deleting(arr, n, k, el);
            cout << endl;
            break;
        }

        case 5: {

            clearing(arr, n, k);
            cout << endl;
            break;
        }

        case 6: {
            cout << "From to from cut? Left border->";
            int left, right;
            cin >> left;
            cout << "Right border ->";
            cin >> right;
            cut(arr, n, k, left, right);
            cout << endl;
            break;
        }
        
        case 7: {

            cout << "After which element?";
            int el;
            cin >> el;
            case_7(arr, n, k, el);

            cout << endl;
            break;
        }
        
        case 8: {
            cout << "Which elemets shoudl be deleted?";
            int el;
            cin >> el;
            case_8(arr, n, k, el);


            cout << endl;
            break;
        }


        case 9: {
            exit = 1;
            break;
        }

        default: {
            cout << "Inserted wrong num. Try again!\n";

        }

        }

    } while (exit == 0);

    free (arr);
    return 0;
}

void inserting(int* arr, int n, int& k) {

    ifstream fin("input.txt");
    fin >> k;
    for (int i = 0; i < k; i++) fin >> arr[i];
    fin.close();

};

void printing(int* arr, int n, int& k) {

    for (int i = 0; i < k; i++) cout << arr[i] << " ";

};

void adding(int* & arr, int n, int& k, int pos) {


    k += 1;

    while (k >= n) rem_mem_plus;

    int tmp;
    for (int i = k; i > pos; i--) {

        arr[i] = arr[i-1];
    }

    cout << "Insert new element:";
    cin >> arr[pos];
    

};


void rem_mem_plus(int* & arr, int& n, int& k) {

    if (n >= 3) n += n / 3;
    else n += 1;
    cout << "\tmem=" << n << "*int\n";
    int* tmp = NULL;
    tmp = (int*) realloc(arr, n * sizeof(int));

    if (tmp != NULL) {
        arr = tmp;
    }

};

void rem_mem_minus(int* & arr, int& n, int& k, int del) {

    n = n - del;

    cout << "\tmem=" << n << "*int\n";
    int * tmp = NULL;
    tmp = (int*)realloc(arr, n * sizeof(int));

    if (tmp != NULL) {
        arr = tmp;
    }
};


void deleting(int*& arr, int& n, int& k, int element) {

    for (int i = element; i <= k; i++) {
        arr[i] = arr[i + 1];
    }
    k -= 1;
    rem_mem_minus(arr, n, k, 1);

};

void clearing(int*& arr, int& n, int& k) {

    for (int i = 0; i < n; i++) arr[i] = NULL;
    k = NULL;
    rem_mem_minus(arr, n, k, n - 1);



};

void cut(int* arr, int & n, int& k, int left, int right) {

    for (int i = 0; i < left; i++) {
        for (int j = 0; j < k; j++) {
            arr[j] = arr[j + 1];
        }
    }
    k = right - left + 1;
    rem_mem_minus(arr, n, k, (n - (right - left + 1)));

};

void case_7(int*& arr, int& n, int& k, int element) {

    int i = 0;
    bool check = 0;
    while (i < k && check == 0) {
        if (arr[i] == element) {
            if (k > n) rem_mem_plus(arr, n, k);
            int pos;
            pos = i+1;

            adding(arr, n, k, pos);
            
            check = 1;
        }
        i++;
    }

    if (check == 0) {
        cout << "Element not found!";
    }

};

void case_8(int*& arr, int& n, int& k, int element) {
    bool check = 0;
    for (int i = 0; i < k; i++) {
        
        if (arr[i] == element) {
            for (int j = i; i <= k; i++) {
                arr[i] = arr[i + 1];
            }
            k -= 1;
            check = 1;
            rem_mem_minus(arr, n, k, 1);
            i = 0;
        }

    }
    for (int i = 0; i < k; i++) {

        if (arr[i] == element) {
            for (int j = i; i <= k; i++) {
                arr[i] = arr[i + 1];
            }
            k -= 1;
            check = 1;
            rem_mem_minus(arr, n, k, 1);
            i = 0;
        }

    }

    if (check == 0) {
        cout << "Elements not found!";
    }


};

