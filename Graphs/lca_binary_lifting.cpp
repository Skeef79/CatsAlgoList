const int LOG = 20;
int n;

vector<vector<int>> g;
vector<int> lvl;
vector<vector<int>> jump;

void dfs(int v, int level=0, int p = 0)
{
	lvl[v] = level;
	jump[v][0] = p;

	for (auto to : g[v])
		if (to != p)
			dfs(to, level + 1, v);
}

void InitJump()
{
	for (int j = 1; j < LOG; j++)
		for (int v = 0; v < n; v++)
			jump[v][j] = jump[jump[v][j - 1]][j - 1];

}

int lca(int u, int v)
{
	if (lvl[u] > lvl[v])
		swap(u, v);

	for (int k = LOG - 1; k >= 0; k--)
		if (lvl[jump[v][k]] >= lvl[u])
			v = jump[v][k];

	if (v == u)
		return u;

	for (int k = LOG - 1; k >= 0; k--)
		if (jump[v][k] != jump[u][k])
		{
			v = jump[v][k];
			u = jump[u][k];
		}

	return jump[u][0];
}
