#include"file.h"
#include<stdio.h>
#include<Windows.h>
#include<cstdlib>
void read_file(int* max)
{
	FILE* fp;
	int eer = fopen_s(&fp, "./memory.txt", "r");
	if (eer) return;
	fscanf_s(fp, "%d",max);
	fclose(fp);
}
void write_file(int* max)
{
	FILE* fp;
	int eer = fopen_s(&fp, "./memory.txt", "w");
	if (eer) return;
	fprintf(fp, "%d", *max);
	fclose(fp);
}