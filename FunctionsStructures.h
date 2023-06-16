#ifndef FUNCTIONSSTRUCTURES_H
#define FUNCTIONSSTRUCTURES_H

#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE 30

template <class XType>
class Stack				
{
public:
	Stack();
	~Stack();
	bool is_empty() const;
	bool is_full() const;
	void push(XType);
	void pop();
	XType top() const;
	int size() const;

private:
	XType elements[MAX_SIZE];
	int Tos;
};

template <class XType>
Stack<XType>::Stack()
{
	Tos = 0;
}

template <class XType>
Stack<XType>::~Stack()
{
	Tos = 0;
}

template <class XType>
bool Stack<XType>::is_empty() const
{
	return (Tos == 0);
}

template <class XType>
bool Stack<XType>::is_full() const
{
	return (Tos == MAX_SIZE);
}

template <class XType>
int Stack<XType>::size() const
{
	return Tos;
}

template <class XType>
void Stack<XType>::push(XType item)
{
	if (!this->is_full())
	{
		elements[Tos] = item;
		Tos++;
	}
}

template <class XType>
void Stack<XType>::pop()
{
	if (!this->is_full())
	{
		Tos--;
	}
}

template <class XType>
XType Stack<XType>::top() const
{
	if (!this->is_empty())
	{
		return (elements[Tos - 1]);
	}
}

struct TreeNode						
{
	char value;
	TreeNode* left;
	TreeNode* right;
};
typedef TreeNode* treeNodePtr;








class origStack		
{
private:
	struct Stack_Node
	{
		char stackValue;
		Stack_Node* next;

	};

	typedef Stack_Node* stackPtr;
	stackPtr Tos;					
	int s_size;						

public:
	origStack()
	{
		s_size = 0;
		Tos = nullptr;
	}

	~origStack()
	{
		s_size = 0;
		Tos = nullptr;
	}

	bool isEmpty() const
	{
		return (s_size == 0 && Tos == nullptr);
	}

	int size() const
	{
		return s_size;
	}

	void push(char item)
	{
		stackPtr sPtr = new Stack_Node;

		sPtr->stackValue = item;
		sPtr->next = Tos;
		Tos = sPtr;
		s_size++;
	}

	void pop()
	{
		if (!this->isEmpty())
		{
			Tos = Tos->next;
			s_size--;
		}
	}

	char top() const
	{
		if (!this->isEmpty())
			return Tos->stackValue;
	}
};


//List for integers
struct IntNode
{
	int num;
	IntNode* next;
};
typedef IntNode* IntNodePtr;
IntNodePtr intHead;

//List/BT
struct ETNode
{
	char op;	
	ETNode* left;
	ETNode* right;
};
typedef ETNode* ETPtr;
ETPtr root;					


//*****************************************************
//	Function Prototypes for the main program		  *
//*****************************************************

string validInfix(string);
int checkPrecedence(char);
string convertToPostfix(string, origStack&);
void connect(origStack, ETNode);
bool isOperator(char);
int evaluateExpression(origStack);
origStack stringToStack(string);
string stackToString(origStack s);
int convertToBase36(int);
string reverseString(string);
int alphaToNumeric(char);
char numericToAlpha(int);

template <class XType> XType buildExpressionTree(string);
template <class XType> void printPreorder(XType);
template <class XType> void printInorder(XType);
template <class XType> void printPostorder(XType);

int menu(string);	//create a two-level menu system with 3 choices
int menuOp1(string);
int menuOp2(string);



//*****************************************************
//	Functions for the main program					  *
//*****************************************************


//-------------------------------------------------------------
// Displays the Main Menu options
// 
// @param - string
// @return - int
//-------------------------------------------------------------

