#pragma once
#include "basic.h"

class NineNineAgent 
{
public:
	string name;
	string skin;
	int colorNum;
	int score, total;
	NineNineAgent(string N = "Agent", string SN = " ", int CN = -1, int S = 0, int T = 0);
	virtual POINT decision(const int(*board)[9], const int* occupy, const int* available) = 0;
private:
	virtual void chooseName() = 0;
	virtual void chooseSkin() = 0;
	virtual void chooseColor() = 0;
};

class NineNinePlayer : public NineNineAgent
{
public:
	NineNinePlayer(const string skin1 = 0, const string skin2 = 0, const int colorNum1 = 0, const int colorNum2 = 0,
		string N = "Player", string SN = " ", int CN = -1, int S = 0, int T = 0);
	POINT decision(const int(*board)[9], const int* occupy, const int* available);
private:
	void chooseName();
	void chooseSkin();
	void chooseColor();
};

class NineNineRandom : public NineNineAgent
{
public:
	NineNineRandom(const string skin1 = 0, const string skin2 = 0, const int colorNum1 = 0, const int colorNum2 = 0,
		string N = "Random", string SN = " ", int CN = -1, int S = 0, int T = 0);
	POINT decision(const int(*board)[9], const int* occupy, const int* available);
private:
	void chooseName();
	void chooseSkin();
	void chooseColor();
};

//��̬�ĺô���ʱ�Ѿ����֣�Ҫ��һ��agentֻ��Ҫ
// 1���̳�NineNineAgent�࣬ʵ�ֹ��캯���Լ��ĸ����麯��
// 2���޸�BasicInfo�е���Ϣ��agentNum++�����ּӽ�ȥ��
// 3����prepareGame��switch�����һ��


class Printer {
private:
	static string board_for_print[27][49];
	static void resetPrintBoard();
	static void loadIntoPrintBoard(const int(*board)[9], const int* occupy, const int* available, const NineNineAgent* agent[2]);
	static void printHead(const NineNineAgent* agent[2]);
	static void printBoard(const int(*board)[9], const int* occupy, const POINT last, int turn, const NineNineAgent* agent[2]);
public:
	static void printAgentForChoose();
	static void printSkinForChoose(const string skin1, const string skin2);
	static void printColorForChoose(const string skin1, const string skin2, const int colorNum1, const int colorNum2, string skin);
	static void printAll(const int(*board)[9], const int* occupy, const int* available, const POINT last, int turn, const NineNineAgent* agent[2]);
};

class Judger {
public:
	static int judgeLegal(const int(*board)[9], const int* available, const POINT pos);
	static int judgeOccupy(const int(*board)[9], const int x);
	static int judgeEnd(const int(*board)[9], const int* occupy, const int* available);
};