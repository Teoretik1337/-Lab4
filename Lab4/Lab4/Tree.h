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

	void Add(int value); //���������� ������ ��������
	void AddMas(int *Mas, int count); //���������� ������� ���������
	void Show(); //�������� ������
	void nodeRoman(); //���� ����������
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

	void AddHelp(Node *tmpN, Node *node, int value); //����� ������ ��� ���������� Add()
	void print_tree(Node *p, int level); //����� ������ ��� Show() 
	void recNodeRoman(Node *verNode, int &quant);
	void recFindNodeRoman(Node *verNode);

	void recCondition(Node *verNode, Node *tmpNode, int *quant);
	void condition(Node *verNode);

};

void Tree::Add(int value) //�������� �������
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

void Tree::AddMas(int * Mas, int count) // �������� ������ ���������
{
	for (int i = 0; i < count; i++)
	{
		Add(Mas[i]);
	}
}

void Tree::AddHelp(Node *tmpN, Node *node, int value) // ����� ������ ��� ���������� ��������� (��������)
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

void Tree::Show() //�������� ������
{
	Node *nodeT = _root;
	print_tree(nodeT, 0);
}

void Tree::print_tree(Node *p, int level) //����������� ����� ������
{
	if (p)
	{
		print_tree(p->right, level + 1);     // ����� ������ ���������
		for (int i = 0; i < level; i++)
		{
			printf("   ");
		}
		printf("%i\n", p->x);               // ����� ����� ���������
		print_tree(p->left, level + 1);    // ����� ������ ���������
	}
}

void Tree::nodeRoman() //������ �������� �����
{
	recFindNodeRoman(_root); //�������� ������ � ������� ����
}

void Tree::recFindNodeRoman(Node *verNode) //���������� ��� ���� (��������)
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
		verNode->romansk = true; //���� ���� ���������, �� ���
	}

	if (verNode->left) //���������� ��� ���� �����
	{
		recFindNodeRoman(verNode->left);
	}
	if (verNode->right) //���������� ��� ���� ������
	{
		recFindNodeRoman(verNode->right);
	}
}

void Tree::recNodeRoman(Node *verNode, int &quant) //������ ������� ����� � ����� (��������)
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

void Tree::conditionStart() //����� �������� �������
{
	nodeRoman(); //����  ��� ���� ����������
	condition(_root); //��������� �������� ��������
}

void Tree::condition(Node *verNode) //���������� ��� ���� ��� ��������
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

	if (verNode->left) //���������� ��� ���� �����
	{
		condition(verNode->left);
	}
	if (verNode->right) //���������� ��� ���� ������
	{
		condition(verNode->right);
	}
}

void Tree::recCondition(Node *verNode, Node *tmpNode, int *quant) //���������� ��� ���������� �����
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
