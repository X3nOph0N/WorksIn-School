#include<iostream>
#include<vector>
#include<array>
#include<random>
#include<ctime>
using namespace std;

//定义皇后数量
const int queenNum = 8;

//冲突检测次数
static int checkNum = 0;


//最大随机次数
static int maxRoundNum = 20;

/*
输入：存放皇后的数组，下标为行数，取值为列数
返回值： /
描述：执行打印功能，打印出皇后最终的摆放位置。
*/
void printResult(vector<int> eightQueenColumnResult, int checkNum);

/*
* 输入：
* 输出：存放皇后的数组，下标为行数，取值为列数
*随机摆放八个皇后的位置，保证不在同一行同一列
*/
vector<int> randomInitQueenColumn();

/*
*输入：存放皇后的数组
*输出：true:正确结果 false:错误结果
*/
bool checkQueenColumn(vector<int> queenColumn);

/*
*输入：第一个参数为存放皇后的数组，下标为行数，取值为列数；第二个参数为代表当前已经放好的皇后数量；
*输出：true：当前皇后无冲突 false：当前皇后有冲突
*/
bool checkCurrentColumn(vector<int> ,int);

/*
*输入：存放皇后的数组，下标为行数，取值为列数
*输出：当前总共能够相互攻击的皇后数量
*/
int evaluateConflictNumber(vector<int>);
/*
*约束满足问题的回溯算法（找到一个结果即可）
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
			else//判断当前行中可能是否存在列满足在这个列上放置皇后能够使这个皇后和其他皇后不冲突
			{
				hasSolution = true;
				break;
			}
		}
		if (hasSolution) //如果有，则currentRaw+=1，在下一列进行搜索
		{
			continue;
		}
		else //否则返回上一行，将上一行的当前列标为冲突并搜索上一行中能够满足皇后和其他皇后不冲突的列
		{
			ansColumn[currentRaw] = 0;
			ansColumn[currentRaw-1] += 1;
			currentRaw -= 2;
		}
	}
	//如果当前行已经是最后一行并且找到了满足在这个列上放置皇后能够满足这个皇后和其他皇后不冲突，则说明找到答案，将当前ansColumn作为函数返回值返回
	return ansColumn;
}

/*
*约束满足问题的最小冲突检测算法（找到一个结果即可）
*/
vector<int> minConflicts() 
{
	vector<int> initQueenColumn;
		initQueenColumn = randomInitQueenColumn();//随机在棋盘的八个位置上放上皇后
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
			}//找到当前所有对单个皇后在一行上的移动中使得冲突最小的移动，在这些移动中随机选择一步执行，再次重复该步直到无法找到这样的移动或者达到移动步数上限
			if (currentBestMovement.size()==0) 
			{//如果不存在这样的移动说明已经得到了答案或者当前状态为局部极小值，返回initQueenColumn
				break;
			}
		int nextStep = rand() % currentBestMovement.size();
		initQueenColumn[currentBestMovement[nextStep][0]] = currentBestMovement[nextStep][1];
		}
		//如果达到移动步数上限，则返回initQueenColumn
	return initQueenColumn;
}


int main() {
	srand(static_cast<int>(time(NULL)));
	while (true) {
		int type;
		cout << "请在此处输入调用的算法：" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "1: 回溯法" << endl;
		cout << "2: 最小冲突检测法" << endl;
		cout << "0:退出" << endl;
		cout << "-----------------------------------------------------" << endl;
		cin >> type;
		while (type < 0 && type>2) {
			cout << "输入类型有误，请重新输入：" << endl;
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
				cout << "正确结果" << endl;
				printResult(queenColumnResult,checkNum);
			}
			else {
				cout << "错误结果" << endl;
				printResult(queenColumnResult, checkNum);
			}
		}
		else if (type == 2) {
			vector<int> queenColumnResult = minConflicts();
			bool result = checkQueenColumn(queenColumnResult);
			if (result) {
				cout << "正确结果" << endl;
				printResult(queenColumnResult, checkNum);
			}
			else {
				cout << "错误结果" << endl;
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
	//初始化N个皇后对应的R数组为0~N-1的一个排列，即没有任意皇后同列，也没有任何皇后同行
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
	cout << "---------------------皇后位置摆放结果如下-----------------" << endl;
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
	cout << "冲突检测次数："<< checkNum << endl;
}






