#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;

struct info {
	int first;
	int second;
	int flag;

	info(int a, int b, int c) {
		first = a;
		second = b;
		flag = c;
	}
};

// move를 할때 블럭 단위로 해야함
int k, t, rr, cc, res, block_cnt;
vector<vector<info> > mp(10, vector<info>(10, info(0, 0, 0)));

void mark(int i) {
	if (i == 1) {
		mp[rr][cc].first = 1;
		mp[rr][cc].second = 1;
		mp[rr][cc].flag = 0;
		
		mp[rr][4].first = 1;
		mp[rr][4].second = 1;
		mp[rr][4].flag = 0;

		mp[4][cc].first = 1;
		mp[4][cc].second = 1;
		mp[4][cc].flag = 0;
	}

	else if (i == 2) {
		mp[rr][cc].first = 1;
		mp[rr][cc].second = 2;
		mp[rr][cc].flag = 0;

		mp[rr][cc + 1].first = 1;
		mp[rr][cc + 1].second = 2;
		mp[rr][cc + 1].flag = 0;
		
		mp[rr][4].first = 1;
		mp[rr][4].second = 2;
		mp[rr][4].flag = 0;

		mp[rr][5].first = 1;
		mp[rr][5].second = 2;
		mp[rr][5].flag = 0;

		mp[4][cc].first = 1;
		mp[4][cc].second = 2;
		mp[4][cc].flag = 0;

		mp[4][cc + 1].first = 1;
		mp[4][cc + 1].second = 2;
		mp[4][cc + 1].flag = 0;
	}

	else {
		mp[rr][cc].first = 1;
		mp[rr][cc].second = 3;
		mp[rr][cc].flag = 0;

		mp[rr + 1][cc].first = 1;
		mp[rr + 1][cc].second = 3;
		mp[rr + 1][cc].flag = 0;

		mp[rr][4].first = 1;
		mp[rr][4].second = 3;
		mp[rr][4].flag = 0;

		mp[rr + 1][4].first = 1;
		mp[rr + 1][4].second = 3;
		mp[rr + 1][4].flag = 0;

		mp[4][cc].first = 1;
		mp[4][cc].second = 3;
		mp[4][cc].flag = 0;

		mp[5][cc].first = 1;
		mp[5][cc].second = 3;
		mp[5][cc].flag = 0;
		// flag 얘들만 move
	}
}

void push_row(vector<vector<pair<int, int>> >& v) {
	for (int i = 0; i < 4; i++) {
		for (int j = v.size() - 1; j > 3; j--) {
			if (v[i][j].first == 1) {
				if (j + 1 > 9 || v[i][j + 1].first == 1) {
					continue;
				}

				else {
					if (v[i][j].second == 1) {
						v[i][j + 1].first = v[i][j].first;
						v[i][j + 1].second = v[i][j].second;
						v[i][j].first = 0;
						v[i][j].second = 0;
						push_row(v);
					}

					else if (v[i][j].second == 2) {
						v[i][j + 1].first = v[i][j].first;
						v[i][j + 1].second = v[i][j].second;
						v[i][j].first = 0;
						v[i][j].second = 0;
						push_row(v);
					}

					else {
						if (i > 0 && v[i][j].first == 1 && v[i - 1][j].first == 1 && v[i][j].second == 3 && v[i - 1][j].second == 3 && v[i][j + 1].first == 0 && v[i - 1][j + 1].first == 0) {
							v[i][j + 1].first = v[i][j].first;
							v[i - 1][j + 1].first = v[i - 1][j].first;
							v[i][j + 1].second = v[i][j].second;
							v[i - 1][j + 1].second = v[i - 1][j].second;

							v[i][j].first = 0;
							v[i][j].second = 0;
							v[i - 1][j].first = 0;
							v[i - 1][j].second = 0;
							push_row(v);
						}

						else if (i < 3 && v[i][j].first == 1 && v[i + 1][j].first == 1 && v[i][j].second == 3 && v[i + 1][j].second == 3 && v[i][j + 1].first == 0 && v[i + 1][j + 1].first == 0) {
							v[i][j + 1].first = v[i][j].first;
							v[i + 1][j + 1].first = v[i + 1][j].first;
							v[i][j + 1].second = v[i][j].second;
							v[i + 1][j + 1].second = v[i + 1][j].second;

							v[i][j].first = 0;
							v[i][j].second = 0;
							v[i + 1][j].first = 0;
							v[i + 1][j].second = 0;
							push_row(v);
						}
					}
				}
			}
		}
	}
}

