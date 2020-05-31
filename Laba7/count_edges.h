#pragma once
struct element {
    int number;
    double key;
    void Set(int n, int k)
    {
        number = n; key = k;
    }
};
int counter_edge(int i, int** Matrix, int Size) {
    int res = 0;
    for (int j(0); j < Size; j++)
        if (Matrix[i][j]) res++;
    return res;
}
void Create_arr(int** Matrix, int Size, element*& arr) {
    for (int i(0); i < Size; i++)
        arr[i].Set(i, counter_edge(i, Matrix, Size));
}