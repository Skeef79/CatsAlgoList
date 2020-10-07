vector<vector<int>>g;
vector<int> tin, fup;
vector<bool>used;
int timer = 0;

vector<pii> bridges;

void dfs(int v, int p = -1)
{
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (auto to : g[v])
	{
		if (to == p)
			continue;

		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else
		{
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
				bridges.pb({ v,to });
		}
	}
}
