int n;
vec<vec<int>>g;
vec<bool>mark;
vec<int>par;
vec<int>sz;

int find_size(int v, int p = -1) {
	sz[v] = 1;
	for (auto to : g[v])
		if (!mark[to] && to != p)
			sz[v] += find_size(to, v);
	return sz[v];
}

int find_centroid(int v, int p = -1, int n = 1) {
	for (auto to : g[v])
		if (to != p && !mark[to] && sz[to] > n / 2)
			return find_centroid(to, v, n);
	return v;
}

void build(int v, int p = -1) {
	find_size(v);

	int c = find_centroid(v, -1, sz[v]);
	mark[c] = true;
	par[c] = p;

	for (auto to : g[c])
		if (!mark[to])
			build(to, c);
}

void init() {
	g.resize(n);
	mark.resize(n);
	par.resize(n, -1);
	sz.resize(n);
}

//init()
//build()
