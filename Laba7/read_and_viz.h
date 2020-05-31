#pragma once
void graph(int** Matrix, int Size) {
    FILE* my = fopen("graph.txt", "w");
    fprintf(my, "strict graph { \n");
    for (int i(0); i < Size; i++)
        for (int j(0); j < Size; j++) {
            if (i >= j) {
                if (Matrix[i][j] == 1)
                    fprintf(my, "%d -- %d;\n", i, j);
                else fprintf(my, "%d;%d;\n", i, j);
            }
        }
    fprintf(my, "}\n");
    fclose(my);
}
void read_from_file(int**& Matrix, int& Size) {
    FILE* my = fopen("file.txt", "r");
    if (!my) {
        std::cout << "File not found.\n";
        system("pause");
        return;
    }
    else {
        fscanf(my, "%d", &Size);
        for (int i(0); i < Size; i++)
            for (int j(0); j < Size; j++)
                fscanf(my, "%d", &Matrix[i][j]);
        fclose(my);
    }
}
void Output_Matrix(int** Matrix, int Size)
{
    for (int i(0); i < Size; i++)
    {
        for (int j(0); j < Size; j++)
            std::cout << Matrix[i][j] << " ";
        std::cout << endl;
    }
}
template<class T>
void output_arr(T* arr, int Size)
{
    for (int i(0); i < Size; i++) cout << arr[i]; cout << endl << endl << endl;
}