#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

void memory(double**&, int, int);
void inserting(double**&, int, int, fstream&);
void printing(double**&, int, int);
void triangMatr(double**&, int, int, int &);
void memoryDel(double**& arr, int n, int m);
void determ(double**& arr, int n, int m, int count_replace);
bool dopStr(double**&, int, int, int);
int zeroString(double**&, int, int, int);
void switchStrings(double**&, int, int, int);
void deltaResults(double**&, double**&, int, int);
void reverseMatr(double**&, int, int, int);
bool check(double **&,int,int);

int main() {

    srand(time(0));
    setlocale(LC_ALL, "rus");

    fstream fin("input.txt");

    int n, m, c_r = 0;


    double** arr;

    if (!fin) {
        cout << "Файла не существует, заполняю случайно!\n";
        cout << "Введите размерность матрицы-> N=";
        cin >> n;
        m = n + 1;

        arr = new double* [n];

        memory(arr, n, m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr[i][j] = 1./(1+i+j+1);
            }
        }

    }
    else {

        fin >> n >> m;

        arr = new double* [n];

        memory(arr, n, m);

        inserting(arr, n, m, fin);

    }

    int old_n = n;

    /*if (n != m - 1) {
        cout << "\nМатрица не является системой уравнений или является переопределённой\n";
        memoryDel(arr, old_n, m);
        return 0;
    }*/

    for (unsigned int i = n - 1; i >= 1; i--) {
        dopStr(arr, n, m, i);
    }

    for (unsigned int i = 0; i < n; i++) {
        int pos = zeroString(arr, n, m, i);
        if (pos != -1) {
            //Заменяем нулевую строку
            for (unsigned int l = 0; l < m; l++) {
                arr[pos][l] = arr[n - 1][l];
            }
            //Зануляем крайнюю строку
            for (unsigned int l = 0; l < m; l++) {
                arr[n - 1][l] = 0;
            }
            n--;
        }
    }
    while (zeroString(arr, n, m, n - 1) != -1) {
        n--;
    }



    printing(arr, n, m);

    double** arr_copy = new double* [n];
    memory(arr_copy, n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr_copy[i][j] = arr[i][j];


    cout << "Приводим матрицу к треугольному виду:\n";



    triangMatr(arr, n, m, c_r);

    for (unsigned int i = n - 1; i >= 1; i--) {
        dopStr(arr, n, m, i);
    }

    cout << "\nУдаляем занулившиеся строки(если есть) ->\n";

    for (unsigned int i = 0; i < n; i++) {
        int pos = zeroString(arr, n, m, i);
        if (pos != -1) {
            //Заменяем нулевую строку
            for (unsigned int l = 0; l < m; l++) {
                arr[pos][l] = arr[n - 1][l];
            }
            //Зануляем крайнюю строку
            for (unsigned int l = 0; l < m; l++) {
                arr[n - 1][l] = 0;
            }
            n--;
        }
    }
    while (zeroString(arr, n, m, n - 1) != -1) {
        n--;
    }

    printing(arr,n,m);

    if (n+1 == m) {

        determ(arr, n, m, c_r);

        cout << endl;

        deltaResults(arr, arr_copy, n, m);
    }
    else {

        cout << "\nТак как матрица не квадратная, то не существует определителя, а X-ы могут быть выражены только через свободные коэфициенты.\n";

    }

    cout << "\nОбратная матрица:\n";

    reverseMatr(arr_copy, n, m, c_r);

    memoryDel(arr, old_n, m);
    memoryDel(arr_copy, old_n, m);

    return 0;
}

bool dopStr(double**& arr, int n, int m, int k) {
    for (int i = 0; i < k; i++) {
        bool doppel = true;
        for (unsigned int j = 0; j < m; j++) {
            if (arr[i][j] != arr[k][j]) doppel = false;
        }
        if (doppel == true) {
            for (unsigned int j = 0; j < m; j++) arr[k][j] = 0;
            printing(arr,n,m);
            return true;
        }
    }
    return false;
}

int zeroString(double**& arr, int n, int m, int k) {
    for (unsigned int i = 0; i < m; i++) {
        if (arr[k][i] != 0) return -1;
    }
    return k;
}

void memory(double**& arr, int n, int m) {

    for (int i = 0; i < n; i++) {

        arr[i] = new double[m];

    }

};

