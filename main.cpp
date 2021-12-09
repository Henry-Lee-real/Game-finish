#include<cstdio>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include<iostream>
#include"home.h"
#include"game.h"
#include"memory.h"
#include"bi_tree.h"
#include"file.h"
using namespace std;
int main()
{
	int max;
	read_file(&max);
	int screen = 0;
	while (TRUE) {
		switch (screen) {
		case 0:
			while (TRUE) {
				screen = main_screen();
				if (screen != 0)
					break;
			}
			break;
		case 1:
			while (TRUE) {
				screen = play_screen();
				if (screen != 1)
					break;
			}
			break;
		case 2:
			printf("历史最高分：%d\n", max);
			screen=read();
			break;
		case 3:
			int k;
			if(max<(k=clean()))
			write_file(&k);
			exit(0);
			return 0;
		}
	}
}