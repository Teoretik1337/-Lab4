#include <iostream>
#include "Tree.h"

int main()
{
	{
		Tree tr;
		int mas[11] = {
			20, 10, 9, 6, 5, 7, 15, 13, 16, 23, 25
		};
		tr.AddMas(mas, 11);
		tr.Show();
		tr.conditionStart();
		system("pause");
	}
	{
		system("cls");
		Tree tr;
		int mas[21] = {
			30, 20, 10, 9, 6, 5, 7, 15, 13, 16, 23, 25, 40, 35, 41, 45, 42, 43, 47, 48, 50
		};
		tr.AddMas(mas, 21);
		tr.Show();
		tr.conditionStart();
	}

	system("pause");
	return 0;
}