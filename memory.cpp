//memory.cpp
#include"bi_tree.h"
#include"memory.h"
#include<cstdio>
#include<iostream>
#include<Windows.h>
using namespace std;
int read(void)
{
	int k;
	char ch;
	print(head);
	printf("ÇÃ»÷B/b·µ»Ø£º");
	while (TRUE) {
		if (scanf_s("%c", &ch, 1) != 1)
			k=getchar();
		if (ch == 'b' || ch == 'B') {
			system("cls");
			return 0;
		}
	}
}