int menu(string str)
{
	int choice;
	string infix;
	origStack stack1;

	cout << "0. Quit.\n";
	cout << "1. Input an infix expression\n";
	cout << "2. Input a postfix expression\n";

	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;

	while (choice < 0 || choice > 2)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choice;
		cout << endl;
	}

	switch (choice)
	{
	case 0:
		return 0;
		break;
	case 1:
		cout << "Please enter an Infix expression: ";
		cin >> infix;
		cout << endl;
		infix = validInfix(infix);
		str = convertToPostfix(infix, stack1);

		menuOp1(str);
		do
		{
			choice = menu(str);
		} while (choice != 0);
		break;
	case 2:
		cout << "Please enter a Postfix expression: ";
		cin >> str;	//validate the postfix expression
		cout << endl;

		menuOp2(str);
		do
		{
			choice = menu(str);
		} while (choice != 0);
		break;
	}

	return choice;
}


//-------------------------------------------------------------
// Displays the Menu1 options
// 
// @param - string
// @return - int
//-------------------------------------------------------------

int menuOp1(string str)
{
	//Menu 1 selection
	int choice, display;

	cout << "0. Return to previous menu.\n";
	cout << "1. Print postfix expression only.\n";
	cout << "2. Print postfix expression, and print the preorder, inorder, and postorder of ";
	cout << "the expression tree, and the final expression value in base BOTH base 10 and base 36.\n";

	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;

	while (choice < 0 || choice > 2)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choice;
		cout << endl;
	}

	switch (choice)
	{
	case 0:
		return 0;
	case 1:
		cout << "Postfix Expression: " << str << endl << endl;
		break;
	case 2:
		cout << "Postfix Expression: " << str << endl;

		cout << "PreOrder: ";
		printPreorder(buildExpressionTree<treeNodePtr>(str)); 
		cout << endl;
		cout << "InOrder: ";
		printInorder(buildExpressionTree<treeNodePtr>(str)); 
		cout << endl;
		cout << "PostOrder: ";
		printPostorder(buildExpressionTree<treeNodePtr>(str)); 
		cout << endl;

		display = evaluateExpression(stringToStack(str));
		cout << "Base 10: " << display << endl;
		cout << "Base 36: " << convertToBase36(display);
		cout << endl << endl;

		break;
	}

	return choice;
}


//-------------------------------------------------------------
// Displays the Menu2 options
// 
// @param - string
// @return - int
//-------------------------------------------------------------


int menuOp2(string str)
{
	//Menu 2 selection

	int choice, display;

	cout << "0. Return to previous menu.\n";
	cout << "1. Print the final expression value ONLY and BOTH base 10 and base 36.\n";
	cout << "2. Print the preorder, inorder and postorder of the expression tree and the ";
	cout << "expression value in base 10 and base 36.\n";

	cout << "Please enter your choice: ";
	cin >> choice;
	cout << endl;

	while (choice < 0 || choice > 2)
	{
		cout << "Please enter a valid menu choice: ";
		cin >> choice;
		cout << endl;
	}

	switch (choice)
	{
	case 0:
		return 0;
	case 1:
		display = evaluateExpression(stringToStack(str));
		cout << "Base 10: " << display << endl;
		cout << "Base 36: " << convertToBase36(display);
		cout << endl << endl;
		break;
	case 2:
		cout << "PreOrder: ";
		printPreorder(buildExpressionTree<treeNodePtr>(str));
		cout << endl;
		cout << "InOrder: ";
		printInorder(buildExpressionTree<treeNodePtr>(str));
		cout << endl;
		cout << "PostOrder: ";
		printPostorder(buildExpressionTree<treeNodePtr>(str));
		cout << endl;

		display = evaluateExpression(stringToStack(str));
		cout << "Base 10: " << display << endl;
		cout << "Base 36: " << convertToBase36(display);
		cout << endl << endl;
		break;
	}
	return choice;
}


//-------------------------------------------------------------
// Prints the preorder traversal of a given root of a tree
// 
// @param - treeNodePtr
// @return - void
//-------------------------------------------------------------

template <class XType>
void printPreorder(XType t)
{
	if (t == nullptr)
	{
		cout << ".";
		return;
	}
	else
	{
		cout << t->value;
		printPreorder(t->left);
		printPreorder(t->right);
	}
}


//-------------------------------------------------------------
// Displays the inorder traversal of a given tree root.
// 
// @param - treeNodePtr
// @return - void
//-------------------------------------------------------------

