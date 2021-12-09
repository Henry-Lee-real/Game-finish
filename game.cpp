#include"game.h"
#include"bi_tree.h"
#include"file.h"
#include<graphics.h>//��ͼ
#include<conio.h>
#include<cstdio>
#include<time.h>//�����
#include<pthread.h>//���߳�
//_____________________________________�곣����______________________________________________
int back = 1;
int score = 0;
pthread_t a;//�̵߳�����
int sum = 0;//��¼����
int x, y;   //���������
int rb[] = { 1,1,81,41 };//���ذ�ť����
//___________________________________________________________________________________________
//_____________________________________������________________________________________________
int game_moving(void);//��Ϸ��С�ڿ���ƶ����õ���'a's'd'w'��ť�Ŀ���
int wall(int r[]);//��Ϸ��ǽ����ֹ�ܳ��߽�
int game_weapon(int r[]);//���ڼ��������ĳ���
void random_pos(int *x ,int *y);//������ֵ�λ�ò�������
int judge_weapon_pos(int* x, int* y, int p);//�Ƿ���е��ж�
void clean_star(int x, int y);//��������ͼ���б�ըͼ��
void *boom(void* arg);	//���̲߳��������������̼߳�ʱ
char* convert1(wchar_t* pwszUnicode);
//___________________________________________________________________________________________
int play_screen(void)//������Ϸ�ĳ�ʼ����
{
	initgraph(1000, 600, EW_NOMINIMIZE | EW_NOCLOSE);//��������
	setbkcolor(WHITE);
	cleardevice();
	LOGFONT b;
	gettextstyle(&b);
	b.lfHeight = 30;
	_tcscpy_s(b.lfFaceName, _T("����"));
	settextstyle(&b);
	settextcolor(BLACK);
	RECT RB = { rb[0],rb[1],rb[2],rb[3] };
	drawtext(_T("HOME"), &RB, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(rb[0], rb[1], rb[2], rb[3]);//��ʽ������ı��ַ���
	wchar_t s[11];
	InputBox(s, 40, L"�������������������<=5����");//������ҵ�����Ϊwchar_t����
	LOGFONT n;
	gettextstyle(&n);
	n.lfHeight = 30;
	_tcscpy_s(n.lfFaceName, _T("����"));//�������ϳ�����ҵ�����
	settextstyle(&n);
	settextcolor(RED);
	RECT BN = { rb[0],rb[1] + 40,rb[2] + 80,rb[3] + 40 };
	drawtext(s, &BN, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	rectangle(rb[0], rb[1] + 40, rb[2] + 80, rb[3] + 40);
	LOGFONT w;
	gettextstyle(&w);
	b.lfHeight = 30;
	_tcscpy_s(w.lfFaceName, _T("����"));
	settextstyle(&w);
	settextcolor(BLUE);
	RECT R_1 = { 0, 170, 1000, 210 };
	RECT R_2 = { 0, 210, 1000, 250 };
	drawtext(_T("�۹��ľ��������Ͷ����ը����ը���ᶨʱ��ը"), &R_1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(0, 170, 1000, 210);
	Sleep(1000);
	drawtext(_T("���ڱ�ըǰ���ƶ��ļ����ڰ�ը�����������ʧ�ܣ�����Ϊ���ը����"), &R_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(0, 210, 1000, 250);
	Sleep(1000);
	RECT RW1 = { 50, 250, 950, 300};
	RECT RW2 = { 50, 300, 950, 350 };
	RECT RW3= { 50, 350, 950, 400 };
	drawtext(_T("�����ƶ���ʹ��w,a,s,d�������ƶ�"), &RW1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(50, 250, 950, 3000);
	Sleep(1000);
	drawtext(_T("�����������Ȱ�q,��ʹ��w,a,s,d�����Ʒ���"), &RW2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(50, 300, 950, 350);
	Sleep(1000);
	drawtext(_T("�����û�b���أ����ҳ�������Ϸ��ע������Ҫ��Ӣ�ĸ�ʽ��"), &RW3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(50, 350, 950, 400);
	MOUSEMSG m;//�������Ĳ����ķ���
	while (TRUE)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://��������ƶ�λ�õ��жϣ���������ƶ�����ť�Ϸ�����Ч�ĳ���
			if (rb[0]<m.x && rb[1]<m.y && rb[2]>m.x && rb[3]>m.y) {
				setlinecolor(RED);
				rectangle(rb[0] + 3, rb[1] + 3, rb[2] - 3, rb[3] - 3);
			}
			else {
				setlinecolor(WHITE);
				rectangle(rb[0] + 3, rb[1] + 3, rb[2] - 3, rb[3] - 3);
			}
			FlushMouseMsgBuffer();
			break;
		case WM_LBUTTONDOWN://������ذ�ť�������˵�
			if (rb[0]<m.x && rb[1]<m.y && rb[2]>m.x && rb[3]>m.y) {
				//Read_number(p,1);
				closegraph();
				FlushMouseMsgBuffer();
				system("cls");
				printf("-----------------��ĵ÷֣�%3d---------------", score);
				Sleep(2000);
				head = insert_link(score, head);
				system("cls");
				score = 0;
				return 0;

			}
		case WM_RBUTTONDOWN:///////////////////////����Ҽ�������Ϸ
			int k = game_moving();
			if (0 == k) {
				LOGFONT b;
				gettextstyle(&b);
				b.lfHeight = 30;
				_tcscpy_s(b.lfFaceName, _T("����"));
				settextstyle(&b);
				settextcolor(BLACK);
				RECT RB = { rb[0],rb[1],rb[2],rb[3] };
				drawtext(_T("HOME"), &RB, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				rectangle(rb[0], rb[1], rb[2], rb[3]);
				break;
			}
			else if(k==7){
				setbkcolor(RED);
				cleardevice();
				LOGFONT b;
				gettextstyle(&b);
				b.lfHeight = 100;
				_tcscpy_s(b.lfFaceName, _T("Consolas"));
				settextstyle(&b);
				settextcolor(BLACK);
				RECT RB = { 100,200,800,300 };
				drawtext(_T("GAME OVER"), &RB, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				rectangle( 200,200,800,400 );
				setlinecolor(RED);
				rectangle(200, 200, 800, 400);
				pthread_cancel(a);
				Sleep(2000);//������ʾ�ӻ�ʱ��
				closegraph();//�ر�ͼ��
				FlushMouseMsgBuffer();//����������������Ϣ
				system("cls");//����
				printf("-----------------��ĵ÷֣�%3d---------------", score);//ʵ��ת�������ˣ�����С�ڿ�
				Sleep(2000);
				head=insert_link(score, head);
				system("cls");
				score = 0;
				back = 1;
				return 0;
			}
		}
	}
}
int game_moving(void)
{
	int r[] = { 80,80,85,85 };//С����ĳ�ʼλ��
	setbkcolor(WHITE);//��������ı���
	cleardevice();
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	rectangle(r[0], r[1], r[2], r[3]);
	fillrectangle(r[0], r[1], r[2], r[3]);
	random_pos(&x,&y);//��ȡը�������λ��
	char pos;
	while (TRUE) {///��ʼ������̵Ĳٿؽ��棬���涼�Ǹ����ƶ�������ƶ���Ĳ���
		          //Ҳ����˵�õ���ɫ����ԭ���Ĳ�������ͼ��
		pos = _getch();//��ȡ�ַ��ĵĶ�����Ϣ
		switch (pos) {
		case 'a':
		case 'A':
			r[0] -= 5;
			r[2] -= 5;
			if (wall(r)) {
				r[0] += 5;
				r[2] += 5;
				break;
			}
			r[0] += 5;
			r[2] += 5;
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			r[0] -= 5;
			r[2] -= 5;
			setlinecolor(BLACK);
			setfillcolor(BLACK);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			if (back== 0) return 7;
			break;
		case 'w':
		case 'W':
			r[1] -= 5;
			r[3] -= 5;
			if (wall(r)) {
				r[1] += 5;
				r[3] += 5;
				break;
			}
			r[1] += 5;
			r[3] += 5;
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			r[1] -= 5;
			r[3] -= 5;
			setlinecolor(BLACK);
			setfillcolor(BLACK);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			if (back == 0) return 7;
			break;
		case 'd':
		case 'D':
			r[0] += 5;
			r[2] += 5;
			if (wall(r)) {
				r[0] -= 5;
				r[2] -= 5;
				break;
			}
			r[0] -= 5;
			r[2] -= 5;
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			r[0] += 5;
			r[2] += 5;
			setlinecolor(BLACK);
			setfillcolor(BLACK);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			if (back == 0) return 7;
			break;
		case 's':
		case 'S':
			r[1] += 5;
			r[3] += 5;
			if (wall(r)) {
				r[1] -= 5;
				r[3] -= 5;
				break;
			}
			r[1] -= 5;
			r[3] -= 5;
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			r[1] += 5;
			r[3] += 5;
			setlinecolor(BLACK);
			setfillcolor(BLACK);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			if (back == 0) return 7;
			break;
		case 'b':
		case 'B':
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			rectangle(r[0], r[1], r[2], r[3]);
			fillrectangle(r[0], r[1], r[2], r[3]);
			if (back == 0) return 7;
			pthread_cancel(a);
			return 0;
			break;
		case 'q':
		case 'Q':
			int k = game_weapon(r);
			if (back == 0) return 7;
			break;
		}
	}
}
int wall(int r[])//�����ı߽磬�ж��Ƿ������
{
	if (r[0] < 0 || r[1] < 0 || r[2]>1000 || r[3]>600)
		return 1;
	return 0;
}
int game_weapon(int r[])
{
	int k;
	char face;//����
	face = _getch();//��ȡ������̵Ķ�����Ϣ
	switch (face)
	{
	case 'w':
	case 'W':
		setlinecolor(YELLOW);
		setfillcolor(RGB(255, 128, 0));
		rectangle(r[0] + 1, r[1] - 600, r[2] - 1, r[1] - 1);
		fillrectangle(r[0] + 1, r[1] - 600, r[2] - 1, r[1] - 1);
		k = (1 == judge_weapon_pos(&x, &y, r[0] + 3));
		Sleep(300);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		rectangle(r[0] + 1, r[1] - 600, r[2] - 1, r[1] - 1);
		fillrectangle(r[0] + 1, r[1] - 600, r[2] - 1, r[1] - 1);
		if (k == 1) random_pos(&x,&y);
		break;
	case 'd':
	case 'D':
		setlinecolor(YELLOW);
		setfillcolor(RGB(255, 128, 0));
		rectangle(r[2] + 1, r[1] + 1, r[2] + 1000, r[3] - 1);
		fillrectangle(r[2] + 1, r[1] + 1, r[2] + 1000, r[3] - 1);
		k=(1==judge_weapon_pos(&x, &y, r[1] + 3));
		Sleep(300);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		rectangle(r[2] + 1, r[1] + 1, r[2] + 1000, r[3] - 1);
		fillrectangle(r[2] + 1, r[1] + 1, r[2] + 1000, r[3] - 1);
		if (k == 1) random_pos(&x, &y);
		break;
	case 's':
	case 'S':
		setlinecolor(YELLOW);
		setfillcolor(RGB(255, 128, 0));
		rectangle(r[0] + 1, r[3] + 1, r[2] - 1, r[3] + 600);
		fillrectangle(r[0] + 1, r[3] + 1, r[2] - 1, r[3] + 600);
		k=(1==judge_weapon_pos(&x, &y, r[0] + 3));
		Sleep(300);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		rectangle(r[0] + 1, r[3] + 1, r[2] - 1, r[3] + 600);
		fillrectangle(r[0] + 1, r[3] + 1, r[2] - 1, r[3] + 600);
		if (k == 1) random_pos(&x, &y);
		break;
	case 'a':
	case 'A':
		setlinecolor(YELLOW);
		setfillcolor(RGB(255, 128, 0));
		rectangle(r[0] - 1000, r[1] + 1, r[0] - 1, r[3] - 1);
		fillrectangle(r[0] - 1000, r[1] + 1, r[0] - 1, r[3] - 1);
		k=(1==judge_weapon_pos(&x, &y, r[1] + 3));
		Sleep(300);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		rectangle(r[0] - 1000, r[1] + 1, r[0] - 1, r[3] - 1);
		fillrectangle(r[0] - 1000, r[1] + 1, r[0] - 1, r[3] - 1);
		if (k == 1) random_pos(&x, &y);
		break;
	default:
		break;
	}
	return 1;
}
void random_pos(int* x, int* y)//�������ը��
{
	//time_t i = (time_t)rand() % 10;
	srand((unsigned int)time(0));//ֲ������
	*x = rand() % 800+100;//������Ӧ�������Χ����x
	*y = rand() % 500+50;//������Ӧ�������Χ����y
	setlinecolor(BLUE);
	setfillcolor(BLUE);
	circle(*x, *y, 5);
	fillcircle(*x, *y, 5);
	pthread_create(&a, NULL, boom, NULL);//���ƺ�ը����ͬʱ���ж��̲߳���������ʱ����
}
int judge_weapon_pos(int *x, int *y, int p)//�����ж��Ƿ�������˼����м��ֱ�߽��е��жϣ�Ҳ����ͨ���жϸ�ֱ���Ƿ����ը��ͼ������֮�ڣ����Զ��������ж���һ��ȱ�ݾ��ǲ����ж���һ������ά��
{
	if ((p <= *x + 8 && p >= *x - 8) || (p >= *y - 8 && p <= *y + 8)) {
		sum++;
		score++;
		clean_star(*x, *y);
		pthread_cancel(a);
		return 1;
	}	
	return 0;
}
void clean_star(int x, int y)
{
	setlinecolor(RED);
	setfillcolor(RED);
	circle(x, y, 7);
	fillcircle(x, y, 7);
	Sleep(200);
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	circle(x, y, 7);
	fillcircle(x, y, 7);
}
void* boom(void* arg)//���̼߳�ʱ����
{
	pthread_testcancel();
	Sleep(9000);
	pthread_testcancel();
	Sleep(1000);
	pthread_testcancel();
	setlinecolor(RGB(255, 128, 0));
	setfillcolor(RGB(255, 128, 0));
	circle(x, y, 15);
	fillcircle(x, y, 15);
	setlinecolor(RED);
	setfillcolor(RED);
	circle(x, y, 5);
	fillcircle(x, y, 5);
	Sleep(1000);
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	circle(x, y, 15);
	fillcircle(x, y, 15);
	Sleep(1000);
	back = 0;
	pthread_testcancel();
	return 0;
}
char* convert1(wchar_t* pwszUnicode)
{
	int iSize;
	char* pszMultiByte;
	iSize = WideCharToMultiByte(CP_ACP, 0, pwszUnicode, -1, NULL, 0, NULL, NULL);
	pszMultiByte = (char*)malloc(iSize * sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, pwszUnicode, -1, pszMultiByte, iSize, NULL, NULL);
	return pszMultiByte;
}