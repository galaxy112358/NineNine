#pragma once
#include "agents.h"

class NineNine
{
private:
	class GameInfo {
	public:
		NineNineAgent* agent[2];
		int occupy[9], board[9][9];//�Ծ�������Ϣ(�������Һ�)
		int turn, available[9];//��ǰ�غ���Ϣ(turn�����0��1)
		POINT lastPos;//�������0��8
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
