#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <Winsock2.h>  
#include <Windows.h>
#include <thread>
#include <ctime>
#include <chrono>
#include <mutex>
#include <condition_variable>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#pragma comment(lib,"ws2_32.lib")
using namespace std;

inline POINT getClickPos();

int rowClicked(int max_, int length, int start = 5, int min_ = 1);

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
	//Ƥ��
	static const int skinNum = 7;
	static bool available_skin[skinNum];
	static string skins[skinNum];
	//��ɫ
	static const int colorNum = 7;
	static bool available_color[colorNum];
	/*
	color:
	0 = ��ɫ 8 = ��ɫ
	1 = ��ɫ 9 = ����ɫ
	2 = ��ɫ 10 = ����ɫ
	3 = ǳ��ɫ 11 = ��ǳ��ɫ
	4 = ��ɫ 12 = ����ɫ
	5 = ��ɫ 13 = ����ɫ
	6 = ��ɫ 14 = ����ɫ
	7 = ��ɫ 15 = ����ɫ
	*/
	static int colors[colorNum];
	//Agents(offline)
	static const int agentNum = 3;
	static bool available_agent[agentNum];
	static string agentNames[agentNum];
};


void getStart();

void theEnd();

void printCurrentTime();