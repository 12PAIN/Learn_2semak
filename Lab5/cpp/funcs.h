#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void push();
void showC();
void sort();
void fileCreate(int);
bool remove();
void clear();
void remove_forward();
void remove_next();
void remove_back();
void readFile();
bool push_next(struct Data);
bool push_back(struct Data);
bool push_forward(struct Data);
void print();
bool move_next();
bool move_prev();
int getN(int, int);