template <class XType>
void printInorder(XType t)
{
	if (t == nullptr)
	{
		cout << ".";
		return;
	}
	else
	{
		printInorder(t->left);
		cout << t->value;
		printInorder(t->right);
	}
}


//-------------------------------------------------------------
// Displays the postorder traversal of a given tree root
// 
// @param - treeNodePtr
// @return - void
//-------------------------------------------------------------


template <class XType>
void printPostorder(XType t)
{
	if (t == nullptr)
	{
		cout << ".";
		return;
	}
	else
	{
		printPostorder(t->left);
		printPostorder(t->right);
		cout << t->value;
	}
}

//-------------------------------------------------------------
// Builds an expression tree with a given postfix expression
// and returns a pointer to the root node
// 
// @param - string
// @return - treeNodePtr
//-------------------------------------------------------------


template <class XType>
XType buildExpressionTree(string str)	//returns the root of the expression tree
{
	Stack<treeNodePtr> stack1;

	for (int i = 0; i < str.length(); i++)
	{
		if (!isOperator(str[i]))
		{
			treeNodePtr node = new TreeNode;
			node->value = str[i];
			node->left = node->right = nullptr;
			stack1.push(node);
		}
		else
		{
			treeNodePtr node = new TreeNode;
			node->value = str[i];
			node->right = stack1.top();
			stack1.pop();
			node->left = stack1.top();
			stack1.pop();
			stack1.push(node);	
		}
	}
	return stack1.top();
}

//-------------------------------------------------------------
// Converts alphabet to base 36 and numeric chars to integers
// 
// @param - char
// @return - int
//-------------------------------------------------------------


int alphaToNumeric(char ch)
{
	if (isalpha(ch))
	{
		return ch - '6';
	}
	else
	{
		return ch - '0';
	}
}

//-------------------------------------------------------------
// Converts numeric chars to alphabet
// 
// @param - int
// @return - char
//-------------------------------------------------------------


char numericToAlpha(int num)
{
	int temp = 64;

	for (int i = 9; i < num; i++)
	{
		temp += 1;
	}

	char ch = temp;
	return ch;
}


//-------------------------------------------------------------
// Reverses a given string
// 
// @param - string
// @return - string
//-------------------------------------------------------------


string reverseString(string str)
{
	string temp;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		temp += str[i];
	}

	return temp;
}

//-------------------------------------------------------------
// Converts the base 10 into base 36
// 
// @param - int
// @return - int
//-------------------------------------------------------------


int convertToBase36(int num10)
{
	string str36;
	int result = 0;
	if (num10 > 9)
	{
		while (num10 > 0)
		{
			result = num10 % 36;
			num10 = num10 / 36;
			if (result > 9)	//what if remainder is greater than 9?
			{

			}
			else
			{
				str36 += to_string(result);
			}
		}

		str36 = reverseString(str36);
		int num = stoi(str36);

		return num;
	}
	else
	{
		return num10;
	}
}

//-------------------------------------------------------------
// Validates the infix expression given.
// 
// @param - string
// @return - string
//-------------------------------------------------------------


string validInfix(string str)
{
	return str;
	for (int i = 0; i < str.length(); i++)
	{
		if (!isalpha(str[i]) && !isOperator(str[i]) && !isdigit(str[i]))
		{
			cout << "Please input a correct Infix Expression: ";
			cin >> str;
			return validInfix(str);
		}
	}


	for (int i = 0; i < str.length() - 1; i++)
	{
		if ((isalpha(str[i]) && isalpha(str[i + 1])) || (isOperator(str[i]) && isOperator(str[i + 1])) 
			|| (isdigit(str[i]) && isdigit(str[i + 1])))
		{
			cout << "Please input a correct Infix Expression: ";
			cin >> str;
			return validInfix(str);
		}

		if (isalpha(str[i]))
		{
			if (!isupper(str[i]))
			{
				cout << "Please input a correct Infix Expression: ";
				cin >> str;
				return validInfix(str);
			}
		}
	}


	//validate parenthesis
	origStack pStack;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			pStack.push(str[i]);
		}
		else if (str[i] == ')' && pStack.top() != '(')
		{
			cout << "Please input a correct Infix Expression: ";
			cin >> str;
			return validInfix(str);
		}
		else if (str[i] == ')')
		{
			pStack.pop();
		}
	}
	return str;
}

