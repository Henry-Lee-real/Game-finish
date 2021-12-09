#include"bi_tree.h"
#include<cstdlib>
#include<cstdio>
#include<string>
link* head = NULL;
link* create_link(void){
	link* p = (link*)malloc(sizeof(link));
	return p;
}
link* insert_link(int num,link *head)
{
	link* p = head;
	if (head == NULL) {
		head = create_link();
		head->num = num;
		head->next = NULL;
		return head;
	}
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = create_link();
	p = p->next;
	p->num = num;
	p->next = NULL;
	return head;
}
void print(link* head)
{
	int n = 1;
	if (head == NULL) {
		printf("None!");
		return;
	}
	link* p = head;
	while (p != NULL) {
		printf("-------------------%d,µÃ·Ö£º%3d-----------------\n", n, p->num);
		n++;
		p = p->next;
	}

}
int clean(void)
{
	int max = 0;
	link* p;
	if (head != NULL) {
		while (head != NULL) {
			p = head;
			if (p->num > max) {
				max = p->num;
			}
			head = head->next;
			free(p);
		}
	}
	free(head);
	return max;
}