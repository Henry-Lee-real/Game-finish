/*#include"link.h"
#include<cstdio>
#include<cstdlib>
#include<Windows.h>
rank_node* Read_name(rank_node** head, char a[])
{
	rank_node* pp = *head;
	rank_node* p = (rank_node*)malloc(sizeof(rank_node));
	rank_node* pc = *head;
	while (pc != NULL) {
		if (strcmp(pc->nam, a) == 0)
			return pc;
		pc = pc->next;
	}
	while (pp != NULL) {
		pp = pp->next;
	}
	pp = p;
	int pos = 0;
	while (a[pos] != '\0') {
		p->nam[pos] = a[pos];
	}
	p->nam[pos] = '\0';
	p->next = NULL;
	p->num = NULL;
	while (pp->next != NULL) {
		pp = pp->next;
	}
	pp->next = p;
	p->next = NULL;
	return p;
}
rank_node* Search_rank(rank_node* head, char a[])
{
	int pan = 0;
	rank_node* p = head;
	while (p != NULL) {
		if (strcmp(p->nam, a) == 0) {
			pan = 1;
			break;
		}
		p = p->next;
	}
	if (pan == 0)
		return NULL;
	return p;
}
void Read_number(rank_node* p, int num)
{
	if (p->num == NULL)
		p->num = num;
	else {
		if (p->num > num)
			p->num = num;
	}
}
char* Put_name(rank_node* p)
{
	return p->nam;
}*/