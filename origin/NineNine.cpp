#include "game.h"
#include <thread>

void outPos()
{
	while (1)
	{
		POINT p = getClickPos();
		cout << p.x << " " << p.y << endl;
		Sleep(1000);
	}
}

void fullScreen()
{
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */
	while (1)
	{
		if (!IsZoomed(hwnd) and !IsIconic(hwnd) and hwnd == GetForegroundWindow())
		{
			cout << "声明：本游戏请全屏游玩，否则鼠标点击可能错位！！！" << endl;
			Sleep(1000);
			LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */
			/* 设置窗口信息 */
			SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE));
			SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
		}
		Sleep(100);
	}
}

int main()
{
	//thread(outPos).detach();
	thread(fullScreen).detach();
	Sleep(3000);
	while (1)
	{
		switch (menu())
		{
		case 1:
		{
			system("cls");
			cout << "即将进入单机模式" << endl;
			Sleep(2000);
			NineNine game;
			game.oneGame();
			break;
		}
		case 2:
			break;
		case 3:
			return 0;
		}
	}
}