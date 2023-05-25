#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;

inline POINT getClickPos();

int rowClicked(int max_, int length, int start = 5);

int randomNum(int x = 1);

template<class T>
void colorPrint(const T& s, const int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | color);
	cout << s;
	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

POINT  pointChosen();

class BasicInfo
{
public:
	//皮肤
	static const int skinNum = 7;
	static bool available_skin[skinNum];
	static string skins[skinNum];
	//颜色
	static const int colorNum = 7;
	static bool available_color[colorNum];
	/*
	color:
	0 = 黑色 8 = 灰色
	1 = 蓝色 9 = 淡蓝色
	2 = 绿色 10 = 淡绿色
	3 = 浅绿色 11 = 淡浅绿色
	4 = 红色 12 = 淡红色
	5 = 紫色 13 = 淡紫色
	6 = 黄色 14 = 淡黄色
	7 = 白色 15 = 亮白色
	*/
	static int colors[colorNum];
	//Agents
	static const int agentNum = 3;
	static bool available_agent[agentNum];
	static string agentNames[agentNum];
};
