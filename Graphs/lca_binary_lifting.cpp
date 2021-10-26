const int LOG = 20;
vec<int>lvl, tin, tout;
vec<vec<int>>g;
vec<vec<int>>jump;

int timer = 0;

void dfs(int v, int p = 0, int level = 0) {
	lvl[v] = level;
	jump[v][0] = p;
	tin[v] = timer++;

	for (int k = 1; k < LOG; k++)
		jump[v][k] = jump[jump[v][k - 1]][k - 1];

	for (auto to : g[v]) {
		if (to == p)
			continue;
		dfs(to, v);
	}
	tout[v] = timer++;
}

bool isAncestor(int u, int v) {
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
	if (isAncestor(u, v))
		return u;
	if (isAncestor(v, u))
		return v;
	
	for (int k = LOG - 1; k >= 0; k--)
		if (!isAncestor(jump[v][k], u))
			v = jump[v][k];

	return jump[v][0];
}
