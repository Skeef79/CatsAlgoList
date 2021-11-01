struct DSU {
	int n, ans;
	vec<tuple<int, int, int>> hist;
	vec<int> p, sz;
 
	DSU(int n) :n(n) {
		p.resize(n);
		sz.resize(n);
		hist.reserve(n);
 
		for (int i = 0; i < n; i++)
			p[i] = i, sz[i] = 1;
		ans = n;
	}
 
	int find(int v) {
		while (v != p[v])
			v = p[v];
		return v;
	}
 
	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a != b) {
			if (sz[a] < sz[b])
				swap(a, b);
			hist.emplace_back(a, b, ans);
			p[b] = a;
			sz[a] += sz[b];
			ans--;
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
 
struct Query {
	int l, r, i;
};
 
const int K = 300;
 
void solve() {
	int n, m;
	cin >> n >> m;
 
	vec<pii>e(m);
	for (int i = 0; i < m; i++) {
		cin >> e[i].first >> e[i].second;
		e[i].first--, e[i].second--;
	}
	int k;
	cin >> k;
	
	DSU dsu(n);
	vec<Query>q;
	vec<int>ans(k);
 
	for (int i = 0; i < k; i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		if (r - l + 1 <= K) {
			for (int j = l; j <= r; j++)
				dsu.unite(e[j].first, e[j].second);
			ans[i] = dsu.ans;
			dsu.rollback();
		}
		else {
			q.pb({ l,r,i });
		}
	}
 
	sort(all(q), [](Query a, Query b) {
		if (a.l / K != b.l / K)
			return a.l < b.l;
		return a.r < b.r;
	}); 
 
	k = szof(q);
	int lastR = K;
	for (int i = 0; i < k; i++) {
		int l = q[i].l, r = q[i].r;
		if (i && q[i - 1].l / K != q[i].l / K) {
			dsu.rollback();
			lastR = l / K * K + K;
		}
 
		for (; lastR <= r; lastR++) {
			dsu.unite(e[lastR].first, e[lastR].second);
		}
 
		int op = szof(dsu.hist);
		for (int j = l; j / K == l / K; j++) {
			dsu.unite(e[j].first, e[j].second);
		}
 
		ans[q[i].i] = dsu.ans;
		dsu.rollback(op);
	}
 
	for (auto to : ans)
		cout << to << en;
 
}