void red() {
	//오른쪽 면으로 stack
	vector<vector<pair<int, int>> > temp_red(10, vector<pair<int, int>>(10, make_pair(0, 0)));

	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 10; j++) {
			temp_red[i][j] = mp[i][j];
		}
	}

	push_row(temp_red);

	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 10; j++) {
			mp[i][j] = temp_red[i][j];
		}
	}

	/*for (auto v : temp_red) {
		for (auto i : v) {
			cout << i << " ";
		}
		cout << "\n";
	}*/
}

void yellow() {
	//아래 면으로 stack
	vector<vector<pair<int, int>> > temp_y(10, vector<pair<int, int> >(10, make_pair(0, 0)));

	for (int i = 4; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			temp_y[3 - j][i] = mp[i][j];
			
			if (mp[i][j].second == 3) {
				temp_y[3 - j][i].second = 2;
			}

			else if (mp[i][j].second == 2) {
				temp_y[3 - j][i].second = 3;
			}
		}
	}

	push_row(temp_y);

	for (auto v : temp_y) {
		for (auto i : v) {
			cout << i.second << " ";
		}
		cout << "\n";
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 10; j++) {
			temp_y[j][3 - i] = temp_y[i][j];

			if (temp_y[i][j].second == 2) {
				temp_y[j][3 - i].second = 3;
			}

			else if (temp_y[i][j].second == 3) {
				temp_y[j][3 - i].second = 2;
			}

			temp_y[i][j] = make_pair(0, 0);
		}
	}

	for (int i = 4; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			mp[i][j] = temp_y[i][j];
		}
	}

	/*for (auto v : temp_y) {
		for (auto i : v) {
			cout << i << " ";
		}
		cout << "\n";
	}*/
}

void check_r() {
	int cnt = 0;
	vector<vector<pair<int, int>> > temp_ch(10, vector<pair<int, int> >(10, make_pair(0, 0)));

	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 10; j++) {
			temp_ch[i][j] = mp[i][j];
		}
	}

	for (int j = 6; j < 10; j++) {
		if (temp_ch[0][j].first == 1 && temp_ch[1][j].first == 1 && temp_ch[2][j].first == 1 && temp_ch[3][j].first == 1) {
			/*cout << cnt << "\n";
			for (auto v : temp_ch) {
				for (auto i : v) {
					cout << i << " ";
				}
				cout << "\n";
			}
			cout << "\n\n\n";*/
			cnt++;
			temp_ch[0][j] = make_pair(0, 0);
			temp_ch[1][j] = make_pair(0, 0);
			temp_ch[2][j] = make_pair(0, 0);
			temp_ch[3][j] = make_pair(0, 0);

			
			for (int a = 0; a < 4; a++) {
				for (int b = j; b > 4; b--) {
					temp_ch[a][b] = temp_ch[a][b - 1];
					temp_ch[a][b - 1] = make_pair(0, 0);
				}
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 4; j < 10; j++) {
					mp[i][j] = temp_ch[i][j];
				}
			}

			/*cout << cnt << "\n";
			for (auto v : temp_ch) {
				for (auto i : v) {
					cout << i << " ";
				}
				cout << "\n";
			}*/
		}
	}

	res += cnt;
}

