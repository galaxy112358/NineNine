#pragma once
#include "agents.h"

class NineNine
{
public:
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
