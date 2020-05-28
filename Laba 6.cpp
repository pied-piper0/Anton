#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int Size;

void read_from_file(int**& Matrix), Output_Matrix(int** Matrix), graph(int** Matrix), dfs(int v, int* used, int** Matrix);

int main()
{
    setlocale(0, "Rus");
    FILE* my = fopen("file.txt", "r");
    fscanf(my, "%d", &Size); fclose(my);
    int** Matrix = new int* [Size];
    for (int i(0); i < Size; i++)
        Matrix[i] = new int[Size];
    read_from_file(Matrix);
    graph(Matrix);
    int* used = new int[Size];
    memset(used, 0, Size);
    int res = 0;
    for (int i(0); i < Size; i++)
        if (!used[i]) 
        {
            dfs(i, used, Matrix);
            res++;
        }
    cout << "×èñëî êîìïîíåíò ñâÿçíîñòè ãðàôà: " << res << endl;
    delete used;
    for (int i(0); i < Size; i++)
        delete Matrix[i];
    delete Matrix;
    return 0;
}

void dfs(int v, int* used, int** Matrix)//ïîèñê â ãëóáèíó
{
    used[v] = 1;
    for (int i = 0; i < Size; i++)
        if (Matrix[v][i] && !used[i])dfs(i, used, Matrix);
}

void graph(int** Matrix) 
{
    FILE* my = fopen("graph.txt", "w");
    fprintf(my, "strict graph { \n");
    for (int i(0); i < Size; i++)
        for (int j(0); j < Size; j++) 
        {
            if (i >= j)
            {
                if (Matrix[i][j] == 1)
                    fprintf(my, "%d -- %d;\n", i, j);
                else fprintf(my, "%d;%d;\n", i, j);
            }
        }
    fprintf(my, "}\n");
    fclose(my);
}

void read_from_file(int**& Matrix) 
{
    FILE* my = fopen("file.txt", "r");
    if (!my) 
    {
        cout << "File not found.\n";
        system("pause");
        return;
    }
    else
    {
        fscanf(my, "%d", &Size);
        for (int i(0); i < Size; i++)
            for (int j(0); j < Size; j++)
                fscanf(my, "%d", &Matrix[i][j]);
        fclose(my);
    }
}
void Output_Matrix(int** Matrix)
{
    for (int i(0); i < Size; i++)
    {
        for (int j(0); j < Size; j++)
            cout << Matrix[i][j] << " ";
        cout << endl;
    }
}