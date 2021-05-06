const int MAXN = ...; // число вершин
const int INF = 3e8; // константа-бесконечность

struct edge {
	int a, b, cap, flow;
};

int source; // исток
int sink; // сток
int d[MAXN], used[MAXN], q[MAXN];
vector<edge> e;
vector<int> g[MAXN];

//у прямых ребер нечетный номер
//у обратных четный
// если x прямое ребро, то обратное ему x + 1.

void add_edge(int a, int b, int cap) {
	edge e1 = { a, b, cap, 0 };
	edge e2 = { b, a, 0, 0 };
	g[a].push_back((int)e.size());
	e.push_back(e1);
	g[b].push_back((int)e.size());
	e.push_back(e2);
}

bool bfs() {	
	queue<int> q;
	fill(d, d + MAXN, -1);
	d[source] = 0;
	q.push(source);
	while (!q.empty()) {
		int v = q.front();
		q.pop();	
		for (auto id : g[v]) {
			auto to = e[id].b;
			if (d[to] == -1 && e[id].flow < e[id].cap) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}
	return d[sink] != -1;
}

int dfs(int v, int flow) {
	if (flow == 0)  return 0;	
	if (v == sink)  
		return flow;	
		for (auto id : g[v]) {
		auto to = e[id].b;
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
		if (pushed) {
			e[id].flow += pushed;
			e[id ^ 1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}

int dinic() {
	int flow = 0;
	while(bfs()) {
		int pushed;
		fill(used, used + MAXN, false);
		while (true) {
			int pushed = dfs(source, INF);
			if (!pushed)
				break;
			flow += pushed;
		}
	}
	return flow;
}
