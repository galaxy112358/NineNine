#include "game.h"

int menu()
{
	system("cls");
	cout << "请选择游戏模式：" << endl;
	cout << "单机模式" << endl;
	cout << "多人联机" << endl;
	cout << "退出游戏" << endl;
	while (1)
	{
		int x = rowClicked(4, 8);
		if (x != 1) return x - 1;
	}
}


NineNine::NineNine()
{
	gameInfo.agent[0] = nullptr;
	gameInfo.agent[1] = nullptr;
	gameInfo.resetGameInfo();
}

void NineNine::GameInfo::resetGameInfo()
{
	for (int i = 0; i < 9; i++) {
		occupy[i] = 0;
		available[i] = 0;
		for (int j = 0; j < 9; j++) board[i][j] = 0;
	}
	if (agent[0] != nullptr and agent[1] != nullptr)
	{
		if (agent[0]->score > agent[1]->score) turn = 1;
		else if (agent[0]->score < agent[1]->score) turn = 0;
		else turn = randomNum() % 2;
	}
	lastPos.x = 666;
	lastPos.y = 4;
	available[4] = 1;
}

void NineNine::changeState(const POINT pos)
{
	//改lastPosition
	gameInfo.lastPos = pos;
	//改board
	gameInfo.board[pos.x][pos.y] = gameInfo.turn + 1;
	//改occupy
	gameInfo.occupy[pos.x] = Judger::judgeOccupy(gameInfo.board, pos.x);
	//改available
	for (int i = 0; i < 9; i++)
		gameInfo.available[i] = 0;
	if (gameInfo.occupy[pos.y] == 0)
		gameInfo.available[pos.y] = 1;
	else {
		for (int i = 0; i < 9; i++)
			if (gameInfo.occupy[i] == 0)
				gameInfo.available[i] = 1;
	}
	//改turn
	gameInfo.turn = (gameInfo.turn + 1) % 2;
}

void NineNine::afterGame()
{
	delete gameInfo.agent[0];
	delete gameInfo.agent[1];
}


int NineNineOffline::finalCheck()
{
	system("cls");
	SetConsoleTitle(L"Final Check");
	cout << "最终确认：若确认请选择先手方" << endl;
	cout << "玩家一："; colorPrint(gameInfo.agent[0]->name + " " + gameInfo.agent[0]->skin, gameInfo.agent[0]->colorNum); cout << endl;
	cout << "玩家二："; colorPrint(gameInfo.agent[1]->name + " " + gameInfo.agent[1]->skin, gameInfo.agent[1]->colorNum); cout << endl;
	cout << "取消";
	if (gameInfo.agent[0]->skin == gameInfo.agent[1]->skin and gameInfo.agent[0]->colorNum == gameInfo.agent[1]->colorNum)
		cout << " （两个玩家的皮肤和颜色均相同，真的要这样吗...）";
	cout << endl;
	while (1)
	{
		int x = rowClicked(4, 30);
		if (x > 1 and x < 5) return x - 2;
	}
}

int NineNineOffline::prepareGame()
{
	int n = 0;
	system("cls");
	SetConsoleTitle(L"Player 1");
	Printer::printAgentForChoose();
	cout << "请选择玩家一" << endl;
	while (1)
	{
		n = rowClicked(BasicInfo::agentNum - 1, 20);
		if (n > 0) break;
	}
	switch (n)
	{
	case 1:
		cout << "你选择的玩家一为：Player" << endl;
		Sleep(500);
		gameInfo.agent[0] = new NineNinePlayer(" ", " ", 0, 0);
		break;
	case 2:
		system("cls");
		cout << "你选择的玩家一为：Random" << endl;
		Sleep(500);
		gameInfo.agent[0] = new NineNineRandom(" ", " ", 0, 0);
		break;
	default:
		cerr << "prepareGame !" << endl;
		system("pause");
		break;
	}

	system("cls");
	SetConsoleTitle(L"Player 2");
	Printer::printAgentForChoose();
	cout << "请选择玩家二" << endl;
	while (1)
	{
		n = rowClicked(BasicInfo::agentNum - 1, 20);
		if (n > 0) break;
	}
	switch (n)
	{
	case 1:
		cout << "你选择的玩家二为：Player" << endl;
		Sleep(500);
		gameInfo.agent[1] = new NineNinePlayer(gameInfo.agent[0]->skin, " ", gameInfo.agent[0]->colorNum, 0);
		break;
	case 2:
		system("cls");
		cout << "你选择的玩家二为：Random" << endl;
		Sleep(500);
		gameInfo.agent[1] = new NineNineRandom(gameInfo.agent[0]->skin, " ", gameInfo.agent[0]->colorNum, 0);
		break;
	default:
		cerr << "prepareGame !" << endl;
		system("pause");
		break;
	}

	int signal = finalCheck();
	if (signal == 2) return 0;
	else gameInfo.turn = signal;
	//以上结束后初始化彻底完成（即所有需要设置的变量都已经设好）
	cout << "即将进入游戏..." << endl;
	Sleep(1000);
	return 1;
}

