#include "agents.h"

//NineNineAgent�����ࣩ
NineNineAgent::NineNineAgent(string N, string SN, int CN, int S, int T)
{
	name = N;
	skin = SN; colorNum = CN;
	score = S; total = T;
}

//NineNinePlayer
NineNinePlayer::NineNinePlayer(const string skin1, const string skin2, const int colorNum1, const int colorNum2, 
	string N, string SN, int CN, int S, int T) : NineNineAgent(N, SN, CN, S, T)
{
	system("cls");
	chooseName();
	system("cls");
	Printer::printSkinForChoose(skin1, skin2);
	chooseSkin();
	system("cls");
	Printer::printColorForChoose(skin1, skin2, colorNum1, colorNum2, skin);
	chooseColor();
}

void NineNinePlayer::chooseName()
{
	string temp;
	cout << "�������ǳƣ�";
	cin >> temp;
	name += (" " + temp);
	cout << "���" << name << "��" << endl;
	Sleep(1000);
}

void NineNinePlayer::chooseSkin() 
{
	cout << "��ѡ����ϲ����Ƥ��" << endl;
	skin = BasicInfo::skins[rowClicked(BasicInfo::skinNum - 1, 5, 5, 0)];
	cout << "��ѡ����Ƥ�� " << skin << endl;
	Sleep(1000);
}

void NineNinePlayer::chooseColor()
{
	cout << "��ѡ����ϲ������ɫ" << endl;
	colorNum = rowClicked(BasicInfo::colorNum - 1, 5);
	cout << "��ѡ���� ";
	colorPrint(skin, colorNum);
	cout << " ��ɫ" << endl;
	Sleep(1000);
}

POINT NineNinePlayer::decision(const int(*board)[9], const int* occupy, const int* available)
{
	POINT p;
	while (1)
	{
		p = pointChosen();
		if (Judger::judgeLegal(board, available, p)) break;
	}
	return p;
}

//NineNineRandom
NineNineRandom::NineNineRandom(const string skin1, const string skin2, const int colorNum1, const int colorNum2, 
	string N, string SN, int CN, int S, int T) : NineNineAgent(N, SN, CN, S, T)
{
	int n = 1;
	chooseName();
	while (1)
	{
		int k = 0;
		k = randomNum(n) % BasicInfo::skinNum;
		if (k > 0 and BasicInfo::skins[k] != skin1 and BasicInfo::skins[k] != skin2)
		{
			skin = BasicInfo::skins[k];
			break;
		}
		n++;
	}
	chooseSkin();
	while (1)
	{
		colorNum = randomNum(n) % BasicInfo::colorNum;
		if (colorNum != colorNum1 and colorNum != colorNum2 and colorNum > 0) break;
		n++;
	}
	chooseColor();
	cout << name << " ѡ���� ";
	colorPrint(skin, colorNum);
	cout << endl;
	Sleep(1000);
}

void NineNineRandom::chooseName()
{
	switch (randomNum() % 10)
	{
	case 1:
		name += " Alice";
		break;
	case 2:
		name += " Bob";
		break;
	case 3:
		name += " Carol";
		break;
	case 4:
		name += " Dave";
		break;
	case 5:
		name += " Eve";
		break;
	case 6:
		name += " Francis";
		break;
	case 7:
		name += " Grace";
		break;
	case 8:
		name += " Hans";
		break;
	case 9:
		name += " Isabella";
		break;
	case 0:
		name += " Jason";
		break;
	}
	cout << "RandomBot �����ǳ���..." << endl;
	Sleep(500);
	cout << name << " ������˸��к���" << endl;
	Sleep(1000);
}

void NineNineRandom::chooseSkin()
{
	cout << "RandomBot ѡ��Ƥ����..." << endl;
	Sleep(1000);
}

void NineNineRandom::chooseColor()
{
	cout << "RandomBot ѡ����ɫ��..." << endl;
	Sleep(1000);
}

POINT NineNineRandom::decision(const int(*board)[9], const int* occupy, const int* available)
{
	colorPrint(name, colorNum);
	cout << " ˼����..." << endl;
	POINT p;
	int temp[9] = { 0 }, count = 0;
	for (int i = 0; i < 9; i++)
	{
		if (available[i])
		{
			temp[count] = i;
			count++;
		}
	}
	p.x = temp[randomNum() % count];
	for (int i = 0; i < count; i++) temp[i] = 0;
	count = 0;
	for (int i = 0; i < 9; i++)
	{
		if (board[p.x][i] == 0)
		{
			temp[count] = i;
			count++;
		}
	}
	p.y = temp[randomNum() % count];
	Sleep(300);
	return p;
}

