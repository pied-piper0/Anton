#include<windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include<cstdio>
#include<cmath>
using namespace std;
const int Size = 100;

struct node {
    int info;
    node* next = nullptr;
};
struct NodeList {
    node* head = nullptr;
    node* tail = nullptr;
    void add_Last(int a) {
        node* _node = new node;
        _node->info = a;
        if (head == nullptr) { head = _node; tail = head; }
        else
        {
            tail->next = _node;
            tail = _node;
        }
    }
    int length()
    {
        int counter = 0;
        node* current = head;
        while (current != nullptr) {
            counter++;
            current = current->next;
        }
        return counter;
    }
    void Print() {
        node* current = head;
        while (current != nullptr) {
            cout << current->info << "\t";
            current = current->next;
        }
    }
};
struct NODE {
    int value;
    int position;
    NODE* next = nullptr;
};
struct NODEList {
    NODE* head = nullptr;
    NODE* tail = nullptr;
    void ADDLast(int a, int b) {
        NODE* _node = new NODE;
        _node->value = a; _node->position = b;
        if (head == nullptr) { head = _node; tail = head; }
        else
        {
            tail->next = _node;
            tail = _node;
        }
    }
    void PRINT() {
        NODE* current = head;
        while (current != nullptr) {
            cout << current->value << "(" << current->position << ") ";
            current = current->next;
        }
        cout << endl;
    }
};
struct Node {
    int x;
    NODEList* List = new NODEList;
    Node* down = nullptr;
};
void Sort_list(NodeList& values, NodeList& rows, NodeList& columns);
struct index_List {
    Node* first = nullptr;
    Node* last = nullptr;

    void ADDlast(Node* need)
    {
        if (first == nullptr) { first = need; first->down = last; last = first; }
        else { last->down = need; need->down = nullptr; last = need; }
    }

    bool Exist(int need)
    {
        bool flag = false;
        Node* current = first;
        while (current != nullptr)
        {
            if (current->x == need)
            {
                flag = true; break;
            }
            else
                current = current->down;
        }
        return(flag);
    }
    void Print()
    {
        Node* current = first;
        while (current != nullptr)
        {
            cout << current->x << " -> "; current->List->PRINT();
            current = current->down;
        }
        cout << endl;
    }
    void to_index_rows_list(NodeList& values1, NodeList& rows1, NodeList& columns1)
    {
        Sort_list(values1, rows1, columns1);
        node* cr = rows1.head, * cc = columns1.head, * cv = values1.head;
        for (; cr != nullptr; cr = cr->next)
        {
            Node* Add;
            if (!Exist(cr->info)) {
                Add = new Node; Add->x = cr->info;
                Add->List->ADDLast(cv->info, cc->info); ADDlast(Add); cv = cv->next; cc = cc->next;
            }
            else {
                Node* This = first;
                while (This != nullptr)
                {
                    if (This->x == cr->info) { This->List->ADDLast(cv->info, cc->info); cv = cv->next; cc = cc->next; break; }
                    else
                        This = This->down;
                }
            }
        }
    }
    void to_index_columns_list(NodeList& values2, NodeList& rows2, NodeList& columns2)
    {
        node* cr = rows2.head, * cc = columns2.head, * cv = values2.head;
        for (; cc != nullptr; cc = cc->next)
        {
            Node* Add;
            if (!Exist(cc->info)) {
                Add = new Node; Add->x = cc->info;
                Add->List->ADDLast(cv->info, cr->info); ADDlast(Add); cv = cv->next; cr = cr->next;
            }
            else {
                Node* This = first;
                while (This != nullptr)
                {
                    if (This->x == cc->info) { This->List->ADDLast(cv->info, cr->info); cv = cv->next; cr = cr->next; break; }
                    else
                        This = This->down;
                }
            }
        }
    }
};
struct brief_node {
    int number;
    int counter = 0;
    brief_node* next = nullptr;
};
struct Brief {
    brief_node* first = nullptr;
    brief_node* last = nullptr;
    void ADD(int number, int counter) {
        brief_node* current = new brief_node;
        current->number = number;
        current->counter = counter;
        if (first == nullptr) { first = current; last = first; }
        else { last->next = current; last = current; }
    }
    void PRINT() {
        brief_node* current = first;
        while (current != nullptr)
        {
            cout << current->number << "(" << current->counter << ");"; current = current->next;
        }
        cout << endl;
    }

};
struct sym //ñòðóêòóðû èëè çàïèñè
{
    unsigned char ch;
    float freq;
    char code[255];
    sym* left;
    sym* right;
};

