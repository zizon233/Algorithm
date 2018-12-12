#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	int n, m, deep = 1, parents[19][100001] = { 0 }, visited[100001] = { 0 }, depth[100001] = { 0 }, k = 1, check = 2;
	vector<int> arr[100001];
	queue<int> bfs;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b;
		cin >> a >> b;
		arr[a].push_back(b);
		arr[b].push_back(a);
	}
	bfs.push(1);
	visited[1] = 1;
	while (!bfs.empty()) {
		int temp = bfs.size();
		for (int i = 0; i < temp; i++) {
			for (int j = 0; j < arr[bfs.front()].size(); j++) {
				if (!visited[arr[bfs.front()][j]]) {
					bfs.push(arr[bfs.front()][j]);
					visited[arr[bfs.front()][j]] = 1;
					parents[0][arr[bfs.front()][j]] = bfs.front();
					depth[arr[bfs.front()][j]] = deep;
				}
			}
			bfs.pop();
		}
		deep++;
	}
	while (true) {
		for (int i = n; i >= 1; i--) {
			parents[k][i] = parents[k - 1][parents[k - 1][i]];
		}
		k++;
		check <<= 1;
		if (check>deep) break;
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		if (depth[a] > depth[b]) {
			int temp = depth[a] - depth[b];
			k = 1;
			while (temp > 0) {
				if (temp % 2 == 1) {
					a = parents[k - 1][a];
				}
				k++;
				temp /= 2;
			}
		}
		else if (depth[a] < depth[b]) {
			int temp = depth[b] - depth[a];
			k = 1;
			while (temp > 0) {
				if (temp % 2 == 1) {
					b = parents[k - 1][b];
				}
				k++;
				temp /= 2;
			}
		}
		if (a != b) {
			k = 0;
			while (true) {
				while (parents[k][a] != parents[k][b]) {
					k++;
				}
				if (k == 0) {
					a = parents[k][a];
					b = parents[k][b];
					break;
				}
				else {
					a = parents[k - 1][a];
					b = parents[k - 1][b];
				}
				k = 0;
			}
		}
		cout << a << '\n';
	}
	return 0;
}