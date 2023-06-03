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
	//Æ¤·ô
	static const int skinNum = 7;
	static bool available_skin[skinNum];
	static string skins[skinNum];
	//ÑÕÉ«
	static const int colorNum = 7;
	static bool available_color[colorNum];
	/*
	color:
	0 = ºÚÉ« 8 = »ÒÉ«
	1 = À¶É« 9 = µ­À¶É«
	2 = ÂÌÉ« 10 = µ­ÂÌÉ«
	3 = Ç³ÂÌÉ« 11 = µ­Ç³ÂÌÉ«
	4 = ºìÉ« 12 = µ­ºìÉ«
	5 = ×ÏÉ« 13 = µ­×ÏÉ«
	6 = »ÆÉ« 14 = µ­»ÆÉ«
	7 = °×É« 15 = ÁÁ°×É«
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