union code
{
    unsigned char chhh;//ïåðåìåííàÿ ñîäåðæàùàÿ êîä äëÿ çàïèñè â ñæàòûé ôàéë
    struct byte
    {
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    }byte;
};
void read(int** First_Matrix, int** Second_Matrix), brief(int** Matrix), index(int** Matrix, NodeList& values, NodeList& rows, NodeList& columns),
add(NodeList& values1, NodeList& rows1, NodeList& columns1, NodeList& values2, NodeList& rows2, NodeList& columns2),
multiply(NodeList& values1, NodeList& rows1, NodeList& columns1, NodeList& values2, NodeList& rows2, NodeList& columns2),
algorithm(), output_matrix(int** matrix, int n), read_from_file(char* s, int** First_Matrix, int** Second_Matrix),
print(NodeList& values, NodeList& rows, NodeList& columns), makeCodes(sym* root);
int MainMenu(), ReadMenu(), check(NODEList* first, NODEList* second);
sym* makeTree(sym* psym[], int k);
int main()
{
    int** First_Matrix = new int* [Size];
    for (int i(0); i < Size; i++)
        First_Matrix[i] = new int[Size];
    int** Second_Matrix = new int* [Size];
    for (int i(0); i < Size; i++)
        Second_Matrix[i] = new int[Size];
    NodeList values1, values2, rows1, rows2, columns1, columns2;
    int answer;
    do {
        answer = MainMenu();
        switch (answer)
        {
        case 0: {read(First_Matrix, Second_Matrix); break; }
        case 1: {brief(First_Matrix); break; }
        case 2: {brief(Second_Matrix); break; }
        case 3: {index(First_Matrix, values1, rows1, columns1); break; }
        case 4: {index(Second_Matrix, values2, rows2, columns2); break; }
        case 5: {print(values1, rows1, columns1); break; }
        case 6: {print(values2, rows2, columns2); break; }
        case 7: {add(values1, rows1, columns1, values2, rows2, columns2); break; }
        case 8: {multiply(values1, rows1, columns1, values2, rows2, columns2); break; }
        case 9: {algorithm(); system("pause"); break; }
        case 10:break;
        }
    } while (answer != 10);
    for (int i(0); i < Size; i++)
        delete First_Matrix[i];
    delete First_Matrix;
    for (int i(0); i < Size; i++)
        delete Second_Matrix[i];
    delete Second_Matrix;

    return 0;
}
void Sort_list(NodeList& values, NodeList& rows, NodeList& columns) {

    node* cv = values.head, * cr = rows.head, * cc = columns.head, * index1 = rows.head, * index2;
    for (; index1 != nullptr; index1 = index1->next)
        for (index2 = rows.head; index2 != nullptr; index2 = index2->next)
        {
            if (cr->info > cr->next->info)
                while (cr->info > cr->next->info)
                {
                    int vtemp = cv->info;
                    cv->info = cv->next->info;
                    cv->next->info = vtemp;

                    int rtemp = cr->info;
                    cr->info = cr->next->info;
                    cr->next->info = rtemp;

                    int ctemp = cc->info;
                    cc->info = cc->next->info;
                    cc->next->info = ctemp;

                    if (cr->next == rows.tail) break;
                    else { cr = cr->next; cv = cv->next; cc = cc->next; }
                }
            else { if (cr->next == rows.tail) { cr = rows.head; cv = values.head; cc = columns.head; } else { cr = cr->next; cv = cv->next; cc = cc->next; } }
        }
}
void algorithm() {
    FILE* fp, * fp2, * fp3; //óêàçàòåëè íà ôàéëû
    fp = fopen("fin.txt", "rb"); //îòêðûâàåì êîíêðåòíûé ôàéë
    fp2 = fopen("fout.txt", "wb");//îòêðûâàåì ôàéë äëÿ çàïèñè áèíàðíîãî êîäà
    fp3 = fopen("binary.txt", "wb");//îòêðûâàåì ôàéë äëÿ çàïèñè ñæàòîãî ôàéëà
    int chh;  // â ýòó ïåðåìåííóþ ÷èòàåòñÿ èíôîðìàöèÿ èç ôàéëà
    int k = 0; //ñ÷¸ò÷èê êîëè÷åñòâà ðàçëè÷íûõ áóêâ, óíèêàëüíûõ ñèìâîëîâ
    int kk = 0; // ñ÷¸ò÷òê êîëè÷åñòâà âñåõ çíàêîâ â ôàéëå
    int fsize2 = 0;//ñ÷¸ò÷èê êîëè÷åñòâà ñèìâîëîâ èç 0 è 1 â ïðîìåæóòî÷íîì ôàéëå teemp
    int ts;//ðàçìåð õâîñòà ôàéëà (òî, ÷òî íå êðàòíî 8 â ïðîìåæóòî÷íîì ôàéëå)
    int kolvo[256] = { 0 };//èíèöèàëèçèðóåì ìàññèâ êîëè÷åñòâà óíèêàëüíûõ ñèìâîëîâ
    sym simbols[256] = { 0 }; //èíèöèàëèçèðóåì ìàññèâ çàïèñåé
    sym* psym[256]; //èíèöèàëèçèðóåì ìàññèâ óêàçàòåëåé íà çàïèñè
    float summir = 0;//ñóììà ÷àñòîò âñòðå÷àåìîñòè
    int mes[8];//ìàññèâ 0 è 1
    char j = 0;//âñïîìîãàòåëüíàÿ ïåðåìåííàÿ
    if (fp == NULL)
    {
        puts("FILE NOT OPEN!");
    }
    else {
        sym* symbols = (sym*)malloc(k * sizeof(sym));//ñîçäàíèå äèíàìè÷åñêîãî ìàññèâà ñòðóêòóð simbols
        sym** psum = (sym**)malloc(k * sizeof(sym*));//ñîçäàíèå äèíàìè÷åñêîãî ìàññèâà óêàçàòåëåé íà simbols
        //Íà÷èíàåì ïîáàéòíî ÷èòàòü ôàéë è ñîñòàâëÿòü òàáëèöó âñòðå÷àåìîñòè
        while ((chh = fgetc(fp)) != EOF)
        {
            for (int j = 0; j < 256; j++)
            {
                if (chh == simbols[j].ch)
                {
                    kolvo[j]++;
                    kk++;
                    break;
                }
                if (simbols[j].ch == 0)
                {
                    simbols[j].ch = (unsigned char)chh;
                    kolvo[j] = 1;
                    k++; kk++;
                    break;
                }
            }
        }

        // Ðàññ÷¸ò ÷àñòîòû âñòðå÷àåìîñòè
        for (int i = 0; i < k; i++)
            simbols[i].freq = (float)kolvo[i] / kk;

        for (int i = 0; i < k; i++) //â ìàññèâ óêàçàòåëåé çàíîñèì àäðåñà çàïèñåé
            psym[i] = &simbols[i];

        //Ñîðòèðîâêà ïî óáûâàíèþ
        sym tempp;
        for (int i = 1; i < k; i++)
            for (int j = 0; j < k - 1; j++)
                if (simbols[j].freq < simbols[j + 1].freq)
                {
                    tempp = simbols[j];
                    simbols[j] = simbols[j + 1];
                    simbols[j + 1] = tempp;
                }

        for (int i = 0; i < k; i++)
        {
            summir += simbols[i].freq;
            printf("Ch= %d\tFreq= %f\tPPP= %c\t\n", simbols[i].ch, simbols[i].freq, psym[i]->ch, i);
        }
        printf("\n Symbols = %d\tFreq_sum=%f\n", kk, summir);

        sym* root = makeTree(psym, k);//âûçîâ ôóíêöèè ñîçäàíèÿ äåðåâà Õîôìàíà

        makeCodes(root);//âûçîâ ôóíêöèè ïîëó÷åíèÿ êîäà

        rewind(fp);//âîçâðàùàåì óêàçàòåëü â ôàéëå â íà÷àëî ôàéëà
    //â öèêëå ÷èòàåì èñõîäíûé ôàéë, è çàïèñûâàåì ïîëó÷åííûå â ôóíêöèÿõ êîäû â ïðîìåæóòî÷íûé ôàéë
        while ((chh = fgetc(fp)) != EOF)
        {
            for (int i = 0; i < k; i++)
                if (chh == simbols[i].ch)
                    fputs(simbols[i].code, fp2);
        }
        fclose(fp2);

        //Çàíîâî îòêðûâàåì ôàéë ñ áèíàðíûì êîäîì, íî òåïåðü äëÿ ÷òåíèÿ
        int i = 0;
        fp2 = fopen("fout.txt", "rb");
        //Ñ÷èòàåì ðàçìåð áèíàðíîãî ôàéëà(êîëè÷åñòâî ñèìâîëîâ â í¸ì)
        while ((chh = fgetc(fp2)) != EOF)
            fsize2++;

        ts = fsize2 % 8;//íàõîäèì îñòàòîê, êîëè÷åñòâî ñèìâîëîâ íå êðàòíûõ 8 (õâîñò)

        //ôîðìèðóåì çàãîëîâîê ñæàòîãî ôàéëà ÷åðåç ïîëÿ áàéòîâ
        fwrite("compresing!!!", sizeof(char), 24, fp3);//óñëîâíàÿ ïîäïèñü
        fwrite(&k, sizeof(int), 1, fp3);//êîëè÷åñòâî óíèêàëüíûõ ñèìâîëîâ
        fwrite(&ts, sizeof(int), 1, fp3);//âåëè÷èíà õâîñòà
        //Çàïèñûâàåì â ñæàòûé ôàéë òàáëèöó âñòðå÷àåìîñòè
        for (i = 0; i < k; i++)
        {
            fwrite(&simbols[i].ch, sizeof(sym), 1, fp3);
            fwrite(&simbols[i].freq, sizeof(sym), 1, fp3);
        }

        rewind(fp2);//âîçâðàùàåì óêàçàòåëü â ïðîìåæóòî÷íîì ôàéëå â íà÷àëî ôàéëà

        union code code1;//èíèöèàëèçèðóåì ïåðåìåííóþ code1
        //×èòàåì áèíàðíûé ôàéë, çàíîñÿ ïîñëåäîâàòåëüíî êàæäûå 8 ýëåìåíòîâ â ìàññèâ äëÿ ïîñëåäóþùåé ïîáèòîâîé îáðàáîòêè â îáúåäèíåíèè union
        j = 0;
        for (int i = 0; i < fsize2 - ts; i++)
        {
            mes[j] = fgetc(fp2);
            if (j == 7)
            {
                code1.byte.b1 = mes[0] - 48;
                code1.byte.b2 = mes[1] - 48;
                code1.byte.b3 = mes[2] - 48;
                code1.byte.b4 = mes[3] - 48;
                code1.byte.b5 = mes[4] - 48;
                code1.byte.b6 = mes[5] - 48;
                code1.byte.b7 = mes[6] - 48;
                code1.byte.b8 = mes[7] - 48;
                fputc(code1.chhh, fp3);
                j = 0;
            }
            j++;
        }
        //Çàïèñûâàåì õâîñò
        j = 0;
        for (int i = 0; i <= ts; i++)
        {
            mes[j] = fgetc(fp2);
            if (j == ts)
            {
                code1.byte.b1 = mes[0] - 48;
                code1.byte.b2 = mes[1] - 48;
                code1.byte.b3 = mes[2] - 48;
                code1.byte.b4 = mes[3] - 48;
                code1.byte.b5 = mes[4] - 48;
                code1.byte.b6 = mes[5] - 48;
                code1.byte.b7 = mes[6] - 48;
                code1.byte.b8 = mes[7] - 48;
                fputc(code1.chhh, fp3);
            }
            j++;
        }
        fclose(fp); fclose(fp2); fclose(fp3);
        cout << endl;
        cout << "To see compressed file open file fout.txt" << endl << endl;
    }
};
void print(NodeList& values, NodeList& rows, NodeList& columns) {
    node* v = values.head, * c = columns.head, * r = rows.head;
    int** Matrix = new int* [Size];
    for (int i(0); i < Size; i++)
        Matrix[i] = new int[Size];

    for (int i(0); i < Size; i++)
        for (int j(0); j < Size; j++)
            Matrix[i][j] = 0;

    while (v != nullptr)
    {
        Matrix[r->info][c->info] = v->info;
        v = v->next; c = c->next; r = r->next;
    }
    for (int i(0); i < Size; i++) {
        for (int j(0); j < Size; j++)
            cout << Matrix[i][j]; cout << endl;

    }system("pause");
}
void multiply(NodeList& values1, NodeList& rows1, NodeList& columns1, NodeList& values2, NodeList& rows2, NodeList& columns2) {
    NodeList values, rows, columns;
    index_List my1, my2;
    my1.to_index_rows_list(values1, rows1, columns1);
    my2.to_index_columns_list(values2, rows2, columns2);
    Node* row = my1.first;
    for (; row != nullptr; row = row->down) {
        for (Node* column = my2.first; column != nullptr; column = column->down)
        {

            int temp = check(row->List, column->List);
            if (temp != 0)
            {
                values.add_Last(temp); rows.add_Last(row->x); columns.add_Last(column->x);
            }
        }
    }
    cout << "The values of elements:\t\t";
    values.Print();
    cout << endl << endl;
    cout << "The rows of elements:\t\t";
    rows.Print();
    cout << endl << endl;
    cout << "The columns of elements:\t";
    columns.Print();
    cout << endl << endl;
    system("pause");
}
int check(NODEList* first, NODEList* second) {
    int sum = 0;
    NODE* f = first->head, * s = second->head;
    while (f != nullptr)
    {
        if (f->position == s->position)
        {
            sum += f->value * s->value; f = f->next; if (s->next != nullptr)
                s = s->next;
            else break;
        }
        else if (s->position > f->position)
            f = f->next;
        else {
            if (s->next != nullptr)
                s = s->next;
            else break;
        }

    }
    return sum;
}

