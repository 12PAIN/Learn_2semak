#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Data {
    string name;
    int quantity;
    bool availability;
    float cost;
};

struct Node {
    struct Data data;

    Node* left; //левое поддерево
    Node* right; //правое поддерево
};

Node* root; //корень дерева
Node* temp;

void printTree_value(Node*&, int);
void printTree_char(Node*&, char);
int getSize(Node*& T);
void sort(Node*& T);
void sort_str(Node*& T);
void push(Node*&, struct Data);
void push_str(Node*&, struct Data);
void menu();
void deleteTree(Node*&);
void fileWrite(Node*&, ofstream&);
void fileRead(ifstream&);

int main()
{
    menu();

    return 0;
}

void menu() {
    
    bool exit = 0;

    do {

        cout << "Menu:\n";
        cout << "1. Sort by name\n";
        cout << "2. Sort by cost\n";
        cout << "3. Print by cost\n";
        cout << "4. Print by first char of name\n";
        cout << "5. Add new element\n";
        cout << "6. Delete tree\n";
        cout << "0. Exit\n";
        cout << "-1. Read from file\n";
        cout << "-2. Write current tree to file\n";
        cout << "Insert->";
        int choice; cin >> choice;
        cout << endl;

        system("cls");

        switch (choice) {

        case 1: {

            sort_str(root);

            root = temp;

            break;
        }
        
        case 2: {

            sort(root);

            root = temp;

            break;
        }

        case 3: {

            cout << "Insert value ->";
            int value; cin >> value;

            system("cls");

            printTree_value(root, value);

            system("pause");
            system("cls");

            break;
        }

        case 4: {

            cout << "Insert first char ->";
            char start_char; cin >> start_char;

            system("cls");

            printTree_char(root, start_char);

            system("pause");
            system("cls");

            cout << endl;

            break;
        }

        case 5: {

            struct Data data;
            cout << "Insert name: "; cin >> data.name;
            cout << "Insert cost: "; cin >> data.cost;
            cout << "Insert quantity: "; cin >> data.quantity;
            cout << "Insert availability: "; cin >> data.availability;

            system("cls");

            push(root, data);

            break;
        }

        case 6: {

            deleteTree(root);

            break;
        }
        
        case 0: {

            exit = 1;

            break;
        }

        case -1: {

            ifstream fin("tree.txt");

            fileRead(fin);

            break;
        }

        case -2: {

            ofstream fout("tree.txt" , ios::trunc);

            fileWrite(root, fout);

            break;
        }

        default: {
            cout << "\nRetry!\n";
            break;
        }


        }



        if (exit == 1) break;
    } while (exit != 1);

    deleteTree(root);

}

void fileWrite(Node*& T, ofstream& fout) {
    if (!T) return;

    fileWrite(T->left, fout);

    fout << T->data.name << " " << T->data.cost << " " << T->data.quantity << " " << T->data.availability << endl;

    fileWrite(T->right, fout);
}

void fileRead(ifstream& fin) {

    struct Data data;

    while (fin >> data.name >> data.cost >> data.quantity >> data.availability) push(root, data);
}

void sort(Node*& T) {
    
    if (T) {

        if (T->left) sort(T->left);
        if (T->right) sort(T->right);

        struct Data data = T->data;
        push(temp, data);
        delete T;
        T = NULL;
    }
    else {
        cout << "Tree is empty";
    }
 
}

void sort_str(Node*& T) {

    if (T) {

        if (T->left) sort_str(T->left);
        if (T->right) sort_str(T->right);

        struct Data data = T->data;
        push_str(temp, data);
        delete T;
        T = NULL;
    }
    else {
        cout << "Tree is empty";
    }

}

int getSize(Node*& T) {
    if (!T) return 0;
    if (!T->left && !T->right) return 1;

    int left = 0, right = 0;

    if (T->left) {
        left = getSize(T->left);
    }

    if (T->right) {
        right = getSize(T->right);
    }

    return left + right + 1;
}

void push(Node*& T, struct Data data) {
    
    if (!T) {
        T = new Node;
        T->data = data;
        T->left = NULL;
        T->right = NULL;
        return;
    }

    if (data.cost < T->data.cost) {
        push(T->left, data);
    }
    else {
        push(T->right, data);
    }

}

void push_str(Node*& T, struct Data data) {

    if (!T) {
        T = new Node;
        T->data = data;
        T->left = NULL;
        T->right = NULL;
        return;
    }

    if (strcmp(data.name.c_str(), T->data.name.c_str()) < 0) {
        push_str(T->left, data);
    }
    else {
        push_str(T->right, data);
    }

}

void printTree_value(Node*& T, int value) {
    if (!T) return;

    printTree_value(T->left, value);

    if (T->data.cost < value) {
        cout << "\nName: " << T->data.name;
        cout << "\nCost: " << T->data.cost << "$";
        cout << "\nQuantity: " << T->data.quantity;
        cout << "\nAvailability: " << (T->data.availability == 1 ? "Yes" : "No");
        cout << endl;
    }

    printTree_value(T->right, value);
}

void printTree_char(Node*& T, char start_char) {
    if (!T) return;

    printTree_char(T->left, start_char);

    if (T->data.name[0] == start_char) {
        cout << "\nName: " << T->data.name;
        cout << "\nCost: " << T->data.cost << "$";
        cout << "\nQuantity: " << T->data.quantity;
        cout << "\nAvailability: " << (T->data.availability == 1 ? "Yes" : "No");
        cout << endl;
    }

    printTree_char(T->right, start_char);
}

void deleteTree(Node*& T) {
    if (T) {

        if (T->left) deleteTree(T->left);
        if (T->right) deleteTree(T->right);

        delete T;
        T = NULL;

    }
    else {
        cout << "Tree is empty";
    }
}