//NineNinePlayerOL
NineNinePlayerOL::NineNinePlayerOL(string N, string SN, int CN, int S, int T) : NineNineAgent(N, SN, CN, S, T)
{
	winRate = 0;
	careerTotal = 0;
	system("cls");
	chooseName();
	system("cls");
	Printer::printSkinForChoose(" ", " ");
	chooseSkin();
	system("cls");
	Printer::printColorForChoose(" ", " ", 0, 0, skin);
	chooseColor();
}

void NineNinePlayerOL::chooseName()
{
	string temp;
	cout << "�������ǳƣ�";
	cin >> temp;
	name += (" " + temp);
	cout << "���" << name << "��" << endl;
	Sleep(1000);
}

void NineNinePlayerOL::chooseSkin()
{
	cout << "��ѡ����ϲ����Ƥ��" << endl;
	skin = BasicInfo::skins[rowClicked(BasicInfo::skinNum - 1, 5)];
	cout << "��ѡ����Ƥ�� " << skin << endl;
	Sleep(1000);
}

void NineNinePlayerOL::chooseColor()
{
	cout << "��ѡ����ϲ������ɫ" << endl;
	colorNum = rowClicked(BasicInfo::colorNum - 1, 5, 5, 0);
	cout << "��ѡ���� ";
	colorPrint(skin, colorNum);
	cout << " ��ɫ" << endl;
	Sleep(1000);
}

POINT NineNinePlayerOL::decision(const int(*board)[9], const int* occupy, const int* available)
{
	POINT p;
	while (1)
	{
		p = pointChosen();
		if (Judger::judgeLegal(board, available, p)) break;
	}
	return p;
}

//NineNineOpponentOL
NineNineOpponentOL::NineNineOpponentOL(SOCKET sS, string N, string SN, int CN, int S, int T, int wR, int cT, int uniN) : NineNineAgent(N, SN, CN, S, T)
{
	serverSocket = sS;
	name = N;
	skin = SN;
	colorNum = CN;
	score = S;
	total = T;
	winRate = wR;
	careerTotal = cT;
	uniNum = uniN;
}

void NineNineOpponentOL::chooseName() {}

void NineNineOpponentOL::chooseSkin() {}

void NineNineOpponentOL::chooseColor() {}

POINT NineNineOpponentOL::decision(const int(*board)[9], const int* occupy, const int* available)
{
	POINT p;
	char buffer[1024] = { 0 };
	if (recv(serverSocket, buffer, 1024, 0) == SOCKET_ERROR)
	{
		cerr << "recv error with code " << WSAGetLastError() << " !" << endl;
		system("pause");
	}
	else
	{
		int i = 0;
		bool flag = 0;
		string str, result;
		char temp[1024] = { 0 };
		for (i = 1; i < 1024; i++)
		{
			for (int j = i; j < 1024; j++)
			{
				if (buffer[j] == ':')
				{
					temp[j - i] = '\0';
					str = temp;
					i = j + 1;
					break;
				}
				temp[j - i] = buffer[j];
			}
			for (int j = i; j < 1024; j++)
			{
				if (buffer[j] == ',')
				{
					temp[j - i] = '\0';
					result = temp;
					i = j;
					break;
				}
				else if (buffer[j] == '}')
				{
					temp[j - i] = '\0';
					result = temp;
					i = j;
					flag = 1;
					break;
				}
				temp[j - i] = buffer[j];
			}
			if (str == "x") p.x = stoi(result);
			else if (str == "y") p.y = stoi(result);
			else
			{
				cerr << "NineNineOpponentOL::decision error !" << endl;
				system("pause");
			}
			if (flag) break;
		}
	}

	return p;
}

//Printer
int which(const int i, const int j)
{
	//����board_for_print��(i, j)�����ĸ����̵ķ�Χ
	if (i >= 0 and i <= 8 and j >= 0 and j <= 16) return 0;
	else if (i >= 0 and i <= 8 and j >= 17 and j <= 33) return 1;
	else if (i >= 0 and i <= 8 and j >= 34 and j <= 48) return 2;
	else if (i >= 9 and i <= 17 and j >= 0 and j <= 16) return 3;
	else if (i >= 9 and i <= 17 and j >= 17 and j <= 33) return 4;
	else if (i >= 9 and i <= 17 and j >= 34 and j <= 48) return 5;
	else if (i >= 18 and i <= 26 and j >= 0 and j <= 16) return 6;
	else if (i >= 18 and i <= 26 and j >= 17 and j <= 33) return 7;
	else if (i >= 18 and i <= 26 and j >= 34 and j <= 48) return 8;
	else return -1;
}

