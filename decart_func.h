#pragma once
#include<cmath>
double func(point p, string s) {
    double res;
    if (s == "sin")res = sin(p.x + p.y);
    else if (s == "cos")res = cos(p.x + p.y);
    else if (s == "+")res = p.x + p.y;
    else if (s == "-")res = p.x - p.y;
    return res;
}
void decart_read(int**& Matrix, int& Size, element*& mas, string s) {
    point* arr;
    FILE* my = fopen("file.txt", "r");
    if (!my) {
        std::cout << "File not found.\n";
        system("pause");
        return;
    }
    else {
        fscanf(my, "%d", &Size);
        arr = new point[Size];
        for (int i(0); i < Size; i++)
            for (int j(0); j < Size; j++)
            {
                fscanf(my, "%d", &Matrix[i][j]);
            }
        for (int k(0); k < Size; k++)
        {
            fscanf(my, "%d", &arr[k].x);
            fscanf(my, "%d", &arr[k].y);
            arr[k].number = k;
        }
        fclose(my);
    }
    for (int j(0); j < Size; j++)
    {
        mas[j].number = j;
        mas[j].key = func(arr[j], s);
    }
}