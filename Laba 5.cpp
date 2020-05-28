#include <iostream>
#include <cstdio>
#include <conio.h>
#include <string>
#include <cstring>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int Size = 50;
int index, Counter = 0;

struct info 
{
    string eng;
    string ru;
    int counter;
};

struct node 
{
    info data;
    node* right = nullptr;
    node* left = nullptr;
};

void fin(), treeprint(node* tree), fout(), Translate(string current);
info* file_to_arr(), * nfile_to_arr();
char* itoa(int a);
int Max(int a, int b), maxVal(node* tree), MainMenu();
node* DeleteNode(node* tree, int c, info* words), * add(node* tree, info* current);

int main() 
{
    FILE* ind = fopen("index.txt", "r");
    char* c = new char[10]; fgets(c, 10, ind); 
    index = atoi(c);
    fclose(ind);
    FILE* f = fopen("file.txt", "r+b");
    FILE* s = fopen("nfile.txt", "a+b");
    info temp; 
    fread(&temp, sizeof(info), 1, f); 
    while (!feof(f))
    { 
        fwrite(&temp, sizeof(info), 1, s); 
        fread(&temp, sizeof(info), 1, f);
    }
    fclose(f);
    fclose(s);
    int answer;
    node* tree = NULL;
    node* ntree = NULL;
    do
    {
        answer = MainMenu();
        switch (answer) 
        {
        case 0: {fin(); fout(); system("pause"); break; }

        case 1: 
        {
            Counter = 0; tree = nullptr; info* arr = file_to_arr();
            cout << "Initial tree:" << endl;
            cout << endl << endl;
            for (int i(0); i < index; i++) {
                tree = add(tree, &arr[i]);

            }
            treeprint(tree); system("pause");
            break; 
        }

        case 2:
        {
            info* words = new info[Size];
            while (tree)
            {
                int a = maxVal(tree);
                tree = DeleteNode(tree, a, words);
            }
            for (int i(0); i < Counter; i++)
                cout << i + 1 << ") " << words[i].eng << endl;
            cout << endl << endl; system("pause"); Counter = 0; break;
        }

        case 3: 
        {
            string current;
            cout << "                  Enter word (Eng.): \t";
            cin >> current;
            Translate(current);
            system("pause");
            break;
        }

        case 4: 
        {
            Counter = 0; ntree = nullptr; info* narr = nfile_to_arr();
            cout << "New tree:" << endl;
            cout << endl << endl;
            for (int i(0); i < index; i++)
            {
                ntree = add(ntree, &narr[i]);
            }
            treeprint(ntree); system("pause");
            break; 
        }

        case 5: 
        {
            info* nwords = new info[Size];
            while (ntree) 
            {
                int na = maxVal(ntree);
                ntree = DeleteNode(ntree, na, nwords);
            }
            for (int i(0); i < Counter; i++)
                cout << i + 1 << ") " << nwords[i].eng << endl;
            cout << endl << endl; system("pause"); Counter = 0; break; 
        }

        case 6: break;
        }
    } 
    while (answer != 6);
    FILE* index1 = fopen("index.txt", "w"); c = itoa(index); fputs(c, index1); fclose(index1);
    remove("file.txt");
    rename("nfile.txt", "file.txt");
    remove("nfile.txt");
    return 0;
}



void Translate(string current)
{
    info help; bool change = false; int i = 0;
    FILE* file = fopen("nfile.txt", "rb+");
    fread(&help, sizeof(info), 1, file);
    do
    {
        if (strcmp(help.eng.c_str(), current.c_str()) == 0)
        {
            change = true;
            break;
        }
        else  i++;
        fread(&help, sizeof(info), 1, file);
    }
    while (!feof(file));
    if (!change) cout << "                    No such words." << endl;
    else
    {
        cout << "Translation: " << help.ru << endl;
        fseek(file, (i) * sizeof(info), SEEK_SET);
        fread(&help, sizeof(info), 1, file);
        help.counter++;
        fseek(file, (i) * sizeof(info), SEEK_SET);
        fwrite(&help, sizeof(info), 1, file);
    }
    fclose(file);

}

int Max(int a, int b)
{
    return((a <= b) ? b : a);
}