void add(NodeList& values1, NodeList& rows1, NodeList& columns1, NodeList& values2, NodeList& rows2, NodeList& columns2) {
    NodeList* values = new NodeList, * rows = new NodeList, * columns = new NodeList;
    node* cv1 = values1.head, * cv2 = values2.head, * cr1 = rows1.head, * cr2 = rows2.head, * cc1 = columns1.head, * cc2 = columns2.head;
    int counter; (columns1.length() < columns2.length() ? counter = columns1.length() : counter = columns2.length());
    while (1)
    {
        if (cc1 == nullptr && cc2 == nullptr) break; else {
            if (cc1->info == cc2->info)
            {
                if (cr1->info == cr2->info)
                {
                    columns->add_Last(cc1->info); cc1 = cc1->next; cc2 = cc2->next; values->add_Last(cv1->info + cv2->info);
                    cv1 = cv1->next; cv2 = cv2->next; rows->add_Last(cr1->info); cr1 = cr1->next; cr2 = cr2->next;
                }
                else if (cr1->info < cr2->info)
                {
                    columns->add_Last(cc1->info); cc1 = cc1->next; values->add_Last(cv1->info);
                    cv1 = cv1->next; rows->add_Last(cr1->info); cr1 = cr1->next;
                }
                else {
                    columns->add_Last(cc2->info); cc2 = cc2->next; values->add_Last(cv2->info);
                    cv2 = cv2->next; rows->add_Last(cr2->info); cr2 = cr2->next;
                }
            }
            else if (cc1->info < cc2->info) {
                columns->add_Last(cc1->info); cc1 = cc1->next; values->add_Last(cv1->info);
                cv1 = cv1->next; rows->add_Last(cr1->info); cr1 = cr1->next;
            }
            else if (cc1->info > cc2->info) {
                columns->add_Last(cc2->info); cc2 = cc2->next; values->add_Last(cv2->info);
                cv2 = cv2->next; rows->add_Last(cr2->info); cr2 = cr2->next;
            }
            if (cc1 == nullptr)
            {
                while (cc2 != nullptr) {
                    values->add_Last(cv2->info); cv2 = cv2->next; rows->add_Last(cr2->info); cr2 = cr2->next;
                    columns->add_Last(cc2->info); cc2 = cc2->next;
                }
            }
            else if (cc2 == nullptr)
            {
                while (cc1 != nullptr) {
                    values->add_Last(cv1->info); cv1 = cv1->next; rows->add_Last(cr1->info); cr1 = cr1->next;
                    columns->add_Last(cc1->info); cc1 = cc1->next;
                }
            }
        }
    }

    cout << "The values of elements:\t\t";
    values->Print();
    cout << endl << endl;
    cout << "The rows of elements:\t\t";
    rows->Print();
    cout << endl << endl;
    cout << "The columns of elements:\t";
    columns->Print();
    cout << endl << endl;
    system("pause");
}
void brief(int** Matrix) {
    Brief* my = new Brief;
    for (int i(0); i < Size; i++)
        for (int j(0); j < Size; j++)
        {
            if (my->first == nullptr) { my->ADD(Matrix[i][j], 1); }
            else {
                if (Matrix[i][j] == my->last->number) { my->last->counter++; }
                else { my->ADD(Matrix[i][j], 1); }
            }
        }
    my->PRINT(); system("pause");
}
void index(int** Matrix, NodeList& values, NodeList& rows, NodeList& columns) {
    NodeList* v = new NodeList, * r = new NodeList, * c = new NodeList;
    for (int j(0); j < Size; j++)
    {
        for (int i(0); i < Size; i++)
        {
            if (Matrix[i][j] != 0)
            {
                v->add_Last(Matrix[i][j]);
                r->add_Last(i); c->add_Last(j);
            }
        }
    }
    values = *v; rows = *r; columns = *c;
    delete(v), delete(r), delete(c);
    cout << "The values of elements:\t\t";
    values.Print();
    cout << endl << endl;
    cout << "The rows of elements:\t\t";
    rows.Print();
    cout << endl << endl;
    cout << "The columns of elements:\t";
    columns.Print();
    cout << endl << endl;
    system("pause");
}
void read(int** First_Matrix, int** Second_Matrix) {
    system("cls");
    int read_answer;
    do {
        read_answer = ReadMenu();
        switch (read_answer) {
        case 0: {
            read_from_file("First_matrix.txt", First_Matrix, Second_Matrix); break; }
        case 1: {
            read_from_file("Second_matrix.txt", First_Matrix, Second_Matrix); break; }
        case 2: break;
        }
    } while (read_answer != 2);
}
void read_from_file(char* s, int** First_Matrix, int** Second_Matrix) {
    FILE* my = fopen(s, "r");
    if (!my) {
        cout << "File not found.\n";
        system("pause");
        return;
    }
    else {
        if (s == "First_matrix.txt")
        {
            for (int i(0); i < Size; i++)
                for (int j(0); j < Size; j++)
                    fscanf(my, "%d", &First_Matrix[i][j]);
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < Size; j++)
                    cout << First_Matrix[i][j];
                cout << endl;
            } system("pause");
        }
        else
        {
            for (int i(0); i < Size; i++)
                for (int j(0); j < Size; j++)
                    fscanf(my, "%d", &Second_Matrix[i][j]);
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < Size; j++)
                    cout << Second_Matrix[i][j];
                cout << endl;
            }
            fclose(my);
            system("pause");
        }
    }
}

