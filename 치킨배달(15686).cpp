#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 999999999

struct Data {
	int y, x, dist = INF;
};
bool visited[101];
int N, M;
int minValue = INF;
vector<Data> chicken;
vector<Data> house;

int dist(Data d1, Data d2) {
	int distY = d1.y - d2.y;
	int distX = d1.x - d2.x;
	distY = distY > 0 ? distY : (-1)*distY;
	distX = distX > 0 ? distX : (-1)*distX;
	return distY + distX;
}


void DFS(int cnt, int start, vector<Data> house, int finalSum) {
	if (cnt == M) {
		minValue = min(minValue, finalSum);
		return;
	}

	for (int i = start; i < chicken.size(); ++i) {
		int recover[101];
		finalSum = 0;
		if (visited[i])	return;
		visited[i] = true;

		for (int j = 0; j < house.size(); ++j) {
			recover[j] = house[j].dist;
			int d = dist(chicken[i], house[j]);
			if (d < house[j].dist) {
				house[j].dist = d;
			}
			finalSum += house[j].dist;
		}

		visited[i] = true; // 조합을 구현하기 위함 (전역변수에 선언해도 됨)
		DFS(cnt + 1, start + 1, house, finalSum);
		visited[i] = false;

		for (int j = 0; j < house.size(); ++j)
			house[j].dist = recover[j];
	}
}

int main() {
	cin.tie(0), ios_base::sync_with_stdio(0);

	cin >> N >> M;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			int tmp;
			cin >> tmp;
			if (tmp == 1)	house.push_back({ i, j });
			else if (tmp == 2)	chicken.push_back({ i, j });
		}

	DFS(0, 0, house, 0);
	cout << minValue << '\n';
}