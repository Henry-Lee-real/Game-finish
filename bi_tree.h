#pragma once
typedef struct link {
	int num;
	struct link* next;
}link;
extern link* head;
link* insert_link(int num, link* head);
void print(link* head);
link* create_link(void);
int clean(void);