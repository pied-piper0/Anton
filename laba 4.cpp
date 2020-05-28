#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>

int const Size = 100;
using namespace std;

struct node 
{
	string info;
	int number;
	bool flag = false;
	node* right = nullptr;
	node* left = nullptr;
};

void Create_array(string* arr, int& arr_counter, char* original);

void derivate(node* node);

bool IS_Oper(string current);

bool IS_Func(string current);

void IS_Brackets(string current);

int Prior(string current);

void graph(node* node, FILE* my);

void viz(node* node, FILE* my);

node* Create_node(string information);

node* Prefix_form(string* arr, int arr_counter);

void solve(stack<node*>& nodes, stack<node*>& oper);

double evaluateTree(node* node, double x);

int index = 0;

int main()
{
	int counter = 0;
	char* original = new char[Size];
	cin.getline(original, Size);
	cin.ignore();
	string* arr = new string[strlen(original)];
	Create_array(arr, counter, original);
	node* ExpressionTree = Prefix_form(arr, counter);
	FILE* f = fopen("expression.txt", "w");
	viz(ExpressionTree, f);
	fclose(f);
	double x;
	cout << "\t\t\t\t\tx= ";
	cin >> x;
	double result = evaluateTree(ExpressionTree, x);
	cout << "Result = " << result << endl;
	derivate(ExpressionTree);
	FILE* f1 = fopen("d_expression.txt", "w");
	viz(ExpressionTree, f1);
	fclose(f1);
	double y;
	cout << "\t\t\t\t\tx= ";
	cin >> y; cout << endl;
	double result1 = evaluateTree(ExpressionTree, y);
	cout << "Derivate result= " << result1 << endl;
	return 0;
}

bool IS_Oper(string current)
{
	if (current == "^" || current == "-" || current == "*" || current == "/" || current == "+") return true; else return false;
}

bool IS_Func(string current)
{
	if (current == "sin" || current == "cos" || current == "log") return true; else return false;
}

bool IS_Brackets(string current)
{
	if (current == "(" || current == ")")return true; else return false;
}

void Create_array(string* arr, int& arr_counter, char* original) 
{
	string piece, help = ""; arr_counter = 0;
	for (int i = 0; i < strlen(original); i++)
	{
		piece = original[i];
		if (IS_Oper(piece) || IS_Brackets(piece)) 
		{
			if (help != "") 
			{
				arr[arr_counter] = help;
				arr_counter++;
				help = "";
			}
			arr[arr_counter] = piece;
			arr_counter++;
			help = "";
		}
		else
			if (piece != "") 
			{
				if (piece != " ")help.append(piece);
				else
				{
					arr[arr_counter] = help;
					arr_counter++;
					help = "";
				}
			}
			else
				if (help != "") 
				{
					arr[arr_counter] = help;
					arr_counter++;
					help = "";
				}
	}
	if (help != "") arr[arr_counter++] = help; help = "";
}

int Prior(string current) 
{
	if (current == "+" || current == "-")return 1; else
		if (current == "*" || current == "/")return 2; else
			if (current == "^") return 3;
			else return 0;
}

node* Prefix_form(string* arr, int arr_counter) 
{
	stack<node*> operators;
	stack<node*> treenodes;
	string token;
	for (int i = 0; i < arr_counter; i++) 
	{
		token = arr[i];
		if (IS_Oper(token) || IS_Func(token))
		{
			if (!(operators.empty()))
			{
				while (((IS_Func(operators.top()->info)) || (Prior(operators.top()->info) >= Prior(token))) && (operators.top()->info != "("))
				{
					solve(treenodes, operators);
					if (operators.empty()) break;
				}
			}
			operators.push(Create_node(token));
		}
		else if (token == "(") operators.push(Create_node(token));
		else if (token == ")")
		{
			while (operators.top()->info != "(") 
			{
				solve(treenodes, operators);
				if (operators.empty()) break;
			}
			if (!operators.empty()) operators.pop();
			else break;
		}
		else treenodes.push(Create_node(token));
	}

	while (!operators.empty())
	{
		if (IS_Brackets(operators.top()->info))
			break;
		solve(treenodes, operators);
	}
	return treenodes.top();
}