void check_y() {
	int cnt = 0;
	vector<vector<pair<int, int>> > temp_ch(10, vector<pair<int, int> >(10, make_pair(0, 0)));

	for (int i = 4; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			temp_ch[3 - j][i] = mp[i][j];

			if (mp[i][j].second == 3) {
				temp_ch[3 - j][i].second = 2;
			}

			else if (mp[i][j].second == 2) {
				temp_ch[3 - j][i].second = 3;
			}
		}
	}

	for (int j = 6; j < 10; j++) {
		if (temp_ch[0][j].first == 1 && temp_ch[1][j].first == 1 && temp_ch[2][j].first == 1 && temp_ch[3][j].first == 1) {
			/*cout << cnt << "\n";
			for (auto v : temp_ch) {
				for (auto i : v) {
					cout << i << " ";
				}
				cout << "\n";
			}
			cout << "\n\n\n";*/

			cnt++;
			temp_ch[0][j] = make_pair(0, 0);
			temp_ch[1][j] = make_pair(0, 0);
			temp_ch[2][j] = make_pair(0, 0);
			temp_ch[3][j] = make_pair(0, 0);

			for (int a = 0; a < 4; a++) {
				for (int b = j; b > 4; b--) {
					temp_ch[a][b] = temp_ch[a][b - 1];
					temp_ch[a][b - 1] = make_pair(0, 0);
				}
			}

			/*cout << cnt << "\n";
			for (auto v : temp_ch) {
				for (auto i : v) {
					cout << i << " ";
				}
				cout << "\n";
			}
			cout << "\n\n\n";*/

			for (int i = 0; i < 4; i++) {
				for (int j = 4; j < 10; j++) {
					temp_ch[j][3 - i] = temp_ch[i][j];

					if (temp_ch[i][j].second == 2) {
						temp_ch[j][3 - i].second = 3;
					}

					else if (temp_ch[i][j].second == 3) {
						temp_ch[j][3 - i].second = 2;
					}

					temp_ch[i][j] = make_pair(0, 0);
				}
			}

			for (int i = 4; i < 10; i++) {
				for (int j = 0; j < 4; j++) {
					mp[i][j] = temp_ch[i][j];
				}
			}

			/*cout << cnt << "\n";
			for (auto v : temp_ch) {
				for (auto i : v) {
					cout << i << " ";
				}
				cout << "\n";
			}*/
		}
	}

	res += cnt;
}

void check_br() {
	int cnt = 0;
	vector<vector<pair<int, int>> > temp_ch(10, vector<pair<int, int> >(10, make_pair(0, 0)));

	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 10; j++) {
			temp_ch[i][j] = mp[i][j];
		}
	}

	for (int j = 5; j > 3; j--) {
		for (int i = 0; i < 4; i++) {
			if (temp_ch[i][j].first == 1) {
				cnt++;
				break;
			}
		}
	}

	if (cnt == 0) {
	}

	else {
		if (cnt == 1) {
			for (int j = 9; j > 8; j--) {
				for (int i = 0; i < 4; i++) {
					temp_ch[i][j].first = 0;
					temp_ch[i][j].second = 0;
				}
			}
		}

		else if (cnt == 2) {
			for (int j = 9; j > 7; j--) {
				for (int i = 0; i < 4; i++) {
					temp_ch[i][j].first = 0;
					temp_ch[i][j].second = 0;
				}
			}
		}

		/*cout << cnt << "\n";
		for (auto v : temp_ch) {
			for (auto i : v) {
				cout << i << " ";
			}
			cout << "\n";
		}
		cout << "\n\n\n";*/

		push_row(temp_ch);


		for (int i = 0; i < 4; i++) {
			for (int j = 4; j < 10; j++) {
				mp[i][j] = temp_ch[i][j];
			}
		}

		/*cout << cnt << "\n";
		for (auto v : temp_ch) {
			for (auto i : v) {
				cout << i << " ";
			}
			cout << "\n";
		}
		cout << "\n\n\n";*/
	}
}

