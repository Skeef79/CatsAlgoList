//tested on https://codeforces.com/gym/100131 (N)

vector<vector<int>>g;
vector<bool>used;
vector<int> tin, fup, cut_points;
int timer = 0;

void dfs(int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	bool ok = false;
	int cnt = 0;

	for (auto to : g[v]) {
		if (to == p)
			continue;
		if (used[to]) 
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			cnt++;
			if (fup[to] >= tin[v])
				ok = true;
		}
	}

	if (p == -1 && cnt>1 || p != -1 && ok)
		cut_points.pb(v);
}