node* Create_node(string info) 
{
	node* current = new node();
	current->info = info; current->number = index++;
	current->right = NULL; current->left = NULL;
	return current;
}

void solve(stack<node*>& nodes, stack<node*>& oper)
{
	node* current = oper.top();
	if (oper.top()->info == "sin" || oper.top()->info == "cos" || oper.top()->info == "log") 
	{
		oper.pop();
		current->right = nodes.top();
		nodes.pop();
		current->left = NULL;
		nodes.push(current);
	}
	else
	{
		oper.pop();
		current->right = nodes.top();
		nodes.pop();
		current->left = nodes.top();
		nodes.pop();
		nodes.push(current);
	}
}

double evaluateTree(node* node, double x)
{
	double left, right, res;
	if (IS_Oper(node->info))
	{
		left = evaluateTree(node->left, x);
		right = evaluateTree(node->right, x);
		if (node->info == "+")
			res = left + right;
		else if (node->info == "-")
			res = left - right;
		else if (node->info == "*")
			res = left * right;
		else if (node->info == "/")
			res = left / right;
		else if (node->info == "^")
			res = pow(left, right);
		return res;
	}
	else if (IS_Func(node->info))
	{
		if (node->info == "sin") 
		{
			right = evaluateTree(node->right, x);
			res = sin(right);
			return res;
		}
		else if (node->info == "cos")
		{
			right = evaluateTree(node->right, x);
			res = cos(right);
			return res;
		}
		else if (node->info == "log") 
		{
			right = evaluateTree(node->right, x);
			res = log(right);
			return res;
		}
	}
	else 
	{
		if (node->info == "x")
			return x;
		else 
		{
			return atoi(node->info.c_str());
		}
	}
}

void graph(node* node, FILE* my)
{
	static int nullcount = 0;
	if (node->left)
	{
		fprintf(my, "%d [label=\"%s\"];\n", node->number, node->info.c_str());
		fprintf(my, "%d -> %d;\n", node->number, node->left->number);
		graph(node->left, my);
	}
	else
	{
		nullcount++;
		fprintf(my, "null%d [shape=point];\n", nullcount);
		fprintf(my, "%d [label=\"%s\"];\n", node->number, node->info.c_str());
		fprintf(my, "%d -> null%d;\n", node->number, nullcount);
	}

	if (node->right)
	{
		fprintf(my, "%d [label=\"%s\"];\n", node->number, node->info.c_str());
		fprintf(my, "%d -> %d;\n", node->number, node->right->number);
		graph(node->right, my);
	}
	else
	{
		nullcount++;
		fprintf(my, "null%d [shape=point];\n", nullcount);
		fprintf(my, "%d [label=\"%s\"];\n", node->number, node->info.c_str());
		fprintf(my, "%d -> null%d;\n", node->number, nullcount);
	}
}

void viz(node* node, FILE* my)
{
	fprintf(my, "digraph \"GRAPH\"{\n");
	if (node == NULL)
		fprintf(my, "\n");
	else if (!node->right && !node->left)
	{
		fprintf(my, "%d [label=\"%s\"];\n", 0, node->info.c_str());
		fprintf(my, "null%d [shape=point];\n", 0);
		fprintf(my, "null%d [shape=point];\n", 1);
		fprintf(my, "%d -> null%d;\n", 0, 1);
		fprintf(my, "%d -> null%d;\n", 0, 0);
	}
	else
		graph(node, my);

	fprintf(my, "}\n");
}

