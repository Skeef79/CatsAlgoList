
const int N = 3e5;
ll t[4 * N]; 
ll a[N]; //значения вершин
ll tadd[4 * N]; 
ll b[N]; // значения вершин после хлд в нужном порядке

int n;

ll neutral = -LINF; 
ll f(ll a, ll b) 
{
	return max(a, b);
}

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
	t[v] = f(t[2 * v + 1], t[2 * v + 2]);
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
		return neutral;

	if (vl >= l && vr <= r)
		return t[v];

	int vm = (vl + vr) / 2;
	ll ql = query(2 * v + 1, vl, vm, l, r);
	ll qr = query(2 * v + 2, vm + 1, vr, l, r);
	return f(ql, qr);
}

void modify(int v, int vl, int vr, int l, int r, ll val)
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
	modify(2 * v + 1, vl, vm, l, r, val);
	modify(2 * v + 2, vm + 1, vr, l, r, val);
	t[v] = f(t[2 * v + 1], t[2 * v + 2]);
}

ll segment_tree_query(int l, int r)
{
	return query(0, 0, n - 1, l, r);
}

void segment_tree_modify(int l, int r, ll val)
{
	modify(0, 0, n - 1, l, r, val);
}

vector<vector<int>> g;
vector<bool>used;
vector<int> parent, depth, heavy, head, pos;
int cur_pos;

int dfs(int v, vector<vector<int>> const& g) 
{
	int size = 1;
	int max_c_size = 0;
	for (int c : g[v]) 
	{
		if (c != parent[v]) 
		{
			parent[c] = v, depth[c] = depth[v] + 1;
			int c_size = dfs(c, g);
			size += c_size;
			if (c_size > max_c_size)
				max_c_size = c_size, heavy[v] = c;
		}
	}
	return size;
}

void decompose(int v, int h, vector<vector<int>> const& g) {
	head[v] = h, pos[v] = cur_pos++;
	b[pos[v]] = a[v];
	if (heavy[v] != -1)
		decompose(heavy[v], h, g);
	for (int c : g[v]) 
	{
		if (c != parent[v] && c != heavy[v])
			decompose(c, c, g);
	}
}

void init(vector<vector<int>> const& g) 
{
	int n = g.size();
	parent = vector<int>(n);
	depth = vector<int>(n);
	heavy = vector<int>(n, -1);
	head = vector<int>(n);
	pos = vector<int>(n);
	cur_pos = 0;

	dfs(0, g);
	decompose(0, 0, g);
}

ll tree_query(int a, int b) 
{
	ll res = neutral; //объявляем res равный нейтальному элементу

	for (; head[a] != head[b]; b = parent[head[b]]) 
	{
		if (depth[head[a]] > depth[head[b]])
			swap(a, b);
		ll cur = segment_tree_query(pos[head[b]], pos[b]);
		res = f(res, cur);
	}
	if (depth[a] > depth[b])
		swap(a, b);
	ll last = segment_tree_query(pos[a], pos[b]);
	res = f(res, last);
	return res;
}

void tree_modify(int a, int b, ll val)
{
	for (; head[a] != head[b]; b = parent[head[b]]) {
		if (depth[head[a]] > depth[head[b]])
			swap(a, b);
		segment_tree_modify(pos[head[b]], pos[b], val);
	}
	if (depth[a] > depth[b])
		swap(a, b);
	segment_tree_modify(pos[a], pos[b], val);
}

//сначала пишем init()
//потом пишем build()