POINT where(const int i, const int j) 
{
	//����board_for_print��(i, j)��Ӧboard�ϵ�����
	POINT p;
	p.x = -1; p.y = -1;
	if (i == 8 or i == 10 or i == 17 or i == 19 or i == 26) return p;
	int x = 0, y = 0;
	x = (i - 2) / 9 * 3 + (j - 3) / 17;
	y = (i + 7) % 9 / 2 * 3 + (j + 14) % 17 / 4;
	if (i == 2 + 9 * (x / 3) + 2 * (y / 3) and j == 3 + 17 * (x % 3) + 4 * (y % 3))
	{
		p.x = x; p.y = y;
		return p;
	}
	else return p;
}

bool judgeArrow(const int i, const int j, const string(*board_for_print)[49])
{
	if (board_for_print[i][j] != "��") return 0;
	if ((i - 8) % 9 == 0 and (j - 7) % 17 == 0) return 1;
	return 0;
}

string Printer::board_for_print[27][49];

void Printer::resetPrintBoard() 
{
	//��ʼ���������
	int i = 0, j = 0, k = 0, l = 0;
	char x = 0;
	for (i = 0; i < 27; i++)
		for (j = 0; j < 49; j++)
			board_for_print[i][j] = " ";
	for (i = 1; i <= 19; i += 9)
		for (j = 1; j <= 35; j += 17) {
			board_for_print[i][j] = "��";
			board_for_print[i + 6][j] = "��";
			board_for_print[i][j + 12] = "��";
			board_for_print[i + 6][j + 12] = "��";
		}
	for (i = 3; i <= 21; i += 9)
		for (j = 1; j <= 35; j += 17) {
			board_for_print[i][j] = "��";
			board_for_print[i + 2][j] = "��";
			board_for_print[i][j + 12] = "��";
			board_for_print[i + 2][j + 12] = "��";
		}
	for (i = 1; i <= 19; i += 9)
		for (j = 5; j <= 39; j += 17) {
			board_for_print[i][j] = "��";
			board_for_print[i][j + 4] = "��";
			board_for_print[i + 6][j] = "��";
			board_for_print[i + 6][j + 4] = "��";
		}
	for (i = 3; i <= 21; i += 9)
		for (j = 5; j <= 39; j += 17) {
			board_for_print[i][j] = "��";
			board_for_print[i + 2][j] = "��";
			board_for_print[i][j + 4] = "��";
			board_for_print[i + 2][j + 4] = "��";
		}
	for (k = 2; k <= 20; k += 9)
		for (l = 1; l <= 35; l += 17)
			for (i = k; i <= k + 4; i += 2)
				for (j = l; j <= l + 12; j += 4)
					board_for_print[i][j] = "��";
	for (k = 1; k <= 19; k += 9)
		for (l = 3; l <= 37; l += 17)
			for (i = k; i <= k + 6; i += 2)
				for (j = l; j <= l + 8; j += 4) {
					board_for_print[i][j] = "��";
					board_for_print[i][j - 1] = "��";
					board_for_print[i][j + 1] = "��";
				}
	board_for_print[8][7] = "1";
	board_for_print[8][24] = "2";
	board_for_print[8][41] = "3";
	board_for_print[17][7] = "4";
	board_for_print[17][24] = "5";
	board_for_print[17][41] = "6";
	board_for_print[26][7] = "7";
	board_for_print[26][24] = "8";
	board_for_print[26][41] = "9";
}

void Printer::loadIntoPrintBoard(const int(*board)[9], const int* occupy, const int* available, const NineNineAgent* agent[2])
{
	int i = 0, j = 0;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			board_for_print[2 + 9 * (i / 3) + 2 * (j / 3)][3 + 17 * (i % 3) + 4 * (j % 3)] = " ";
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			if (board[i][j])
				board_for_print[2 + 9 * (i / 3) + 2 * (j / 3)][3 + 17 * (i % 3) + 4 * (j % 3)]
				= agent[board[i][j] - 1]->skin;
	for (i = 0; i < 9; i++)
		if (occupy[i] and occupy[i] != 3)
			board_for_print[8 + 9 * (i / 3)][7 + 17 * (i % 3)]
			= agent[occupy[i] - 1]->skin;
	for (i = 0; i < 9; i++)
		if (available[i])
			board_for_print[8 + 9 * (i / 3)][7 + 17 * (i % 3)] = "��";
}

