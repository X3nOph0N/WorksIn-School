#include<iostream>
#include<vector>
#include<array>
#include<random>
#include<ctime>
using namespace std;

//����ʺ�����
const int queenNum = 8;

//��ͻ������
static int checkNum = 0;


//����������
static int maxRoundNum = 20;

/*
���룺��Żʺ�����飬�±�Ϊ������ȡֵΪ����
����ֵ�� /
������ִ�д�ӡ���ܣ���ӡ���ʺ����յİڷ�λ�á�
*/
void printResult(vector<int> eightQueenColumnResult, int checkNum);

/*
* ���룺
* �������Żʺ�����飬�±�Ϊ������ȡֵΪ����
*����ڷŰ˸��ʺ��λ�ã���֤����ͬһ��ͬһ��
*/
vector<int> randomInitQueenColumn();

/*
*���룺��Żʺ������
*�����true:��ȷ��� false:������
*/
bool checkQueenColumn(vector<int> queenColumn);

/*
*���룺��һ������Ϊ��Żʺ�����飬�±�Ϊ������ȡֵΪ�������ڶ�������Ϊ����ǰ�Ѿ��źõĻʺ�������
*�����true����ǰ�ʺ��޳�ͻ false����ǰ�ʺ��г�ͻ
*/
bool checkCurrentColumn(vector<int> ,int);

/*
*���룺��Żʺ�����飬�±�Ϊ������ȡֵΪ����
*�������ǰ�ܹ��ܹ��໥�����Ļʺ�����
*/
int evaluateConflictNumber(vector<int>);
/*
*Լ����������Ļ����㷨���ҵ�һ��������ɣ�
*/
vector<int> bactrackDFS()
{
	vector<int>ansColumn;
	ansColumn.assign(8, 0);
	for (int currentRaw = 0; currentRaw < 8; currentRaw++) 
	{
		bool hasSolution = false;
		for (int possibleColumn = ansColumn[currentRaw]; possibleColumn < 8; possibleColumn++) 
		{
			bool isConflict = false;
			for (int preRaw = 0; preRaw < currentRaw; preRaw++) 
			{
				if (checkCurrentColumn(ansColumn,currentRaw))
				{
					isConflict = true;
					break;
				}
			}
			if (isConflict) 
			{
				ansColumn[currentRaw]++;
				continue;
			}
			else//�жϵ�ǰ���п����Ƿ������������������Ϸ��ûʺ��ܹ�ʹ����ʺ�������ʺ󲻳�ͻ
			{
				hasSolution = true;
				break;
			}
		}
		if (hasSolution) //����У���currentRaw+=1������һ�н�������
		{
			continue;
		}
		else //���򷵻���һ�У�����һ�еĵ�ǰ�б�Ϊ��ͻ��������һ�����ܹ�����ʺ�������ʺ󲻳�ͻ����
		{
			ansColumn[currentRaw] = 0;
			ansColumn[currentRaw-1] += 1;
			currentRaw -= 2;
		}
	}
	//�����ǰ���Ѿ������һ�в����ҵ���������������Ϸ��ûʺ��ܹ���������ʺ�������ʺ󲻳�ͻ����˵���ҵ��𰸣�����ǰansColumn��Ϊ��������ֵ����
	return ansColumn;
}

/*
*Լ�������������С��ͻ����㷨���ҵ�һ��������ɣ�
*/
vector<int> minConflicts() 
{
	vector<int> initQueenColumn;
		initQueenColumn = randomInitQueenColumn();//��������̵İ˸�λ���Ϸ��ϻʺ�
		int currentConflictQueens = evaluateConflictNumber(initQueenColumn);
		for (int steps = 0; steps < maxRoundNum; steps++)
		{
			currentConflictQueens = evaluateConflictNumber(initQueenColumn);
			array<int, 2>movement;
			vector<array<int, 2>>currentBestMovement;
			for (int i = 0; i < 8; i++) 
			{
				for (int j = 0; j < 8; j++) 
				{
					movement = { i,j };
					vector<int>nextQueenColumn = initQueenColumn;
					nextQueenColumn[movement[0]] = movement[1];
					if (evaluateConflictNumber(nextQueenColumn) <= currentConflictQueens) 
					{
						currentBestMovement.push_back(movement);
					}
				}
			}//�ҵ���ǰ���жԵ����ʺ���һ���ϵ��ƶ���ʹ�ó�ͻ��С���ƶ�������Щ�ƶ������ѡ��һ��ִ�У��ٴ��ظ��ò�ֱ���޷��ҵ��������ƶ����ߴﵽ�ƶ���������
			if (currentBestMovement.size()==0) 
			{//����������������ƶ�˵���Ѿ��õ��˴𰸻��ߵ�ǰ״̬Ϊ�ֲ���Сֵ������initQueenColumn
				break;
			}
		int nextStep = rand() % currentBestMovement.size();
		initQueenColumn[currentBestMovement[nextStep][0]] = currentBestMovement[nextStep][1];
		}
		//����ﵽ�ƶ��������ޣ��򷵻�initQueenColumn
	return initQueenColumn;
}