int MainMenu() {
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 11) % 11;
        if (key == 0)cout << "---> Read from file" << endl;
        else  cout << "Read from file" << endl;
        if (key == 1) cout << "---> Build connected compressed storage for first matrix" << endl;
        else  cout << "Build connected compressed storage for first matrix" << endl;
        if (key == 2) cout << "---> Build connected compressed storage for second matrix" << endl;
        else  cout << "Build connected compressed storage for second matrix" << endl;
        if (key == 3) cout << "---> Build a series-connected index storage for first matrix" << endl;
        else  cout << "Build a series-connected index storage for first matrix" << endl;
        if (key == 4) cout << "---> Build a series-connected index storage for second matrix" << endl;
        else  cout << "Build a series-connected index storage for second matrix" << endl;
        if (key == 5) cout << "---> Print first matrix from index storage" << endl;
        else  cout << "Print first matrix from index storage" << endl;
        if (key == 6) cout << "---> Print second matrix from index storage" << endl;
        else  cout << "Print second matrix from index storage" << endl;
        if (key == 7) cout << "---> Add matrix" << endl;
        else  cout << "Add matrix" << endl;
        if (key == 8) cout << "---> Multiply" << endl;
        else  cout << "Multiply" << endl;
        if (key == 9) cout << "---> Compress file" << endl;
        else  cout << "Compress file" << endl;
        if (key == 10) cout << "---> Exit" << endl;
        else  cout << "Exit" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}
