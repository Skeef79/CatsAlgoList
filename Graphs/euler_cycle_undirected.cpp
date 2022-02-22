const int N = 1e5 + 1010;
vec<int>g[N];
int ed[4 * N][2];
bool used[4 * N];

int id = 0;
void add_edge(int u, int v) {
	ed[id][0] = u;
	ed[id][1] = v;
	g[u].pb(id);
	g[v].pb(id);
	id++;
}

int get_other(int id, int v) {
	return ed[id][0] ^ ed[id][1] ^ v;
}

vec<int>order;

void dfs(int v) {
	while (!g[v].empty()) {
		int id = g[v].back();
		g[v].pop_back();
		if (used[id])
			continue;
		used[id] = true;
		dfs(get_other(id, v));
		order.pb(id);
	}
}

//ответ - список id ребер, граф это тоже список id (ребра в него добавляются через add_edge)
