#include "basic.h"

const int BasicInfo::skinNum;
bool BasicInfo::available_skin[BasicInfo::skinNum] = { 0 };
string BasicInfo::skins[BasicInfo::skinNum] = { " ","●","○","◎","☉","★","☆" };

const int BasicInfo::colorNum;
bool BasicInfo::available_color[BasicInfo::colorNum] = { 0 };
int BasicInfo::colors[BasicInfo::colorNum] = { 7, 1, 2, 3, 4, 5, 6 };

const int BasicInfo::agentNum;
bool BasicInfo::available_agent[BasicInfo::agentNum] = { 0 };
string BasicInfo::agentNames[BasicInfo::agentNum] = { "default", "Player", "Random" };

inline POINT getClickPos()
{
	while (1)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			POINT p = { 0 };
			HWND h = GetForegroundWindow();
			GetCursorPos(&p);
			ScreenToClient(h, &p);
			return p;
		}
		Sleep(10);
	}
}

int rowClicked(int max_, int length, int start)
{
	while (1)
	{
		POINT pos = getClickPos();
		if (pos.x > start + length * 10 or pos.x < start) continue;
		int n = (pos.y - 7) / 20 - 1;
		if (n > max_) continue;
		else return n;
	}
}

POINT pointChosen()
{
	while (1)
	{
		//数据是一个个点出来的...
		POINT p = getClickPos();
		int x, y;
		if (p.y >= 95 and p.y <= 125) x = 1;
		else if (p.y >= 133 and p.y <= 163) x = 2;
		else if (p.y >= 172 and p.y <= 202) x = 3;
		else if (p.y >= 288 and p.y <= 318) x = 4;
		else if (p.y >= 326 and p.y <= 356) x = 5;
		else if (p.y >= 363 and p.y <= 393) x = 6;
		else if (p.y >= 480 and p.y <= 510) x = 7;
		else if (p.y >= 518 and p.y <= 548) x = 8;
		else if (p.y >= 557 and p.y <= 587) x = 9;
		else continue;

		if (p.x >= 25 and p.x <= 55) y = 1;
		else if (p.x >= 63 and p.x <= 93) y = 2;
		else if (p.x >= 100 and p.x <= 130) y = 3;
		else if (p.x >= 183 and p.x <= 213) y = 4;
		else if (p.x >= 222 and p.x <= 252) y = 5;
		else if (p.x >= 258 and p.x <= 288) y = 6;
		else if (p.x >= 342 and p.x <= 372) y = 7;
		else if (p.x >= 380 and p.x <= 410) y = 8;
		else if (p.x >= 418 and p.x <= 448) y = 9;
		else continue;
		
		p.x = (x - 1) / 3 * 3 + (y - 1) / 3;
		p.y = (x - 1) % 3 * 3 + (y - 1) % 3;
		return p;
	}
}

int randomNum(int x)
{
	//生成随机数
	unsigned seed = 0;
	seed = time(0);
	srand(seed);
	return rand() / x;
}
