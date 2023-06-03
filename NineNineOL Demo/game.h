#pragma once
#include "agents.h"

class NineNine
{
public:
	class GameInfo {
	public:
		NineNineAgent* agent[2];
		int occupy[9], board[9][9];//对局棋盘信息(存的是玩家号)
		int turn, available[9];//当前回合信息(turn存的是0或1)
		POINT lastPos;//坐标均从0到8
		void resetGameInfo();
	};
	GameInfo gameInfo;
	void changeState(const POINT pos);
	virtual int finalCheck() = 0;
	virtual int prepareGame() = 0;
	virtual void holdGames() = 0;
	void afterGame();
	NineNine();
};

class NineNineOffline : public NineNine 
{
public:
	int finalCheck();
	int prepareGame();
	void holdGames();
};

class NineNineOnline : public NineNine
{
public:
	int uniNum;
	NineNineOnline(int n = 0);
	Connector connector;
	int finalCheck();
	int prepareGame();
	void holdGames();
};

int menu();
