#include <cmath>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <cstring>
#include <string>
using namespace std;

int const Size = 100;
struct element {
    char existance;
    char name;
    int index;
};
struct Node {
    element _element[Size / 10];
    Node* next = nullptr;
};
struct function_node {
    int component;
    function_node* next = nullptr;
};
void change_Matrix(int** Matrix, Node* node, int counter);
struct NodeList {
    Node* head = nullptr;
    Node* tail = nullptr;
    void addLast(element* _element, int count_in_node) {
        Node* node = new Node;
        for (int i(0); i < count_in_node; i++)
            node->_element[i] = _element[i];
        if (head == nullptr) { head = node; tail = head; }
        else
        {
            tail->next = node;
            tail = node;
        }
    }
    void print() {
        Node* current = head;
        while (current != nullptr) {
            for (int i(0); i < Size / 10; i++)
                cout << current->_element[i].existance << current->_element[i].name << current->_element[i].index;
            current = current->next;
        }
    }
    void read_to_Matrix(int** Matrix, int counter, char* s) {
        Node* current = head;
        while (current != nullptr) {
            change_Matrix(Matrix, current, counter);
            current = current->next;
        }
    }
};
struct function_NodeList {
    function_node* head = nullptr;
    function_node* tail = nullptr;
    void add_Last(int a) {
        function_node* _node = new function_node;
        _node->component = a;
        if (head == nullptr) { head = _node; tail = head; }
        else
        {
            tail->next = _node;
            tail = _node;
        }
    }
    void Print() {
        function_node* current = head;
        cout << "f=(";
        while (current != nullptr) {
            cout << current->component;
            current = current->next;
        }
        cout << ")";
    }
};
void Input_Matrix(int counter, int** Matrix), Output_Matrix(int counter, int** Matrix), write_variables(int counter);
int* convert_to_array(element* elements, int counter);
NodeList to_pieces(char* s, int& counter);
int count_of_different_numbers(char* str), convert(element element);
bool compare(int x, int y);
int main()
{

    char* s = new char[Size];
    gets(s);
    NodeList my;
    int counter = count_of_different_numbers(s);
    int rows = pow(2, counter);
    int** Matrix = new int* [rows];
    for (int i(0); i < rows; i++)
        Matrix[i] = new int[counter + 1];
    Input_Matrix(counter, Matrix);
    my = to_pieces(s, counter);
    my.read_to_Matrix(Matrix, counter, s);
    cout << endl;
    write_variables(counter);
    Output_Matrix(counter, Matrix);
    function_NodeList _vector;
    for (int i(0); i < pow(2, counter); i++)
        _vector.add_Last(Matrix[i][counter]);
    cout << endl;
    _vector.Print();
    for (int i(0); i < rows; i++)
        delete Matrix[i];
    delete Matrix; delete s;
    return 0;
}
void Input_Matrix(int counter, int** Matrix)
{
    for (int i = 0; i < pow(2, counter); i++)
    {
        for (int k = 0; k < counter; k++)
            Matrix[i][k] = (i >> (counter - k - 1)) & 1;
        Matrix[i][counter] = 0;
    }
}
void Output_Matrix(int counter, int** Matrix)
{
    for (int i(0); i < pow(2, counter); i++)
    {
        for (int j(0); j <= counter; j++)
            cout << Matrix[i][j] << " | ";
        cout << endl;
    }
}
void write_variables(int counter)
{
    for (int i(1); i <= counter; i++)
        cout << "x" << i << "| "; cout << "f |";
    cout << endl;
}
int count_of_different_numbers(char* str)
{
    int lenght = strlen(str);
    int* arr = new int[lenght];
    char* help = new char[lenght];
    int arr_count = 0, help_count = 0;
    int n = 0;
    bool in_digit = false;
    for (int i = 0; i < lenght; i++)
    {
        if (isdigit(str[i]))
        {
            if (!in_digit)
            {
                in_digit = true;
                help[help_count] = str[i];
                help_count++;
                if (i == lenght - 1)
                {
                    help[help_count] = '\0';
                    arr[arr_count] = atoi(help);
                    arr_count++; in_digit = false; help_count = 0;
                }
            }
            else {
                help[help_count] = str[i]; help_count++;
                if (i == lenght - 1)
                {
                    help[help_count] = '\0';
                    arr[arr_count] = atoi(help);
                    arr_count++; in_digit = false; help_count = 0;
                }
            }
        }
        else if (help_count != 0) {
            help[help_count] = '\0';
            arr[arr_count] = atoi(help);
            arr_count++; in_digit = false; help_count = 0;
        }

    }
    for (int i = 0; i < arr_count; i++)
    {
        int j = 0;
        while (j < i && arr[j] != arr[i]) j++;

        n += j == i;
    }
    delete arr;
    delete help;
    return n;
}
NodeList to_pieces(char* s, int& counter)
{
    NodeList dnf;
    element DNF[Size];
    int k(0);
    for (int i(0); i < strlen(s) + 1;)
    {
        if (s[i] == 'x')
        {
            DNF[k].existance = '\0';
            DNF[k].name = s[i]; i++;
            DNF[k].index = (int)(s[i]) - 48; i++;
            k++;
        }
        else if (s[i] == '!')
        {
            DNF[k].existance = s[i]; i++;
            DNF[k].name = s[i]; i++;
            DNF[k].index = (int)(s[i]) - 48; i++;
            k++;
        }
        else if (s[i] == 'V' || s[i] == '\0')
        {
            dnf.addLast(DNF, k); k = 0; i++;
        }
        else i++;
    }
    return dnf;
}

void change_Matrix(int** Matrix, Node* node, int  counter)
{
    int* arr = new int[counter];
    element elements[counter + 1];
    for (int i(0); i < counter + 1; i++)
        elements[i] = node->_element[i];
    for (int i(0); i < counter + 1; i++)
    {
        for (int j(0); j < counter + 1; j++)
            if (elements[i].index == elements[j].index && elements[i].existance != elements[j].existance)
            {
                arr = nullptr; break;
            }
    }
    if (arr != nullptr)
    {
        arr = convert_to_array(elements, counter);
        for (int i(0); i < (pow(2, counter)); i++)
        {
            int j(0);
            for (; j < counter;)
            {
                if (compare(arr[j], Matrix[i][j])) j++; else break;
            }
            if (j == counter) Matrix[i][counter] = 1;
        }
    }
}
int* convert_to_array(element* elements, int counter)
{
    int* arr = new int[counter];
    for (int i(0); i < counter; i++)
        arr[i] = 2;
    for (int i(0); i < counter; i++)
    {
        if (convert(elements[i]) == 1)
            arr[elements[i].index - 1] = 1;
        else if (convert(elements[i]) == 0)
            arr[elements[i].index - 1] = 0;
    }
    for (int i(0); i < counter; i++)
        //cout<<arr[i];
        //cout<<endl;getch();
        return arr;
}
int convert(element element)
{
    if (element.existance == '!')
        return 0;
    else
        return 1;
}
bool compare(int x, int y)
{
    if (x == 0 && y == 0)return true;
    if (x == 1 && y == 1)return true;
    if (x == 2 && y == 0)return true;
    if (x == 2 && y == 1)return true;
    if (x == 1 && y == 2)return true;
    if (x == 0 && y == 2)return true;
    if (x == 0 && y == 1)return false;
    if (x == 1 && y == 0)return false;

}