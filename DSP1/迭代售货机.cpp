#include<iostream>
#include<string>
using namespace std;
int ans10[63]{};
int changeWays(int x) {
	for (int i = 0; i < x; i++) {
		if ((x - i - 1) % 25 == 0)
			for (int j = 0; j < (i + 1) / 10 + 1&&j<6; j++) {
				//ans10[i] += 1 + (i + 1 - j * 10) / 5;
				if (i + 1 - j * 10 == 0) {
					continue;
				}
				if (i + 1 - j * 10 < 5) {
					ans10[i] += 1; 
					continue;
				}
				if ((i + 1 - j * 10) % 5 == 0&&(i+1-j*10)<30&& (i + 1 - j * 10) != 0) {
					ans10[i] += 2;
					continue;
				}
				if (i + 1 - j * 10 > 30)
					continue;
				ans10[i] += 1;
			}
	}
	int t = 0;
	for (int j = 0; j < x / 25 + 1; j++) {
		if (x - 1 - j * 25 >=0) {
			t += ans10[x - 1 - j * 25];
			continue;
		}
			t += 1;
	}
	return t;
}
string bestChangeWay(int i_nM) {
	int a = i_nM / 25;
	i_nM %= 25;
	int b = i_nM / 10;
	i_nM %= 10;
	int c = i_nM / 5;
	i_nM %= 5;
	int d = i_nM;
	string t_ans = to_string(a) + " 25 cents coin(s) " + to_string(b) + " 10 cents coin(s) " + to_string(c) + " 5 cents coin(s) " + to_string(d) + " 1 cents coin(s)"
		+ "\nIn total " + to_string(a + b + c + d) + " coin(s)";
	return t_ans;
}

int main() {
	int t;
	while (cin >> t) {
		cout << changeWays(t) << endl;
		cout << bestChangeWay(t) << endl;
	}
	return 0;
}