void Printer::printHead(const NineNineAgent* agent[2]) 
{
	cout << "    ";
	colorPrint(agent[0]->name + " " + agent[0]->skin, agent[0]->colorNum);
	cout << "  ";
	colorPrint(to_string(agent[0]->score), agent[0]->colorNum);
	colorPrint("   V ", agent[0]->colorNum);
	colorPrint("S   ", agent[1]->colorNum);
	colorPrint(to_string(agent[1]->score), agent[1]->colorNum);
	cout << "  ";
	colorPrint(agent[1]->skin + " " + agent[1]->name, agent[1]->colorNum);
	cout << "   ��ǰΪ�� " << agent[0]->total + 1 << " ��" << endl;
}

void Printer::printBoard(const int(*board)[9], const int* occupy, const POINT last, int turn, const NineNineAgent* agent[2]) 
{
	int k = 0, l = 0;
	POINT t;
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 49; j++) {
			k = occupy[which(i, j)];//ռ��(i, j)�������̵���Һ�
			t = where(i, j);//(i, j)��Ӧ�����꣬�����ǿ��µ���Ϊ-1
			if (t.x != -1) l = board[t.x][t.y];//(i, j)��Ӧ�Ŀ��µ����Һ�
			if (k) {//����һ���ѱ�ռ�죬ֱ�Ӵ�ӡΪռ������ɫ
				if (k == 3) colorPrint(board_for_print[i][j], 8);
				else
					colorPrint(board_for_print[i][j], agent[k - 1]->colorNum);
			}
			else if (t.x != -1 and !(t.x == last.x and t.y == last.y) and l != 0)
				//���ô�Ϊ���ӵ��Ҳ�Ϊ��һ���ӣ���ӡΪ��������ɫ
				colorPrint(board_for_print[i][j], agent[l - 1]->colorNum);
			else if (judgeArrow(i, j, board_for_print))//���ô�Ϊ��Ӧλ�ü�ͷ����ӡΪ���غ������ɫ
				colorPrint(board_for_print[i][j], agent[turn]->colorNum);
			else cout << board_for_print[i][j];
		}
		cout << endl;
		if (i == 8 or i == 17 or i == 26) cout << endl;
	}
	if (last.x == 666)
	{
		colorPrint(agent[turn]->name, agent[turn]->colorNum);
		cout << " ������" << endl;
	}
	else if (last.x >= 0 and last.x <= 8 and last.y >= 0 and last.y <= 8)
	{
		colorPrint(agent[(turn + 1) % 2]->name, agent[(turn + 1) % 2]->colorNum);
		cout << " ���ڵ� " << last.x + 1 << " ������ " << last.y + 1 << " ��λ" << endl;
	}
}

void Printer::printAgentForChoose()
{
	for (int i = 1; i < BasicInfo::agentNum; i++)
		cout << i << ": " << BasicInfo::agentNames[i] << endl;
}

void Printer::printSkinForChoose(const string skin1, const string skin2)
{
	for (int i = 1; i < BasicInfo::skinNum; i++) {
		cout << i << ": " << BasicInfo::skins[i];
		if (skin1 == BasicInfo::skins[i]) cout << " (���һ��ѡ)";
		if (skin2 == BasicInfo::skins[i]) cout << " (��Ҷ���ѡ)";
		cout << endl;
	}
}

void Printer::printColorForChoose(const string skin1, const string skin2, const int colorNum1, const int colorNum2, string skin)
{
	for (int i = 1; i < BasicInfo::colorNum; i++) {
		cout << i << ": ";
		colorPrint(skin, BasicInfo::colors[i]);
		if (colorNum1 == i) colorPrint(" (���һ��ѡ)", BasicInfo::colors[i]);
		if (colorNum2 == i) colorPrint(" (��Ҷ���ѡ)", BasicInfo::colors[i]);
		cout << endl;
	}
}