void derivate(node* Node)
{
	if (!Node) return;
	else if (Node->left == NULL && Node->right == NULL && Node->number == 0) { Node->info = "0"; Node->flag = true; }
	else
		derivate(Node->left);
	{
		if (Node->info == "log" && Node->flag == false)
		{
			Node->info = "/";
			delete(Node->left);
			Node->left = new node;
			Node->left->number = ++index;
			Node->left->info = "1";
			Node->flag = true;
			Node->right->flag = true;
		}
		else if (Node->info == "sin" && Node->flag == false)
		{
			Node->info = "cos";
			Node->flag = true;
			Node->right->flag = true;
		}
		else if (Node->info == "*" && Node->flag == false)
		{
			if (Node->right->info == "x" && Node->left->info != "x")
			{
				Node->info = Node->left->info;
				delete(Node->left);
				delete(Node->right);
				Node->left = NULL;
				Node->right = NULL;
			}
			else if (Node->left->info == "x" && Node->right->info != "x")
			{
				Node->info = Node->right->info;
				delete(Node->left);
				delete(Node->right);
				Node->left = NULL;
				Node->right = NULL;

			}
			else if (Node->left->info != "x" && Node->right->info != "x")
			{
				Node->info = "0";
				delete(Node->left);
				delete(Node->right);
				Node->left = NULL;
				Node->right = NULL;

			}
			Node->flag = true;
		}
		else if (Node->info == "cos" && Node->flag == false)
		{
			node* temp = new node;
			temp->number = ++index;
			temp->right = Node->right;
			temp->info = "sin";
			Node->info = "-";
			Node->number = ++index;
			delete(Node->left);
			Node->left = new node;
			Node->left->number = ++index;
			Node->left->info = "0";
			Node->right = temp;
			Node->flag = true;
			Node->right->flag = true;
			Node->right->right->flag = true;
		}
		else if (Node->info == "^" && Node->flag == false)
		{
			if (Node->left->info != "x" && Node->right->info != "x")
			{
				Node->info = "0";
				delete(Node->left);
				delete(Node->right);
				Node->left = NULL;
				Node->right = NULL;
				Node->flag = true;
			}
			else {
				node* temp = new node;
				Node->left->info = Node->right->info;
				temp->number = ++index;
				temp->left = new node;
				temp->left->number = ++index;
				temp->left->info = "x";
				temp->right = Node->right;
				temp->right->info = to_string(atoi(Node->right->info.c_str()) - 1);
				temp->info = "^";
				Node->info = "*";
				Node->right = temp;
				Node->flag = true;
				Node->right->flag = true;
				Node->right->left->flag = true;
			}
		}
		else if ((Node->info == "+" || Node->info == "-") && Node->flag == false)
		{
			if (Node->left->info == "x" && Node->right->info == "x")
			{
				Node->left->info = "1"; Node->right->info = "1"; Node->left->flag = true; Node->right->flag = true; Node->flag = true;
			}
			else if (Node->left->info == "x" && (IS_Func(Node->right->info) || IS_Oper(Node->right->info)))
			{
				Node->left->info = "1"; Node->left->flag = true; Node->flag = true;
			}
			else if (Node->right->info == "x" && (IS_Func(Node->left->info) || IS_Oper(Node->left->info)))
			{
				Node->right->info = "1"; Node->right->flag = true; Node->flag = true;
			}
			else if ((!(IS_Func(Node->right->info))) && (!(IS_Oper(Node->right->info))) && (Node->right->info != "x") && (IS_Func(Node->left->info) || IS_Oper(Node->left->info)))
			{
				Node->right->info = "0"; Node->right->flag = true; Node->flag = true;
			}
			else if ((!(IS_Func(Node->left->info))) && (!(IS_Oper(Node->left->info))) && (Node->left->info != "x") && (IS_Func(Node->right->info) || IS_Oper(Node->right->info)))
			{
				Node->left->info = "0"; Node->left->flag = true; Node->flag = true;
			}
			else if ((IS_Func(Node->right->info) || IS_Oper(Node->right->info)) && (IS_Func(Node->left->info) || IS_Oper(Node->left->info)))
			{
				Node->flag = true;
			}
			else if (Node->left->info == "x" && ((!(IS_Func(Node->right->info))) && (!(IS_Oper(Node->right->info))) && (Node->right->info != "x")))
			{
				Node->left->info = "1"; Node->right->info = "0"; Node->flag = true;
			}
			else if (Node->right->info == "x" && ((!(IS_Func(Node->left->info))) && (!(IS_Oper(Node->left->info))) && (Node->left->info != "x")))
			{
				Node->right->info = "1"; Node->left->info = "0"; Node->flag = true;
			}
			else if (((!(IS_Func(Node->left->info))) && (!(IS_Oper(Node->left->info))) && (Node->left->info != "x")) && ((!(IS_Func(Node->right->info))) && (!(IS_Oper(Node->right->info))) && (Node->right->info != "x")))
				Node->left->info = "0"; Node->right->info = "0"; Node->flag = true;
		}

		derivate(Node->right);
	}
}