int ReadMenu() {
    int key = 0;
    int code;
    do {
        system("cls");
        key = (key + 3) % 3;
        if (key == 0)cout << "---> Show my first matrix" << endl;
        else  cout << "Show my first matrix" << endl;
        if (key == 1) cout << "---> Show my second matrix" << endl;
        else  cout << "Show my second matrix" << endl;
        if (key == 2) cout << "---> Exit" << endl;
        else  cout << "Exit" << endl;
        code = _getch();
        if (code == 224)
        {
            code = _getch();
            if (code == 80) key++;
            if (code == 72) key--;
        }
    } while (code != 13);
    system("cls");
    return key;
}

sym* makeTree(sym* psym[], int k)//ðeêóðñèâíàÿ ôóíêöèÿ ñîçäàíèÿ äåðåâà Õîôìàíà
{
    sym* temp;
    temp = (sym*)malloc(sizeof(sym));
    temp->freq = psym[k - 1]->freq + psym[k - 2]->freq;
    temp->code[0] = 0;
    temp->left = psym[k - 1];
    temp->right = psym[k - 2];
    if (k == 2)
        return temp;
    else //âíåñåíèå â ìàññèâ â íóæíîå ìåñòî ýëåìåíòà äåðåâà Õàôìàíà
    {
        for (int i = 0; i < k; i++)
            if (temp->freq > psym[i]->freq)
            {
                for (int j = k - 1; j > i; j--)
                    psym[j] = psym[j - 1];

                psym[i] = temp;
                break;
            }
    }
    return makeTree(psym, k - 1);
}

void makeCodes(sym* root)//Ðåêóðñèâíàÿ ôóíêöèÿ êîäèðîâàíèÿ
{
    if (root->left)
    {
        strcpy(root->left->code, root->code);
        strcat(root->left->code, "0");
        makeCodes(root->left);
    }
    if (root->right)
    {
        strcpy(root->right->code, root->code);
        strcat(root->right->code, "1");
        makeCodes(root->right);
    }
}