void Printer::printAll(const int(*board)[9], const int* occupy, const int* available, const POINT last, int turn, const NineNineAgent* agent[2])
{
	system("cls");
	printHead(agent);
	resetPrintBoard();
	loadIntoPrintBoard(board, occupy, available, agent);
	printBoard(board, occupy, last, turn, agent);
}

//Judger
int Judger::judgeOccupy(const int(*board)[9], const int x)
{
	//����ռ��x���̵���Һţ������򷵻�0
	int i = 0;
	for (i = 0; i < 3; i++) {
		if (board[x][i * 3] != 0 and
			board[x][i * 3] == board[x][1 + i * 3] and
			board[x][i * 3] == board[x][2 + i * 3])
			return board[x][i * 3];
		if (board[x][i] != 0 and
			board[x][i] == board[x][i + 3] and
			board[x][i] == board[x][i + 6])
			return board[x][i];
	}
	if (board[x][4] != 0) {
		if (board[x][0] == board[x][4] and
			board[x][8] == board[x][4])
			return board[x][4];
		if (board[x][2] == board[x][4] and
			board[x][6] == board[x][4])
			return board[x][4];
	}
	for (int i = 0; i < 9; i++)
		if (board[x][i] == 0)
			return 0;
	return 3;
}

int Judger::judgeEnd(const int(*board)[9], const int* occupy, const int* available)
{
	//�ж���Ϸ�Ƿ���������ػ�ʤ����ƽ�ַ���-1�������ܼ�������0
	bool flag = 0;
	int i = 0, j = 0;
	for (i = 0; i < 3; i++) {
		if (occupy[i * 3] != 3 and occupy[i * 3] != 0 and occupy[i * 3] == occupy[1 + i * 3] and occupy[i * 3] == occupy[2 + i * 3]) return occupy[i * 3];
		if (occupy[i] != 3 and occupy[i] != 0 and occupy[i] == occupy[i + 3] and occupy[i] == occupy[i + 6]) return occupy[i];
	}
	if (occupy[4] != 0 and occupy[4] != 3) {
		if (occupy[0] == occupy[4] and occupy[8] == occupy[4]) return occupy[4];
		if (occupy[2] == occupy[4] and occupy[6] == occupy[4]) return occupy[4];
	}
	for (i = 0; i < 9; i++)
		if (available[i])
			for (j = 0; j < 9; j++)
				if (board[i][j] == 0)
					flag = 1;
	if (flag == 0) return -1;
	return 0;
}

int Judger::judgeLegal(const int(*board)[9], const int* available, const POINT pos)
{
	if (available[pos.x] and board[pos.x][pos.y] == 0) return 1;
	else return 0;
}

//Connector
Connector::Connector(int n)
{
	while (true)
	{
		system("cls");
		cout << "׼�������������..." << endl;
		Sleep(1000);
		if (n == 1)
		{
			short p = 0;
			string addr;
			cout << "�������������ַ��";
			cin >> addr;
			cout << "������˿ںţ�";
			cin >> p;
			serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (serverSocket == INVALID_SOCKET)
			{
				cerr << "create serverSocket error with code " << WSAGetLastError() << " !" << endl;
				closesocket(serverSocket);
			}
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(p);
			serverAddr.sin_addr.S_un.S_addr = inet_addr(addr.c_str());
		}
		else if (n == 0)
		{
			const short p = 1123;
			const char* addr = "152.136.206.64";
			Sleep(1000);
			serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (serverSocket == INVALID_SOCKET)
			{
				cerr << "create serverSocket error with code " << WSAGetLastError() << " !" << endl;
				closesocket(serverSocket);
			}
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(p);
			serverAddr.sin_addr.S_un.S_addr = inet_addr(addr);
		}

		if (connectServer() == 0)
		{
			cout << "����ʧ�ܣ�����������" << endl;
			continue;
		}
		else if(checkConnection())
		{
			system("cls");
			cout << "���ѳɹ�����!" << endl;
			break;
		}
		else
		{
			cout << "����ʧ�ܣ�����������" << endl;
			continue;
		}
	}
}

Connector::~Connector()
{
	closesocket(serverSocket);
}