bool check(double**& arr, int n, int m){

    for(int i = 1; i < n; i++){

        for(int j = 0; j < i; j++){
            if(arr[i][j] != 0) return 0;
        }

    }

    return 1;
}

void memoryDel(double**& arr, int n, int m) {

    for (int i = 0; i < n; i++) {

        delete[] arr[i];

    }

    delete[]arr;

};

void inserting(double**& arr, int n, int m, fstream& fin) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fin >> arr[i][j];
        }
    }


};

void printing(double**& arr, int n, int m) {

    cout << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(5) << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout <<"-----------------------------------" <<endl;

};

void triangMatr(double**& arr, int n, int m, int & count_replace) {
    double koef;

    for (unsigned int k = 0; k < n; k++) for (unsigned int i = k + 1; i < n; i++) {
        if (arr[k][k] == 0) {
            switchStrings(arr, n, m, k);
            count_replace++;
        }
        koef = -1 * arr[i][k] / arr[k][k];

        for (unsigned int j = k; j < n + 1; j++){


                if(check(arr,n,m) == 1) break;

                arr[i][j] = arr[i][j] + arr[k][j] * koef;



        };



    }
    printing(arr, n, m);
}

void switchStrings(double**& arr, int n, int m, int k) {
    double* buf = new double[m];
    //Нахождение строки с максимальным по модулю элементом
    int pos = k + 1;
    double max = 0;
    if (n - k > 1) {
        for (unsigned int i = k + 1; i < n; i++) {
            if (fabs(arr[i][k]) > max) {
                max = fabs(arr[i][k]);
                pos = i;
                //cout << endl << max << endl;
            }
        }
    }
    //Перемещение строк
    //Буфер
    for (unsigned int l = 0; l < m; l++) {
        buf[l] = arr[k][l];
    }
    //Заменяем k-тую строку
    for (unsigned int l = 0; l < m; l++) {
        arr[k][l] = arr[pos][l];
    }
    //Заменяем целевую строку
    for (unsigned int l = 0; l < m; l++) {
        arr[pos][l] = buf[l];
    }

    printing(arr, n, m);

    delete[] buf;
}

void deltaResults(double**& arr, double**& arr_copy, int n, int m) {

    double* x = new double[n];
    double res = 0;

    for (int i = n - 1; i >= 0; i--) {
        res = 0;
        for (int j = i + 1; j <= n - 1; j++) res = res - x[j] * arr[i][j];
        res += arr[i][m - 1];
        x[i] = res / arr[i][i];
    }

    cout << "Решение:\n";


    for (int i = 0; i < n; i++) {

        cout << "X" << i + 1 << "=" <<x[i] << " ";

    }

    double* y = new double[n];

    cout << "\n\nОбратные результаты последнего столбца: ";

    for (unsigned int i = 0; i < n; i++) {
        double res = 0;
        for (unsigned int j = 0; j < n; j++) {
            res += arr_copy[i][j] * x[j];
        }

        y[i] = res;

        cout << y[i] << ", ";
    }

    cout << endl << endl;
    double max;
    max = fabs(y[0] - arr_copy[0][m - 1]);
    for (unsigned int i = 1; i < n; i++) {
        if (fabs(y[i] - arr_copy[i][m - 1]) > max) max = fabs(y[i] - arr_copy[i][m - 1]);
    }

    cout << "Отклонение дельта =" << max << endl;

    delete[] y;
    delete[] x;

}

void reverseMatr(double**& arr, int n, int m, int c_r) {

    c_r = 0;

    double** reverse = new double* [n];

    memory(reverse, n, m * 2-2);



    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++) {
            reverse[i][j] = arr[i][j];
        }

        for (int j = m-1; j < m * 2-1; j++) {

            if (j == m-1 + i) reverse[i][j] = 1;
            else reverse[i][j] = 0;

        }



    }

    printing(reverse, n, m * 2-2);

    triangMatr(reverse, n, m*2-2, c_r);

    cout << "\nОбратная матрица:\n";

    printing(reverse, n, m-1);

    memoryDel(reverse, n, m * 2);


}

void determ(double**& arr, int n, int m, int count_replace) {

    if (n == m - 1) {
        float determ = 1;
        for (int i = 0; i < n; i++) {
            determ *= arr[i][i];
        }
        determ *= pow(-1, count_replace);
        cout << "Определитель = " << setprecision(5) <<determ;

    }
    else {

        cout << "Определителя не существует, матрица не квадратная";

    }

    cout << endl;

}
