#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
int minValue = 2000000000;
int N;
int arr[21][21];

void DFS(bool isSelect[], int n, int cur) {
	
	bool recover[21];
	for (int i = 1; i <= N; i++)
		recover[i] = isSelect[i];

	if (n == N/2) {

		int team1 = 0;
		int team2 = 0;
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (isSelect[i] && isSelect[j]) 
					team1 += arr[i][j];
				else if((!isSelect[i] && !isSelect[j]))
					team2 += arr[i][j];
		minValue = min(minValue, abs(team2 - team1));

		return;
	}

	// DFS -> 조합 
	for (int k = cur; k <= N; k++) { // 현재 인덱스 부터 진행 -> 한칸씩 앞으로.. 끝까지
		if (isSelect[k]) continue; // 이미 선택했으면 pass
		isSelect[k] = true; // 선택
		DFS(isSelect, n + 1, k); // 선택한 것 누적한 후, 다음 것 반복.
		isSelect[k] = false; // 종료 후, 복원시킴(이전에 종료되었던 자료 복구) 
		 					//-> 이유 : isSelect는 call by reference이므로 종료할 때의 데이터도 남아있음.
	}
	//

}

int main() {
	cin.tie(0), ios_base::sync_with_stdio(0);
	cin >> N;
	
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> arr[i][j];

	bool isSelect[21] = { 0, };

	DFS(isSelect, 0, 1);
	cout << minValue << '\n';
}