vector<vector<int>> g, gr;
 
vector<int> c, order;
vector<bool>used;
 
int comp = 0;
 
void dfs1(int v)
{
	used[v] = true;
	for (auto to : g[v])
		if (!used[to])
			dfs1(to);
	order.pb(v);
}
 
void dfs2(int v)
{
	used[v] = true;
	c[v] = comp;
	for (auto to : gr[v])
		if (!used[to])
			dfs2(to);
}
 
void build_condensation()
{
	fill(all(used), false);
 
	for (int v = 0; v < g.size(); v++)
		if (!used[v])
			dfs1(v);
 
	fill(all(used), false);
	reverse(all(order));
 
	for (auto v : order)
		if (!used[v])
		{
			dfs2(v);
			comp++;
		}
}
