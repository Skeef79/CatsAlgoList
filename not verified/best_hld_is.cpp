int n;
vec<int>a, b, sz, pos, head, depth, p;
vec<vec<int>>g;
int cur_pos = 0;

const int N = 1e5 + 1010;
vec<int> t[4 * N];

void build(int v, int vl, int vr) {
	if (vl == vr) {
		t[v] = { a[vl] };
		return;
	}

	int vm = (vl + vr) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm + 1, vr);
	merge(all(t[2 * v + 1]), all(t[2 * v + 2]), back_inserter(t[v]));
}

int query(int v, int vl, int vr, int l, int r, int x) {
	if (r < vl || vr < l)
		return 0;
	if (vl >= l && vr <= r)
		return upper_bound(all(t[v]), x) - lower_bound(all(t[v]), x);
	int vm = (vl + vr) / 2;
	return query(2 * v + 1, vl, vm, l, r, x) + query(2 * v + 2, vm + 1, vr, l, r, x);
}

int tree_query(int l, int r, int x) {
	return query(0, 0, n - 1, l, r, x);
}

void dfs_sz(int v, int pr = -1) {
	sz[v] = 1;
	p[v] = pr;
	for (auto &to : g[v])
		if (to != pr) {
			depth[to] = depth[v] + 1;
			dfs_sz(to, v);
			sz[v] += sz[to];
			if (sz[to] > sz[g[v][0]])
				swap(g[v][0], to);
		}
}

void dfs_hld(int v, int pr = -1) {
	pos[v] = cur_pos++;
	for (auto to : g[v])
		if (to != pr) {
			head[to] = (to == g[v][0] ? head[v] : to);
			dfs_hld(to, v);
		}
}

int query(int u, int v, int x) {
	int ans = 0;
	for (; head[u] != head[v]; v = p[head[v]]) {
		if (depth[head[u]] > depth[head[v]])
			swap(u, v);
		ans += tree_query(pos[head[v]], pos[v],x);
	}
	if (depth[u] > depth[v])
		swap(u, v);
	ans += tree_query(pos[u], pos[v], x);
	return ans;
}

void init() {
	sz.resize(n);
	pos.resize(n);
	head.resize(n);
	depth.resize(n);
	p.resize(n);
	b.resize(n);

	dfs_sz(0);
	dfs_hld(0);
	
	for (int i = 0; i < n; i++)
		b[pos[i]] = a[i];

	a = b;
	build(0, 0, n - 1);
}


void solve() {
	int q;
	cin >> n >> q;
	a.resize(n);
	g.resize(n);

	for (int i = 0; i < n; i++)
		cin >> a[i];

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v);
		g[v].pb(u);
	}

	init();
	while (q--) {
		int u, v, x;
		cin >> u >> v >> x;
		u--, v--;
		int res = query(u, v, x);
		if (res > 0)
			cout << 1;
		else
			cout << 0;
	}


}
