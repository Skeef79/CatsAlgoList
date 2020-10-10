const int N = 3e5;
ll t[4 * N];
ll a[N];
ll tadd[4 * N];
ll b[N];

int n;

void build(int v, int vl, int vr)
{
	if (vl == vr)
	{
		t[v] = b[vl];
		return;
	}
	int vm = (vl + vr) / 2;
	build(2 * v + 1, vl, vm);
	build(2 * v + 2, vm + 1, vr);
	t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}

void push(int v, int vl, int vr)
{
	if (tadd[v] != 0)
	{
		t[v] += tadd[v];
		if (vl != vr)
		{
			tadd[2 * v + 1] += tadd[v];
			tadd[2 * v + 2] += tadd[v];
		}
		tadd[v] = 0;
	}
}

ll query(int v, int vl, int vr, int l, int r)
{
	push(v, vl, vr);
	if (r < vl || vr < l)
		return LINF;

	if (vl >= l && vr <= r)
		return t[v];
	int vm = (vl + vr) / 2;
	ll ql = query(2 * v + 1, vl, vm, l, r);
	ll qr = query(2 * v + 2, vm + 1, vr, l, r);
	return min(ql, qr);
}

void inc(int v, int vl, int vr, int l, int r, ll val)
{
	push(v, vl, vr);

	if (r < vl || vr < l)
		return;
	if (vl >= l && vr <= r)
	{
		tadd[v] = val;
		push(v, vl, vr);
		return;
	}
	int vm = (vl + vr) / 2;
	inc(2 * v + 1, vl, vm, l, r, val);
	inc(2 * v + 2, vm + 1, vr, l, r, val);
	t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}

ll segment_tree_query(int l, int r)
{
	return query(0, 0, n - 1, l, r);
}

vector<vector<int>> g;
vector<int> p, depth, heavy, head, pos;
int cur_pos;

int dfs(int v) {
	int size = 1;
	int max_c_size = 0;
	for (auto to : g[v]) {
		if (to != p[v]) {
			p[to] = v, p[to] = p[v] + 1;
			int c_size = dfs(to);
			size += c_size;
			if (c_size > max_c_size)
				max_c_size = c_size, heavy[v] = to;
		}
	}
	return size;
}

void decompose(int v, int h) {
	head[v] = h, pos[v] = cur_pos++;
	b[pos[v]] = a[v];
	if (heavy[v] != -1)
		decompose(heavy[v], h);

	for (int c : g[v]) {
		if (c != p[v] && c != heavy[v])
			decompose(c, c);
	}
}

void init() {
	int n = g.size();
	p = vector<int>(n);
	depth = vector<int>(n);
	heavy = vector<int>(n, -1);
	head = vector<int>(n);
	pos = vector<int>(n);
	cur_pos = 0;

	dfs(0);
	decompose(0, 0);
}

ll tree_query(int a, int b) {
	ll res = LINF;
	for (; head[a] != head[b]; b = p[head[b]]) {
		if (depth[head[a]] > depth[head[b]])
			swap(a, b);
		ll cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
		res = min(res, cur_heavy_path_max);
	}
	if (depth[a] > depth[b])
		swap(a, b);
	ll last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
	res = min(res, last_heavy_path_max);
	return res;
}

void tree_inc(int a, int b, ll val)
{
	for (; head[a] != head[b]; b = p[head[b]]) {
		if (depth[head[a]] > depth[head[b]])
			swap(a, b);
		inc(0, 0, n - 1, pos[head[b]], pos[b], val);
	}
	if (depth[a] > depth[b])
		swap(a, b);
	inc(0, 0, n - 1, pos[a], pos[b], val);
}
