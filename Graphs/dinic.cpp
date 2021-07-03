struct edge {
	int a, b, f, c;
};

int n, m, s, t;
vec<vec<int>>g;
vec<edge> e;
vec<int>pt;
vec<int>d;

//у прямых ребер четный номер, у обратных нечетный

void add_edge(int a, int b, int c) {
	e.pb({ a, b, 0, c });
	g[a].pb(szof(e) - 1);
	e.pb({ b, a, 0, 0 });
	g[b].pb(szof(e) - 1);
}

bool bfs() {
	queue<int>q;
	fill(all(d), -1);
	q.push(s);
	d[s] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto id : g[v]) {
			int to = e[id].b;
			if (d[to] == -1 && e[id].f < e[id].c) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}
	return d[t] != -1;
}

int dfs(int v, int flow) {
	if (flow == 0)
		return 0;

	if (v == t)
		return flow;

	for (; pt[v] < szof(g[v]); pt[v]++) {
		int id = g[v][pt[v]];
		int to = e[id].b;
		if (d[to] == d[v] + 1 && e[id].f < e[id].c) {
			int pushed = dfs(to, min(flow, e[id].c - e[id].f));
			if (pushed) {
				e[id].f += pushed;
				e[id ^ 1].f -= pushed; 
				return pushed;
			}
		}
	}

	return 0;
}

ll dinic() {
	ll ans = 0;
	int f;
	while (bfs()) {
		fill(all(pt), 0);
		while (f = dfs(s, INF))
			ans += f;
	}
	return ans;
}

void init() {
	g.resize(n);
	d.resize(n);
	pt.resize(n);
}

//для неориентированных графов можно либо добавлять два ребра, либо поменять capacity у обратного на c
