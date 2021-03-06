#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

class LCA {
public:
	int n;
	int deep;
	int parentsdeep;
	unordered_map<int, vector<int>> tree;
	vector<vector<int>> parents;
	vector<int> depth;

public:
	void init() {
		this->deep = 1;
		this->parentsdeep = 1;
		this->tree.clear();
		this->parents.clear();
		this->depth.clear();
	}
	void makeTree() {
		cin >> this->n;
		this->depth.resize(this->n + 1);
		this->parents.push_back(vector<int>(this->n + 1, 0));
		for (int i = 1; i < n; i++) {
			int n1, n2;
			cin >> n1 >> n2;
			this->tree[n1].push_back(n2);
			this->tree[n2].push_back(n1);
		}
	}
	void bfs() {
		int visited[this->n + 1]{};
		queue<int> q;
		q.push(1);
		visited[1] = 1;
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++) {
				int node = q.front();
				for (int j = 0; j < this->tree[node].size(); j++) {
					if (!visited[this->tree[node][j]]) {
						q.push(this->tree[node][j]);
						visited[this->tree[node][j]] = 1;
						this->parents[0][this->tree[node][j]] = q.front();
						this->depth[this->tree[node][j]] = this->deep;
					}
				}
				q.pop();
			}
			this->deep++;
		}
	}
	void makeSparseTable() {
		int expo = 1;
		while (this->parentsdeep <= this->deep) {
			this->parents.push_back(vector<int>(n + 1, 0));
			for (int i = this->n; i >= 1; i--) {
				this->parents[expo][i] = this->parents[expo - 1][this->parents[expo - 1][i]];
			}
			expo++;
			this->parentsdeep <<= 1;
		}
	}
	void query() {
		int m;
		cin >> m;
		while (m--) queryExecute();
	}
	int difftoequal(int n1, int n2) {
		int expo = 1, diff = this->depth[n2] - this->depth[n1];
		while (diff) {
			if (diff % 2) n1 = this->parents[expo - 1][n1];
			expo++;
			diff /= 2;
		}
		return n1;
	}
	void queryExecute() {
		int n1, n2, expo = 1;
		cin >> n1 >> n2;
		if (this->depth[n1] > this->depth[n2]) n1 = difftoequal(n1, n2);
		else if (this->depth[n1] < this->depth[n2]) n2 = difftoequal(n2, n1);
		if (n1 != n2) {
			expo = 0;
			while (1) {
				while (this->parents[expo][n1] != this->parents[expo][n2]) expo++;
				if (expo) {
					n1 = this->parents[expo - 1][n1];
					n2 = this->parents[expo - 1][n2];
					expo = 0;
				}
				else {
					n1 = this->parents[expo][n1];
					n2 = this->parents[expo][n2];
					break;
				}
			}
		}
		cout << n1 << '\n';
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	LCA lca;
	lca.init();
	lca.makeTree();
	lca.bfs();
	lca.makeSparseTable();
	lca.query();
	return 0;
}