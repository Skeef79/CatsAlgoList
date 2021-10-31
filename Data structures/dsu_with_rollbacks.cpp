struct DSU {
	int ans;
	int n;
	vec<tuple<int, int, int>>hist;
	vec<int> p, sz;
	DSU(int n) : n(n) {
		p.resize(n);
		sz.resize(n);
		hist.reserve(n);
 
		for (int i = 0; i < n; i++)
			p[i] = i, sz[i] = 1;
		ans = 1;
	}
 
	int find(int v) {
		for (; v != p[v]; v = p[v]);
		return v;
	}
 
	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) {
			if (sz[a] < sz[b])
				swap(a, b);
			hist.pb({ a,b,ans });
			p[b] = a;
			sz[a] += sz[b];
			ans = max(ans, sz[a]);
		}
	}
 
	void rollback(int op = 0) {
		while (szof(hist) > op) {
			auto[a, b, pAns] = hist.back();
			ans = pAns;
			p[b] = b;
			sz[a] -= sz[b];
			hist.pop_back();
		}
	}
};
