#include"game.h"
#include"bi_tree.h"
#include"file.h"
#include<graphics.h>//画图
#include<conio.h>
#include<cstdio>
#include<time.h>//随机数
#include<pthread.h>//多线程
//_____________________________________宏常量区______________________________________________
int back = 1;
int score = 0;
pthread_t a;//线程的名字
int sum = 0;//记录分数
int x, y;   //星球的坐标
int rb[] = { 1,1,81,41 };//返回按钮坐标
//___________________________________________________________________________________________
//_____________________________________函数区________________________________________________
int game_moving(void);//游戏中小黑快的移动，用的是'a's'd'w'按钮的控制
int wall(int r[]);//游戏中墙，防止跑出边界
int game_weapon(int r[]);//关于激光武器的呈现
void random_pos(int *x ,int *y);//星球出现的位置并画出来
int judge_weapon_pos(int* x, int* y, int p);//是否击中的判断
void clean_star(int x, int y);//清除星球的图像并有爆炸图样
void *boom(void* arg);	//多线程操作，单独开个线程计时
char* convert1(wchar_t* pwszUnicode);
//___________________________________________________________________________________________
int play_screen(void)//呈现游戏的初始界面
{
	initgraph(1000, 600, EW_NOMINIMIZE | EW_NOCLOSE);//画出界面
	setbkcolor(WHITE);
	cleardevice();
	LOGFONT b;
	gettextstyle(&b);
	b.lfHeight = 30;
	_tcscpy_s(b.lfFaceName, _T("黑体"));
	settextstyle(&b);
	settextcolor(BLACK);
	RECT RB = { rb[0],rb[1],rb[2],rb[3] };
	drawtext(_T("HOME"), &RB, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(rb[0], rb[1], rb[2], rb[3]);//格式化输出文本字符串
	wchar_t s[11];
	InputBox(s, 40, L"请输入你的姓名（中文<=5）：");//输入玩家的名字为wchar_t类型
	LOGFONT n;
	gettextstyle(&n);
	n.lfHeight = 30;
	_tcscpy_s(n.lfFaceName, _T("黑体"));//在桌面上呈现玩家的名字
	settextstyle(&n);
	settextcolor(RED);
	RECT BN = { rb[0],rb[1] + 40,rb[2] + 80,rb[3] + 40 };
	drawtext(s, &BN, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	rectangle(rb[0], rb[1] + 40, rb[2] + 80, rb[3] + 40);
	LOGFONT w;
	gettextstyle(&w);
	b.lfHeight = 30;
	_tcscpy_s(w.lfFaceName, _T("黑体"));
	settextstyle(&w);
	settextcolor(BLUE);
	RECT R_1 = { 0, 170, 1000, 210 };
	RECT R_2 = { 0, 210, 1000, 250 };
	drawtext(_T("帝国的军舰向地面投下了炸弹，炸弹会定时爆炸"), &R_1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(0, 170, 1000, 210);
	Sleep(1000);
	drawtext(_T("请在爆炸前用移动的激光炮把炸弹清除，否者失败，分数为清除炸弹数"), &R_2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(0, 210, 1000, 250);
	Sleep(1000);
	RECT RW1 = { 50, 250, 950, 300};
	RECT RW2 = { 50, 300, 950, 350 };
	RECT RW3= { 50, 350, 950, 400 };
	drawtext(_T("物体移动：使用w,a,s,d键控制移动"), &RW1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(50, 250, 950, 3000);
	Sleep(1000);
	drawtext(_T("武器攻击：先按q,再使用w,a,s,d键控制方向"), &RW2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(50, 300, 950, 350);
	Sleep(1000);
	drawtext(_T("键盘敲击b返回，点击页面进入游戏（注意以上要用英文格式）"), &RW3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(50, 350, 950, 400);
	MOUSEMSG m;//对于鼠标的操作的反馈
	while (TRUE)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://对于鼠标移动位置的判断，出现鼠标移动到按钮上方有特效的出现
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
		case WM_LBUTTONDOWN://点击返回按钮来到主菜单
			if (rb[0]<m.x && rb[1]<m.y && rb[2]>m.x && rb[3]>m.y) {
				//Read_number(p,1);
				closegraph();
				FlushMouseMsgBuffer();
				system("cls");
				printf("-----------------你的得分：%3d---------------", score);
				Sleep(2000);
				head = insert_link(score, head);
				system("cls");
				score = 0;
				return 0;

			}
		case WM_RBUTTONDOWN:///////////////////////点击右键进入游戏
			int k = game_moving();
			if (0 == k) {
				LOGFONT b;
				gettextstyle(&b);
				b.lfHeight = 30;
				_tcscpy_s(b.lfFaceName, _T("黑体"));
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
				Sleep(2000);//界面显示延缓时间
				closegraph();//关闭图画
				FlushMouseMsgBuffer();//清除残余的鼠标读入信息
				system("cls");//清屏
				printf("-----------------你的得分：%3d---------------", score);//实在转换不来了，就用小黑框
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
	int r[] = { 80,80,85,85 };//小方块的初始位置
	setbkcolor(WHITE);//更新桌面的背景
	cleardevice();
	setlinecolor(BLACK);
	setfillcolor(BLACK);
	rectangle(r[0], r[1], r[2], r[3]);
	fillrectangle(r[0], r[1], r[2], r[3]);
	random_pos(&x,&y);//获取炸弹的随机位置
	char pos;
	while (TRUE) {///开始进入键盘的操控界面，下面都是各种移动后对于移动后的操作
		          //也就是说用的颜色覆盖原来的操作画的图像
		pos = _getch();//获取字符的的读入信息
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
int wall(int r[])//画布的边界，判断是否出界限
{
	if (r[0] < 0 || r[1] < 0 || r[2]>1000 || r[3]>600)
		return 1;
	return 0;
}
int game_weapon(int r[])
{
	int k;
	char face;//朝向
	face = _getch();//获取界面键盘的读入信息
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
void random_pos(int* x, int* y)//随机绘制炸弹
{
	//time_t i = (time_t)rand() % 10;
	srand((unsigned int)time(0));//植入种子
	*x = rand() % 800+100;//给出相应的随机范围——x
	*y = rand() % 500+50;//给出相应的随机范围——y
	setlinecolor(BLUE);
	setfillcolor(BLUE);
	circle(*x, *y, 5);
	fillcircle(*x, *y, 5);
	pthread_create(&a, NULL, boom, NULL);//绘制好炸弹后，同时进行多线程操作，倒计时操作
}
int judge_weapon_pos(int *x, int *y, int p)//这里判断是否击中用了激光中间的直线进行的判断，也就是通过判断该直线是否夹在炸弹图形区域之内，所以对于这种判断有一个缺陷就是不能判断另一个坐标维度
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
void* boom(void* arg)//多线程记时操作
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