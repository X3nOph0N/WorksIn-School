#include<iostream>
#include<string>
using namespace std;
int ans = 0;
int RchangeWays(int x, int flag) {
	if (flag == 0) {
		if (x == 0)return 1;
		int t = 0;
		for (int j = 0; j <x / 10 + 1 && j < 6; j++) {
					if (x - j * 10 == 0)
						continue;
					if (x - j * 10 < 5) {
						t += 1;
						continue;
					}
					if ((x - j * 10) % 5 == 0 && (x - j * 10) < 30 && (x - j * 10) != 0) {
						t += 2;
						continue;
					}
					if (x - j * 10 > 30)
						continue;
					t += 1;
				}
		return t;
	}

	if (flag == 1) {
		int t1 = 0;
		for (int j = 0; j < x / 25 + 1; j++) {
			if (x  - j * 25 >= 0) {
				t1 += RchangeWays(x - j * 25, 0);
				continue;
			}
		}
		return t1;
	}
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
		
		cout << RchangeWays(t, 1) << endl;
		cout << bestChangeWay(t) << endl;
	}
	return 0;
}