int main() {
	srand(static_cast<int>(time(NULL)));
	while (true) {
		int type;
		cout << "���ڴ˴�������õ��㷨��" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "1: ���ݷ�" << endl;
		cout << "2: ��С��ͻ��ⷨ" << endl;
		cout << "0:�˳�" << endl;
		cout << "-----------------------------------------------------" << endl;
		cin >> type;
		while (type < 0 && type>2) {
			cout << "���������������������룺" << endl;
			cin >> type;
			break;
		}
		checkNum = 0;
		cout << "----------------------START--------------------------" << endl;
		cout << endl;
		if (type == 1) {
			vector<int>queenColumnResult( bactrackDFS());
			bool result = checkQueenColumn(bactrackDFS());
			if (result) {
				cout << "��ȷ���" << endl;
				printResult(queenColumnResult,checkNum);
			}
			else {
				cout << "������" << endl;
				printResult(queenColumnResult, checkNum);
			}
		}
		else if (type == 2) {
			vector<int> queenColumnResult = minConflicts();
			bool result = checkQueenColumn(queenColumnResult);
			if (result) {
				cout << "��ȷ���" << endl;
				printResult(queenColumnResult, checkNum);
			}
			else {
				cout << "������" << endl;
				printResult(queenColumnResult, checkNum);
			}
		}
		else {
			return 0;
		}
		cout << "----------------------END ---------------------------" << endl;
		cout << endl;
	}
	return 0;
}

bool checkQueenColumn(vector<int> queenColumn) {
	if (queenColumn.size() != queenNum)
		return false;
	checkNum++;
	for (int i = 0; i < queenNum; i++) {
		for (int j = i + 1; j < queenNum; j++) {
			if (queenColumn[i] == queenColumn[j])
				return false;
			if (abs(i - j) == abs(queenColumn[i] - queenColumn[j]))
				return false;
		}
	}
	return true;
}

bool checkCurrentColumn(vector<int> currentColumn,int currentRaw) {
	checkNum++;

	bool isConflict = false;
	for (int i = 0; i < currentRaw; i++) {
		if (currentColumn[i] == currentColumn[currentRaw]||currentColumn[i]+i==currentColumn[currentRaw]+ currentRaw || currentColumn[i] - i == currentColumn[currentRaw] - currentRaw) {
			isConflict = true;
			break;
		}
	}
	return isConflict;
}

int evaluateConflictNumber(vector<int>currentColumn) {
	checkNum++;
	int sum = 0;
	for (int i = 0; i < 8; i++){
		for (int j = i + 1; j < 8; j++) {
			if (currentColumn[i] == currentColumn[j] || currentColumn[i] + i == currentColumn[j] + j || currentColumn[i] - i == currentColumn[j] - j) {
				sum++;
		}
		}
	}
	return sum;
}

vector<int> randomInitQueenColumn() {
	vector<int> randomQueenColumn = vector<int>();
	for (int i = 0; i < queenNum; i++) {
		randomQueenColumn.push_back(i);
	}
	//��ʼ��N���ʺ��Ӧ��R����Ϊ0~N-1��һ�����У���û������ʺ�ͬ�У�Ҳû���κλʺ�ͬ��
	for (int i = 0; i <= queenNum - 2; i++) {
		/*srand((int)time(0));*/
		int randomNum = rand() % (queenNum - i) + i;
		int temp = randomQueenColumn[i];
		randomQueenColumn[i] = randomQueenColumn[randomNum];
		randomQueenColumn[randomNum] = temp;
	}
	return randomQueenColumn;
}

void printResult(vector<int> eightQueenColumnResult, int checkNum)
{
	cout << "---------------------�ʺ�λ�ðڷŽ������-----------------" << endl;
	cout << endl;
	for (int i = 0; i < eightQueenColumnResult.size(); i++) {
		switch (eightQueenColumnResult[i]) {
		case 0:
			cout << "Q * * * * * * *" << endl;
			break;
		case 1:
			cout << "* Q * * * * * *" << endl;
			break;
		case 2:
			cout << "* * Q * * * * *" << endl;
			break;
		case 3:
			cout << "* * * Q * * * *" << endl;
			break;
		case 4:
			cout << "* * * * Q * * *" << endl;
			break;
		case 5:
			cout << "* * * * * Q * *" << endl;
			break;
		case 6:
			cout << "* * * * * * Q *" << endl;
			break;
		case 7:
			cout << "* * * * * * * Q" << endl;
			break;
		}

	}
	cout << "��ͻ��������"<< checkNum << endl;
}






