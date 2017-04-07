#pragma once

#include <iostream>
#include <cmath>

class Tree
{
public:
	Tree()
	{
		_root = NULL;
	};

	void Add(int value); //добавление одного элемента
	void AddMas(int *Mas, int count); //добавление массива элементов
	void Show(); //показать дерево
	void nodeRoman(); //узлы романского
	void conditionStart();

private:
	class Node
	{
	public:
		Node()
		{
			x = NULL;
			left = NULL;
			right = NULL;
			romansk = false;
			countDes = 0;
		}
		int x;
		Node *left, *right;
		bool romansk;
		int countDes;
	};
	Node *_root;

	void AddHelp(Node *tmpN, Node *node, int value); //метод помощи при добавлении Add()
	void print_tree(Node *p, int level); //метод вывода для Show() 
	void recNodeRoman(Node *verNode, int &quant);
	void recFindNodeRoman(Node *verNode);

	void recCondition(Node *verNode, Node *tmpNode, int *quant);
	void condition(Node *verNode);

};

void Tree::Add(int value) //добавить элемент
{
	if (_root == NULL)
	{
		Node *node = new Node;
		node->x = value;
		node->left = NULL;
		node->right = NULL;
		_root = node;
	}
	else
	{
		Node *tmpN = new Node;
		tmpN->x = value;
		Node *node = _root;
		AddHelp(tmpN, node, value);
	}
}

void Tree::AddMas(int * Mas, int count) // добавить массив элементов
{
	for (int i = 0; i < count; i++)
	{
		Add(Mas[i]);
	}
}

void Tree::AddHelp(Node *tmpN, Node *node, int value) // штука нужная для добовления элементов (рекурсия)
{
	if (value > node->x)
	{
		if (node->right == NULL)
		{
			node->right = tmpN;
		}
		else
		{
			AddHelp(tmpN, node->right, value);
		}
	}
	else if (value <= node->x)
	{
		if (node->left == NULL)
		{
			node->left = tmpN;
		}
		else
		{
			AddHelp(tmpN, node->left, value);
		}
	}
}

void Tree::Show() //показать дерево
{
	Node *nodeT = _root;
	print_tree(nodeT, 0);
}

void Tree::print_tree(Node *p, int level) //рекурсивный обход дерева
{
	if (p)
	{
		print_tree(p->right, level + 1);     // вывод левого поддерева
		for (int i = 0; i < level; i++)
		{
			printf("   ");
		}
		printf("%i\n", p->x);               // вывод корня поддерева
		print_tree(p->left, level + 1);    // вывод левого поддерева
	}
}

void Tree::nodeRoman() //запуск проверки узлов
{
	recFindNodeRoman(_root); //начально задаем с первого узла
}

void Tree::recFindNodeRoman(Node *verNode) //перебирает все узлы (рекурсия)
{
	int quantLeft = 0, quantRight = 0;
	if (verNode->left)
	{
		recNodeRoman(verNode->left, quantLeft);
		quantLeft++;
	}
	if (verNode->right)
	{
		recNodeRoman(verNode->right, quantRight);
		quantRight++;
	}

	verNode->countDes = std::abs((quantLeft)+(quantRight));

	if (std::abs((quantLeft)-(quantRight)) < 6)
	{
		verNode->romansk = true; //если узел романский, то тру
	}

	if (verNode->left) //перебераем все узлы слева
	{
		recFindNodeRoman(verNode->left);
	}
	if (verNode->right) //перебераем все узлы справа
	{
		recFindNodeRoman(verNode->right);
	}
}

void Tree::recNodeRoman(Node *verNode, int &quant) //узнаем сколько узлов в ветке (рекурсия)
{
	if (verNode->left)
	{
		quant++;
		recNodeRoman(verNode->left, quant);
	}
	if (verNode->right)
	{
		quant++;
		recNodeRoman(verNode->right, quant);
	}
}

void Tree::conditionStart() //старт проверки условия
{
	nodeRoman(); //ищем  все узлы романского
	condition(_root); //запускаем основную проверку
}

void Tree::condition(Node *verNode) //перебераем все узлы для проверки
{
	int quant = 0;
	Node *tmpNode = verNode;
	/////////////////////////////////////////
	if (verNode->left)
	{
		if (!verNode->romansk)
		{
			quant = -1;
		}
		quant = quant + 1;
		recCondition(verNode->left, tmpNode, &quant);
	}
	if (verNode->right)
	{
		if (!verNode->romansk)
		{
			quant = -1;
		}
		quant = quant + 1;
		recCondition(verNode->right, tmpNode, &quant);
	}
	///////////////////////////////////////////
	//recCondition(verNode, verNode,&quant);

	if ((quant != verNode->countDes) && !(verNode->romansk) && (quant != -1))
	{
		printf("%i - Approaches the condition\n", verNode->x);
	}

	if (verNode->left) //перебераем все узлы слева
	{
		condition(verNode->left);
	}
	if (verNode->right) //перебераем все узлы справа
	{
		condition(verNode->right);
	}
}

void Tree::recCondition(Node *verNode, Node *tmpNode, int *quant) //перебераем все поддеревья узлов
{
	if (verNode->x != tmpNode->x)
	{
		if (verNode->left)
		{
			if (!verNode->romansk)
			{
				*quant = -1;
				return;
			}
			*quant = *quant + 1;
			recCondition(verNode->left, tmpNode, *&quant);
		}
		if (verNode->right)
		{
			if (!verNode->romansk)
			{
				*quant = -1;
				return;
			}
			*quant = *quant + 1;
			recCondition(verNode->right, tmpNode, *&quant);
		}
	}
}
