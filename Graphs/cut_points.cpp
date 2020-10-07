vector<vector<int>>g;
vector<int> tin, fup;
vector<bool>used;
vector<int> cut_points;

int timer = 0;

void dfs(int v, int p = -1)
{
	used[v] = true;
	tin[v] = fup[v] = timer++;
	
	bool ok = true; // true - если это не точка сочлинения
	int cnt = 0; //считаем, сколько ребер есть из корня в дереве дфса

	for (auto to : g[v])
	{
		if (to == p)
			continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else
		{
			cnt++;
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			// если хотя бы одно ребро ведет в вершину v или ее потомка, то это точка сочленения
			if (fup[to] >= tin[v]) 
				ok = false;
		}
	}
	if (p == -1)
	{
		if (cnt > 1)
			cut_points.pb(v);
	}
	else
		if (!ok)
			cut_points.pb(v);
}