int maxVal(node* tree)
{
    if ((tree->left == NULL) && (tree->right == NULL))
        return tree->data.counter;
    else
        if (tree->left == NULL)
            return Max(tree->data.counter, maxVal(tree->right));
        else
            if (tree->right == NULL)
                return Max(tree->data.counter, maxVal(tree->left));
            else
                return Max(tree->data.counter, Max(maxVal(tree->left), maxVal(tree->right)));

}
node* DeleteNode(node* tree, int c, info* words) 
{
    if (tree == NULL)
        return tree;
    if (c == tree->data.counter) 
    {
        words[Counter].eng = tree->data.eng;
        words[Counter].ru = tree->data.ru;
        words[Counter++].counter = tree->data.counter;
        node* tmp;
        if (tree->right == NULL)
            tmp = tree->left;
        else
        {
            node* ptr = tree->right;
            if (ptr->left == NULL)
            {
                ptr->left = tree->left;
                tmp = ptr;
            }
            else 
            {
                node* pmin = ptr->left;
                while (pmin->left != NULL) 
                {
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = tree->left;
                pmin->right = tree->right;
                tmp = pmin;
            }
        }

        delete tree;
        return tmp;
    }
    else 
    {
        tree->left = DeleteNode(tree->left, c, words);
        tree->right = DeleteNode(tree->right, c, words);
    }
    return tree;
}
char* itoa(int a) 
{
    char* s = new char[5];
    int i = 0;
    while (a) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    return s;
}
info* file_to_arr() 
{
    info b;
    FILE* my2 = fopen("file.txt", "r+b");
    info* arr = new info[index];
    fread(&b, sizeof(b), 1, my2);
    int i = 0;
    do
    {
        arr[i] = b; i++; fread(&b, sizeof(b), 1, my2);
    } while (!feof(my2));
    fclose(my2);
    return arr;
}
info* nfile_to_arr() 
{
    info b;
    FILE* my3 = fopen("nfile.txt", "r+b");
    info* arr = new info[index];
    fread(&b, sizeof(b), 1, my3);
    int i = 0;
    do
    {
        arr[i] = b; i++; fread(&b, sizeof(b), 1, my3);
    } while (!feof(my3));
    fclose(my3);
    return arr;
}
void treeprint(node* tree) 
{
    if (tree != NULL)
    {
        treeprint(tree->left);
        cout << tree->data.eng << " " << tree->data.ru << " " << tree->data.counter << endl;
        treeprint(tree->right);
    }
}
node* add(node* tree, info* current) 
{
    if (tree == NULL)
    {
        tree = new node;
        tree->data.eng = current->eng;
        tree->data.ru = current->ru;
        tree->data.counter = current->counter;
    }
    else if (strcmp(current->eng.c_str(), tree->data.eng.c_str()) <= 0)
        tree->left = add(tree->left, current);
    else tree->right = add(tree->right, current);
    return tree;
}
void fin() 
{
    info a;
    cout << "                     Enter new word:  ";
    cin >> a.eng;
    cout << "                        Translation:  ";
    cin >> a.ru;
    cout << "                            Counter:  ";
    cin >> a.counter;
    index++;
    FILE* my = fopen("file.txt", "a+b");
    fwrite(&a, sizeof(a), 1, my);
    fclose(my);
    FILE* nmy = fopen("nfile.txt", "a+b");
    fwrite(&a, sizeof(a), 1, nmy);
    fclose(nmy);
}
void fout()
{
    info b;
    FILE* my1 = fopen("file.txt", "r+b");
    fread(&b, sizeof(b), 1, my1);
    do
    {
        cout << b.eng << " " << b.ru << " " << b.counter << endl; fread(&b, sizeof(b), 1, my1);
    } 
    while (!feof(my1));
    fclose(my1);
}
int MainMenu()
{
    int key = 0;
    int code;
    do 
    {
        system("cls");
        key = (key + 7) % 7;
        if (key == 0) cout << "-> Add word " << endl;
        else  cout << "Add word" << endl;
        if (key == 1) cout << "-> Build original tree" << endl;
        else  cout << "Build original tree" << endl;
        if (key == 2) cout << "-> Show original vocabulary " << endl;
        else  cout << "Show original vocabulary" << endl;
        if (key == 3) cout << "-> Translate from Eng. to Rus." << endl;
        else  cout << "Translate from Eng. to Rus." << endl;
        if (key == 4) cout << "-> Build new tree" << endl;
        else  cout << "Build new tree" << endl;
        if (key == 5) cout << "-> Show new vocabulary " << endl;
        else  cout << "Show new vocabulary" << endl;
        if (key == 6) cout << "-> Exit" << endl;
        else  cout << "Exit" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } 
    while (code != 13);
    system("cls");
    return key;
}