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
	int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
	int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */
	while (1)
	{
		if (!IsZoomed(hwnd) and !IsIconic(hwnd) and hwnd == GetForegroundWindow())
		{
			cout << "����������Ϸ��ȫ�����棬������������ܴ�λ������" << endl;
			Sleep(1000);
			LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* ��ȡ������Ϣ */
			/* ���ô�����Ϣ */
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
			SetConsoleTitle(L"����ģʽ");
			cout << "�������뵥��ģʽ" << endl;
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
			SetConsoleTitle(L"����ģʽ");
			cout << "������������ģʽ" << endl;
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

Ŀǰ���ٵ����⣺
������������ҵ��ߵĴ���
�������������ս����ս���˳�/��������

����Ļ��У�
��ǿ���bot
��½��������˺�->����/ս��
... ...
*/