void NineNineOffline::holdGames()
{
	SetConsoleTitle(L"Nine Nine");
	POINT pos;
	int end, flag;
	while (1)
	{
		end = 0;
		while (1)
		{
			Printer::printAll(gameInfo.board, gameInfo.occupy, gameInfo.available, gameInfo.lastPos, gameInfo.turn, const_cast<const NineNineAgent**>(gameInfo.agent));
			while (1)
			{
				pos = gameInfo.agent[gameInfo.turn]->decision(gameInfo.board, gameInfo.occupy, gameInfo.available);
				if (Judger::judgeLegal(gameInfo.board, gameInfo.available, pos)) break;
			}
			changeState(pos);
			end = Judger::judgeEnd(gameInfo.board, gameInfo.occupy, gameInfo.available);
			if (end)
			{
				Printer::printAll(gameInfo.board, gameInfo.occupy, gameInfo.available, gameInfo.lastPos, gameInfo.turn, const_cast<const NineNineAgent**>(gameInfo.agent));
				gameInfo.agent[0]->total++;
				gameInfo.agent[1]->total++;
				if (end == 1 or end == 2)
				{
					gameInfo.agent[end - 1]->score++;
					colorPrint(gameInfo.agent[end - 1]->name + " 获胜！", gameInfo.agent[end - 1]->colorNum);
				}
				else cout << "平局！";
				cout << endl;
				Sleep(1000);
				cout << "点击鼠标以继续" << endl;
				while (1)
				{
					if (getClickPos().x) break;
					Sleep(50);
				}
				gameInfo.resetGameInfo();
				break;
			}
		}
	system("cls");
	cout << "还要继续吗？" << endl;
	cout << "继续" << endl << "结束" << endl;
	while (1)
	{
		flag = rowClicked(3, 10);
		if (flag > 1) break;
	}
	if (flag == 3) break;
	}
}


int NineNineOnline::finalCheck()
{
	system("cls");
	SetConsoleTitle(L"Final Check");
	cout << "玩家一："; colorPrint(gameInfo.agent[0]->name + " " + gameInfo.agent[0]->skin, gameInfo.agent[0]->colorNum); cout << endl;
	cout << "玩家二："; colorPrint(gameInfo.agent[1]->name + " " + gameInfo.agent[1]->skin, gameInfo.agent[1]->colorNum); cout << endl;
	if (gameInfo.agent[0]->skin == gameInfo.agent[1]->skin and gameInfo.agent[0]->colorNum == gameInfo.agent[1]->colorNum)
		cout << " （两个玩家的皮肤和颜色均相同，真的要这样吗...）";
	cout << endl;
	Sleep(2000);
	return 0;
}

int NineNineOnline::prepareGame()
{	
	cout << "欢迎来到NineNine游戏！" << endl;
	Sleep(1000);
	//己方相关信息的获取
	SetConsoleTitle(L"昵称与皮肤");
	while (1)
	{
		gameInfo.agent[0] = new NineNinePlayerOL();
		system("cls");
		cout << "确认信息：" << gameInfo.agent[0]->name << " ";
		colorPrint(gameInfo.agent[0]->skin, gameInfo.agent[0]->colorNum);
		cout << endl << "确认" << endl << "重选" << endl << "退出" << endl;
		int n = rowClicked(4, 5, 5, 2);
		if (n == 2) break;
		else if (n == 3)
		{
			delete gameInfo.agent[0];
			continue;
		}
		else if (n == 4)
		{
			delete gameInfo.agent[0];
			return -1;
		}
	}
	connector.sendPlayerInfo((NineNinePlayerOL*)gameInfo.agent[0]);
	uniNum = connector.getUniN();
	//对手信息的获取
	SetConsoleTitle(L"匹配中");
	system("cls");
	cout << "为你匹配对手中..." << endl;
	connector.getPlayerInfo(gameInfo.agent[1]);
	//最终确认
	finalCheck();
	if (uniNum > ((NineNineOpponentOL*)gameInfo.agent[1])->uniNum) gameInfo.turn = 1;
	else gameInfo.turn = 0;
	//以上结束后初始化彻底完成（即所有需要设置的变量都已经设好）
	cout << "即将进入..." << endl;
	Sleep(1000);
	return 0;
}

void NineNineOnline::holdGames()
{
	SetConsoleTitle(L"Nine Nine");
	POINT pos;
	int end, flag;
	while (1)
	{
		end = 0;
		while (1)
		{
			Printer::printAll(gameInfo.board, gameInfo.occupy, gameInfo.available, gameInfo.lastPos, gameInfo.turn, const_cast<const NineNineAgent**>(gameInfo.agent));
			while (1)
			{
				pos = gameInfo.agent[gameInfo.turn]->decision(gameInfo.board, gameInfo.occupy, gameInfo.available);
				if (gameInfo.turn == 0)
				{
					string decision = "{NineNine:{Decision:{uniqueNum:" + to_string(uniNum)
						+ ",x:" + to_string(pos.x) + ",y:" + to_string(pos.y) + "}}}";
					const char* p = decision.c_str();
					connector.sendData(p);
				}
				if (Judger::judgeLegal(gameInfo.board, gameInfo.available, pos)) break;
			}
			changeState(pos);
			end = Judger::judgeEnd(gameInfo.board, gameInfo.occupy, gameInfo.available);
			if (end)
			{
				Printer::printAll(gameInfo.board, gameInfo.occupy, gameInfo.available, gameInfo.lastPos, gameInfo.turn, const_cast<const NineNineAgent**>(gameInfo.agent));
				gameInfo.agent[0]->total++;
				gameInfo.agent[1]->total++;
				if (end == 1 or end == 2)
				{
					gameInfo.agent[end - 1]->score++;
					colorPrint(gameInfo.agent[end - 1]->name + " 获胜！", gameInfo.agent[end - 1]->colorNum);
				}
				else cout << "平局！";
				cout << endl;
				Sleep(1000);
				cout << "点击鼠标以继续" << endl;
				while (1)
				{
					if (getClickPos().x) break;
					Sleep(50);
				}
				gameInfo.resetGameInfo();
				break;
			}
		}
	}
}

NineNineOnline::NineNineOnline(int n) :connector(n), NineNine() {}
