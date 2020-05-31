#pragma once
#include <cmath>
struct point {
    int number;
    int x;
    int y;
};
double length(point a, point b) {
    double res = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    return res;
}
double length_for_point(int** Matrix, int j, int Size, point* arr)
{
    double res = 0;
    for (int p(0); p < Size; p++)
        if (Matrix[j][p] == 1)
            res += length(arr[j], arr[p]);
    return res;
}
void read(int**& Matrix, int& Size, element*& mas) {
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
        mas[j].key = length_for_point(Matrix, j, Size, arr);
    }
}