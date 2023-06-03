#include "game.h"

int menu()
{
	system("cls");
	cout << "��ѡ����Ϸģʽ��" << endl;
	cout << "����ģʽ" << endl;
	cout << "��������" << endl;
	cout << "�˳���Ϸ" << endl;
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
	//��lastPosition
	gameInfo.lastPos = pos;
	//��board
	gameInfo.board[pos.x][pos.y] = gameInfo.turn + 1;
	//��occupy
	gameInfo.occupy[pos.x] = Judger::judgeOccupy(gameInfo.board, pos.x);
	//��available
	for (int i = 0; i < 9; i++)
		gameInfo.available[i] = 0;
	if (gameInfo.occupy[pos.y] == 0)
		gameInfo.available[pos.y] = 1;
	else {
		for (int i = 0; i < 9; i++)
			if (gameInfo.occupy[i] == 0)
				gameInfo.available[i] = 1;
	}
	//��turn
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
	cout << "����ȷ�ϣ���ȷ����ѡ�����ַ�" << endl;
	cout << "���һ��"; colorPrint(gameInfo.agent[0]->name + " " + gameInfo.agent[0]->skin, gameInfo.agent[0]->colorNum); cout << endl;
	cout << "��Ҷ���"; colorPrint(gameInfo.agent[1]->name + " " + gameInfo.agent[1]->skin, gameInfo.agent[1]->colorNum); cout << endl;
	cout << "ȡ��";
	if (gameInfo.agent[0]->skin == gameInfo.agent[1]->skin and gameInfo.agent[0]->colorNum == gameInfo.agent[1]->colorNum)
		cout << " ��������ҵ�Ƥ������ɫ����ͬ�����Ҫ������...��";
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
	cout << "��ѡ�����һ" << endl;
	while (1)
	{
		n = rowClicked(BasicInfo::agentNum - 1, 20);
		if (n > 0) break;
	}
	switch (n)
	{
	case 1:
		cout << "��ѡ������һΪ��Player" << endl;
		Sleep(500);
		gameInfo.agent[0] = new NineNinePlayer(" ", " ", 0, 0);
		break;
	case 2:
		system("cls");
		cout << "��ѡ������һΪ��Random" << endl;
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
	cout << "��ѡ����Ҷ�" << endl;
	while (1)
	{
		n = rowClicked(BasicInfo::agentNum - 1, 20);
		if (n > 0) break;
	}
	switch (n)
	{
	case 1:
		cout << "��ѡ�����Ҷ�Ϊ��Player" << endl;
		Sleep(500);
		gameInfo.agent[1] = new NineNinePlayer(gameInfo.agent[0]->skin, " ", gameInfo.agent[0]->colorNum, 0);
		break;
	case 2:
		system("cls");
		cout << "��ѡ�����Ҷ�Ϊ��Random" << endl;
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
	//���Ͻ������ʼ��������ɣ���������Ҫ���õı������Ѿ���ã�
	cout << "����������Ϸ..." << endl;
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
					colorPrint(gameInfo.agent[end - 1]->name + " ��ʤ��", gameInfo.agent[end - 1]->colorNum);
				}
				else cout << "ƽ�֣�";
				cout << endl;
				Sleep(1000);
				cout << "�������Լ���" << endl;
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
	cout << "��Ҫ������" << endl;
	cout << "����" << endl << "����" << endl;
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
	cout << "���һ��"; colorPrint(gameInfo.agent[0]->name + " " + gameInfo.agent[0]->skin, gameInfo.agent[0]->colorNum); cout << endl;
	cout << "��Ҷ���"; colorPrint(gameInfo.agent[1]->name + " " + gameInfo.agent[1]->skin, gameInfo.agent[1]->colorNum); cout << endl;
	if (gameInfo.agent[0]->skin == gameInfo.agent[1]->skin and gameInfo.agent[0]->colorNum == gameInfo.agent[1]->colorNum)
		cout << " ��������ҵ�Ƥ������ɫ����ͬ�����Ҫ������...��";
	cout << endl;
	Sleep(2000);
	return 0;
}

int NineNineOnline::prepareGame()
{	
	cout << "��ӭ����NineNine��Ϸ��" << endl;
	Sleep(1000);
	//���������Ϣ�Ļ�ȡ
	SetConsoleTitle(L"�ǳ���Ƥ��");
	while (1)
	{
		gameInfo.agent[0] = new NineNinePlayerOL();
		system("cls");
		cout << "ȷ����Ϣ��" << gameInfo.agent[0]->name << " ";
		colorPrint(gameInfo.agent[0]->skin, gameInfo.agent[0]->colorNum);
		cout << endl << "ȷ��" << endl << "��ѡ" << endl << "�˳�" << endl;
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
	//������Ϣ�Ļ�ȡ
	SetConsoleTitle(L"ƥ����");
	system("cls");
	cout << "Ϊ��ƥ�������..." << endl;
	connector.getPlayerInfo(gameInfo.agent[1]);
	//����ȷ��
	finalCheck();
	if (uniNum > ((NineNineOpponentOL*)gameInfo.agent[1])->uniNum) gameInfo.turn = 1;
	else gameInfo.turn = 0;
	//���Ͻ������ʼ��������ɣ���������Ҫ���õı������Ѿ���ã�
	cout << "��������..." << endl;
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
					colorPrint(gameInfo.agent[end - 1]->name + " ��ʤ��", gameInfo.agent[end - 1]->colorNum);
				}
				else cout << "ƽ�֣�";
				cout << endl;
				Sleep(1000);
				cout << "�������Լ���" << endl;
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