bool Connector::connectServer()
{
	if (connect(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		cerr << "connect error with code: " << WSAGetLastError() << "!" << endl;
		return false;
	}
	return true;
}

bool Connector::sendData(const char* data)
{
	if (send(serverSocket, data, 1024, 0) == SOCKET_ERROR)
	{
		cerr << "send error with code " << WSAGetLastError() << " !" << endl;
		return false;
	}
	else return true;
}

bool Connector::getData(char* buffer)
{
	if (recv(serverSocket, buffer, 1024, 0) == SOCKET_ERROR)
	{
		cerr << "recv error with code " << WSAGetLastError() << " !" << endl;
		return false;
	}
	else return true;
}

bool Connector::sendPlayerInfo(NineNinePlayerOL* player)
{
	string info = "{NineNine:{PlayerInfo:{name:" + player->name + ",skin:" + player->skin
		+ ",colorNum:" + to_string(player->colorNum) + ",winRate:" + to_string(player->winRate)
		+ ",careerTotal:" + to_string(player->careerTotal) + "}}}";
	const char* p = info.c_str();
	return sendData(p);
}

bool Connector::getPlayerInfo(NineNineAgent*& opponent)
{
	char data[1024] = { 0 };
	getData(data);

	string name;
	string skin;
	int colorNum = 0;
	int winRate = 0;
	int careerTotal = 0;
	int uniNum = 0;

	int i = 0;
	bool flag = 0;
	string str, result;
	char temp[1024] = { 0 };
	for (i = 1; i < 1024; i++)
	{
		for (int j = i; j < 1024; j++)
		{
			if (data[j] == ':')
			{
				temp[j - i] = '\0';
				str = temp;
				i = j + 1;
				break;
			}
			temp[j - i] = data[j];
		}
		for (int j = i; j < 1024; j++)
		{
			if (data[j] == ',')
			{
				temp[j - i] = '\0';
				result = temp;
				i = j;
				break;
			}
			else if (data[j] == '}')
			{
				temp[j - i] = '\0';
				result = temp;
				i = j;
				flag = 1;
				break;
			}
			temp[j - i] = data[j];
		}
		if (str == "name") name = result;
		else if (str == "skin") skin = result;
		else if (str == "colorNum") colorNum = stoi(result);
		else if (str == "winRate") winRate = stoi(result);
		else if (str == "careerTotal") careerTotal = stoi(result);
		else if (str == "uniqueNum") uniNum = stoi(result);
		else
		{
			cerr << "Connector::getPlayerInfo error !" << endl;
			system("pause");
		}
		if (flag) break;
	}

	opponent = new NineNineOpponentOL(serverSocket, name, skin, colorNum, 0, 0, winRate, careerTotal, uniNum);

	return 0;
}

int Connector::getUniN()
{
	char data[1024] = { 0 };
	getData(data);
	int uniNumber = 0;
	int i = 0;
	bool flag = 0;
	string str, result;
	char temp[1024] = { 0 };
	for (i = 1; i < 1024; i++)
	{
		for (int j = i; j < 1024; j++)
		{
			if (data[j] == ':')
			{
				temp[j - i] = '\0';
				str = temp;
				i = j + 1;
				break;
			}
			temp[j - i] = data[j];
		}
		for (int j = i; j < 1024; j++)
		{
			if (data[j] == ',')
			{
				temp[j - i] = '\0';
				result = temp;
				i = j;
				break;
			}
			else if (data[j] == '}')
			{
				temp[j - i] = '\0';
				result = temp;
				i = j;
				flag = 1;
				break;
			}
			temp[j - i] = data[j];
		}
		if (str == "uniqueNum") uniNumber = stoi(result);
		else
		{
			cerr << "Connector::getUniN error !" << endl;
			system("pause");
		}
		if (flag) break;
	}
	return uniNumber;
}

bool Connector::checkConnection()
{
	char data[1024] = { 0 };
	getData(data);
	int i = 0;
	bool flag = 0;
	string str, result;
	char temp[1024] = { 0 };
	for (i = 1; i < 1024; i++)
	{
		for (int j = i; j < 1024; j++)
		{
			if (data[j] == ':')
			{
				temp[j - i] = '\0';
				str = temp;
				i = j + 1;
				break;
			}
			temp[j - i] = data[j];
		}
		for (int j = i; j < 1024; j++)
		{
			if (data[j] == ',')
			{
				temp[j - i] = '\0';
				result = temp;
				i = j;
				break;
			}
			else if (data[j] == '}')
			{
				temp[j - i] = '\0';
				result = temp;
				i = j;
				flag = 1;
				break;
			}
			temp[j - i] = data[j];
		}
		if (str == "ServerBroadcast" and result == "Connected Successfully !") return true;
		else return false;
	}
}