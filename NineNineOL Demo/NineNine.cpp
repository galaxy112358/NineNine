#include "game.h"

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
	while (1)
	{
		Sleep(2000);
		switch (menu())
		{
		case 1:
		{
			system("cls");
			SetConsoleTitle(L"单机模式");
			cout << "即将进入单机模式" << endl;
			Sleep(2000);
			NineNineOffline game;
			if (game.prepareGame())
				game.holdGames();
			game.afterGame();
			break;
		}
		case 2:
		{
			system("cls");
			SetConsoleTitle(L"联机模式");
			cout << "即将进入联机模式" << endl;
			Sleep(2000);
			getStart();
			NineNineOnline game(0);
			int signal = game.prepareGame();
			if (signal == 0)
			{
				game.holdGames();
				game.afterGame();
			}
			theEnd();
			break;
		}
		case 3:
			return 0;
		}
	}
}

/* 

目前面临的问题：
服务器对于玩家掉线的处理
两个玩家连续对战、对战中退出/更换对手

更多的还有：
更强大的bot
登陆（多个）账号->积分/战绩
... ...
*/