//-------------------------------------------------------------
// Converts a given string into a postfix expression
// 
// @param - string, Stack
// @return - string
//-------------------------------------------------------------


string convertToPostfix(string infixStr, origStack& stack1) 
{
	int i = 0;
	string output;
	while (i < infixStr.size())
	{
		if (infixStr[i] == ' ')
		{
			i++;
		}

		if (infixStr[i] == '(')
		{
			stack1.push(infixStr[i]);
		}

		else if (infixStr[i] == ')')
		{
			while (stack1.top() != '(')
			{
				output += stack1.top();
				stack1.pop();
			}
			stack1.pop();
		}

		else if (infixStr[i] == '+' || infixStr[i] == '-' || infixStr[i] == '*' || infixStr[i] == '/')
		{
			if (stack1.isEmpty())
			{
				stack1.push(infixStr[i]);
			}
			else
			{
				if (checkPrecedence(stack1.top()) >= checkPrecedence(infixStr[i]))
				{
					output += stack1.top();
					stack1.pop();
					stack1.push(infixStr[i]);
				}
				else
				{
					stack1.push(infixStr[i]);
				}
			}
		}

		else
		{
			output += infixStr[i];
		}
		i++;			
	}

	if (!stack1.isEmpty())
	{
		while (!stack1.isEmpty())
		{
			output += stack1.top();
			stack1.pop();
		}
	}

	return output;
}

//-------------------------------------------------------------
// Converts a given string into a stack
// 
// @param - string
// @return - Stack
//-------------------------------------------------------------


origStack stringToStack(string str)
{
	origStack stack1;
	for (int i = 0; i < str.length(); i++)
	{
		stack1.push(str[i]);
	}

	return stack1;
}

//-------------------------------------------------------------
// Checks the precedence of the operator character given
// 
// @param - char
// @return - int
//-------------------------------------------------------------


int checkPrecedence(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	else if (ch == '*' || ch == '/')
		return 2;
	else
		return 0;
}

//-------------------------------------------------------------
// checks if the given character is an operator char
// 
// @param - char
// @return - bool
//-------------------------------------------------------------


bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}

//-------------------------------------------------------------
// Evaluates the given stack and returns the integer result
// 
// @param - Stack
// @return - int
//-------------------------------------------------------------


int evaluateExpression(origStack s)
{
	string str = stackToString(s);
	//origStack stack1;
	intHead = nullptr;
	IntNodePtr tPtr = intHead;

	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]) || isalpha(str[i]))
		{
				tPtr = new IntNode;
				tPtr->num = alphaToNumeric(str[i]);
				tPtr->next = intHead;
				intHead = tPtr;
		}
		else
		{
			int num1 = tPtr->num;
			intHead = tPtr = tPtr->next;
			int num2 = tPtr->num;
			intHead = tPtr = tPtr->next;

			switch (str[i])
			{
			case '+':
				tPtr = new IntNode;
				tPtr->num = (num2 + num1);
				tPtr->next = intHead;
				intHead = tPtr;
				break;
			case '-':
				tPtr = new IntNode;
				tPtr->num = (num2 - num1);
				tPtr->next = intHead;
				intHead = tPtr;
				break;
			case '*':
				tPtr = new IntNode;
				tPtr->num = (num2 * num1);
				tPtr->next = intHead;
				intHead = tPtr;
				break;
			case '/':
				tPtr = new IntNode;
				tPtr->num = (num2 / num1); //don't divide by 0
				tPtr->next = intHead;
				intHead = tPtr;
				break;
			}
		}
	}
	return tPtr->num;
}

//-------------------------------------------------------------
// Converts a stack to a string
// 
// @param - Stack
// @return - string
//-------------------------------------------------------------


string stackToString(origStack s)
{
	string str;

	while (!s.isEmpty())
	{
		str += s.top();
		s.pop();
	}

	return reverseString(str);
}


#endif