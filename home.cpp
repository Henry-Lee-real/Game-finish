#include"home.h"
#include<graphics.h>
int r1[] = { 210,30,630,240 };
int r2[] = { 70,300,270,400 };
int r3[] = { 320,300,520,400 };
int r4[] = { 570,300,770,400 };
int button_pos(int x, int y)
{
	if (x > r2[0] && x<r2[2] && y>r2[1] && y < r2[3])return 1;
	if (x > r3[0] && x<r3[2] && y>r3[1] && y < r3[3])return 2;
	if (x > r4[0] && x<r4[2] && y>r4[1] && y < r4[3])return 3;
	return 0;//判断鼠标的位置，判断是否点击进入
}
int main_screen(void)
{
	initgraph(840, 480, EW_NOMINIMIZE | EW_NOCLOSE);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);//打印界面，下面为坐标位置
	RECT R1 = { r1[0],r1[1],r1[2],r1[3] };
	RECT R2 = { r2[0],r2[1],r2[2],r2[3] };
	RECT R3 = { r3[0],r3[1],r3[2],r3[3] };
	RECT R4 = { r4[0],r4[1],r4[2],r4[3] };
	LOGFONT f, k;
	gettextstyle(&f);
	f.lfHeight = 80;
	_tcscpy_s(f.lfFaceName, _T("Consolas"));//Consolas
	settextstyle(&f);
	settextcolor(BLACK);
	drawtext(_T("STAR WARS"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	gettextstyle(&k);
	k.lfHeight = 20;
	_tcscpy_s(k.lfFaceName, _T("黑体"));
	settextstyle(&k);
	settextcolor(BLACK);
	drawtext(_T("开始游戏"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("记录"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("退出"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rectangle(r2[0], r2[1], r2[2], r2[3]);
	rectangle(r3[0], r3[1], r3[2], r3[3]);
	rectangle(r4[0], r4[1], r4[2], r4[3]);
	MOUSEMSG m;
	while (TRUE)
	{
		int pos;
		int pos2;
		m = GetMouseMsg();//得到鼠标的信息
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			pos = button_pos(m.x, m.y);
			switch (pos)//炫酷的鼠标在按键上的浮动效果
			{
			case 1:
				setlinecolor(GREEN);
				rectangle(r2[0] - 5, r2[1] - 5, r2[2] + 5, r2[3] + 5);
				break;
			case 2:
				setlinecolor(BLUE);
				rectangle(r3[0] - 5, r3[1] - 5, r3[2] + 5, r3[3] + 5);
				break;
			case 3:
				setlinecolor(RED);
				rectangle(r4[0] - 5, r4[1] - 5, r4[2] + 5, r4[3] + 5);
				break;
			case 0:
				setlinecolor(WHITE);
				rectangle(r2[0] - 5, r2[1] - 5, r2[2] + 5, r2[3] + 5);
				rectangle(r3[0] - 5, r3[1] - 5, r3[2] + 5, r3[3] + 5);
				rectangle(r4[0] - 5, r4[1] - 5, r4[2] + 5, r4[3] + 5);
				break;
			}
			FlushMouseMsgBuffer();
			break;
		case WM_LBUTTONDOWN://切屏操作
			pos2 = button_pos(m.x, m.y);
			switch (pos2)
			{
			case 1:
				closegraph();
				return 1;
				break;
			case 2:
				closegraph();
				return 2;
				break;
			case 3:
				closegraph();
				return 3;
			}
		}
	}
}