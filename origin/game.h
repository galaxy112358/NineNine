#pragma once
#include "agents.h"

class NineNine
{
private:
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
	int finalCheck();
	int prepareGame();
	void holdGames();
	void afterGame();
public:
	NineNine();
	void oneGame();
};

int menu();
