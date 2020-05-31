#include <iostream>
#include <stdio.h>
#include <string>
#include "sort.h"
#include "read_and_viz.h"
#include "count_edges.h"
#include "length_edges.h"
#include "decart_func.h"
#include <ctime>
using namespace std;
bool operator<(element e1, element e2) {
    return e1.key < e2.key;
}
bool operator<=(element e1, element e2) {
    return e1.key <= e2.key;
}
bool operator>(element e1, element e2) {
    return e1.key > e2.key;
}
ostream& operator<<(ostream& out, element el) {
    out << el.number << "(" << el.key << ") ";
    return out;
}
int main()
{
    setlocale(0, "Rus"); int Size; unsigned long long t1 = 0, t2 = 0;
    FILE* my = fopen("file.txt", "r");
    fscanf(my, "%d", &Size); fclose(my);
    int** Matrix = new int* [Size];
    for (int i(0); i < Size; i++)
        Matrix[i] = new int[Size];
    read_from_file(Matrix, Size);


    element* count_edges = new element[Size];
    Create_arr(Matrix, Size, count_edges);
    t1 = clock();//cout<<t1<<endl;
    BubbleSort(count_edges, Size); t2 = clock();//cout<<t2<<endl;
    cout << "Bubble sort: (time=" << t2 - t1 << ")" << endl;
    output_arr(count_edges, Size);


    element* length = new element[Size];
    read(Matrix, Size, length); t1 = clock();
    QuickSort(length, 0, Size - 1); t2 = clock();
    cout << "Quick sort: (time=" << t2 - t1 << ")" << endl;
    output_arr(length, Size);


    element* func = new element[Size];
    string s;
    cout << "Enter a function: "; getline(cin, s);
    decart_read(Matrix, Size, func, s); t1 = clock();
    MergeSort(func, 0, Size - 1); t2 = clock();
    cout << "Merge sort: (time=" << t2 - t1 << ")" << endl;
    output_arr(func, Size);


    for (int i(0); i < Size; i++)
        delete Matrix[i];
    delete Matrix;
    return 0;
}