void check_by() {
	int cnt = 0;
	vector<vector<pair<int, int>> > temp_ch(10, vector<pair<int, int> >(10, make_pair(0, 0)));

	for (int i = 4; i < 10; i++) {
		for (int j = 0; j < 4; j++) {
			temp_ch[3 - j][i] = mp[i][j];

			if (mp[i][j].second == 3) {
				temp_ch[3 - j][i].second = 2;
			}

			else if (mp[i][j].second == 2) {
				temp_ch[3 - j][i].second = 3;
			}
		}
	}

	for (int j = 5; j > 3; j--) {
		for (int i = 0; i < 4; i++) {
			if (temp_ch[i][j].first == 1) {
				cnt++;
				break;
			}
		}
	}

	if (cnt == 0) {
	}

	else {
		if (cnt == 1) {
			for (int j = 9; j > 8; j--) {
				for (int i = 0; i < 4; i++) {
					temp_ch[i][j].first = 0;
					temp_ch[i][j].second = 0;
				}
			}
		}

		else if (cnt == 2) {
			for (int j = 9; j > 7; j--) {
				for (int i = 0; i < 4; i++) {
					temp_ch[i][j].first = 0;
					temp_ch[i][j].second = 0;
				}
			}
		}

		/*cout << cnt << "\n";
		for (auto v : temp_ch) {
			for (auto i : v) {
				cout << i << " ";
			}
			cout << "\n";
		}
		cout << "\n\n\n";*/

		push_row(temp_ch);

		for (int i = 0; i < 4; i++) {
			for (int j = 4; j < 10; j++) {
				temp_ch[j][3 - i] = temp_ch[i][j];

				if (temp_ch[i][j].second == 2) {
					temp_ch[j][3 - i].second = 3;
				}

				else if (temp_ch[i][j].second == 3) {
					temp_ch[j][3 - i].second = 2;
				}

				temp_ch[i][j] = make_pair(0, 0);
			}
		}

		/*cout << cnt << "\n";
		for (auto v : temp_ch) {
			for (auto i : v) {
				cout << i << " ";
			}
			cout << "\n";
		}
		cout << "\n\n\n";*/

		for (int i = 4; i < 10; i++) {
			for (int j = 0; j < 4; j++) {
				mp[i][j] = temp_ch[i][j];
			}
		}

		/*cout << cnt << "\n";
		for (auto v : mp) {
			for (auto i : v) {
				cout << i << " ";
			}
			cout << "\n";
		}*/
	}
}

void mp_clear() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mp[i][j] = make_pair(0, 0);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	freopen("input.txt", "rt", stdin);

	cin >> k;

	while (k--) {
		vector<vector<int> > temp(4, vector<int>(4, 0));

		cin >> t >> rr >> cc;
		//마지막에 map의 파란 영역 꼭 초기화 하기

		mark(t);

		red();
		yellow();

		cout << "move: \n";
		for (auto v : mp) {
			for (auto i : v) {
				cout << i.second << " ";
			}
			cout << "\n";
		}

		check_r();
		check_y();

		cout << "check: \n";
		for (auto v : mp) {
			for (auto i : v) {
				cout << i.second << " ";
			}
			cout << "\n";
		}

		check_br();
		check_by();

		cout << "boundary: \n";
		for (auto v : mp) {
			for (auto i : v) {
				cout << i.second << " ";
			}
			cout << "\n";
		}

		mp_clear();

		cout << "final: \n";
		for (auto v : mp) {
			for (auto i : v) {
				cout << i.second << " ";
			}
			cout << "\n";
		}
		cout << "\n\n\n";
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (mp[i][j].first == 1) {
				block_cnt++;
			}
		}
	}

	cout << res << "\n";
	cout << block_cnt << "\n";
	return 0;
}