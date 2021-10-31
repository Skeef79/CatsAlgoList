#define _USE_MATH_DEFINES
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<climits>
#include<set>
#include<map>
#include<cmath>
#include<iomanip>
#include<iterator>
#include<queue>
#include<stack>
#include<cctype>
#include<deque>
#include<time.h>
#include<bitset>
#include<random>
#include<functional>
#include<unordered_set>
#include<unordered_map>
#include<random>
#include<numeric>
#include<sstream>
#include<cassert>
#include<chrono>
#include<complex>

//by Skeef79

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:16777216")
#define pb push_back
#define en '\n'
#define forn(i,n) for(int i = 0;i<n;i++)
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define vec vector
#define pii pair<int,int>
#define pll pair<ll,ll>
#define szof(x) int(x.size())

using namespace std;

const int INF = 1000000000 + 1e8;
const ll LINF = 2000000000000000000;

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

struct Query {
	int l, r, i;
};

const int N = 1e5 + 1010;
int a[N];
int cnt[N];

const int K = 400;
vec<int> hist;

void rollback(int op = 0) {
	while (szof(hist) > op) {
		cnt[hist.back()] = 0;
		hist.pop_back();
	}
}

void solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int m;
	cin >> m;
	vec<Query> q;

	hist.reserve(N);
	vec<int>ans(m);
	DSU dsu(N);

	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--, r--;

		if (r - l + 1 <= K) {
			for (int j = l; j <= r; j++) {
				if (cnt[a[j]] > 0)
					continue;

				hist.pb(a[j]);
				cnt[a[j]] = 1;

				if (cnt[a[j] - 1] > 0)
					dsu.unite(a[j] - 1, a[j]);
				if (cnt[a[j] + 1] > 0)
					dsu.unite(a[j] + 1, a[j]);
			}
			ans[i] = dsu.ans;
			dsu.rollback();
			rollback();
		}
		else {
			q.pb({ l,r,i });
		}
	}

	m = szof(q);
	sort(all(q), [](const Query a, const Query b) {
		if (a.l / K != b.l / K)
			return a.l < b.l;
		return a.r < b.r;
	});


	int lastR = K;
	for (int i = 0; i < m; i++) {
		int l = q[i].l, r = q[i].r;
		if (r - l + 1 <= K)
			continue;

		if (i && q[i - 1].l / K != q[i].l / K) {
			rollback();
			dsu.rollback();
			lastR = l / K * K + K;
		}
		for (; lastR <= r; lastR++) {
			int j = lastR;
			if (cnt[a[j]] > 0)
				continue;

			hist.pb(a[j]);
			cnt[a[j]] = 1;

			if (cnt[a[j] - 1] > 0)
				dsu.unite(a[j] - 1, a[j]);
			if (cnt[a[j] + 1] > 0)
				dsu.unite(a[j] + 1, a[j]);
		}

		int opNum = szof(dsu.hist);
		int opNum2 = szof(hist);
		for (int j = l; j / K == l / K; j++) {
			if (cnt[a[j]] > 0)
				continue;

			hist.pb(a[j]);
			cnt[a[j]] = 1;

			if (cnt[a[j] - 1] > 0)
				dsu.unite(a[j] - 1, a[j]);
			if (cnt[a[j] + 1] > 0)
				dsu.unite(a[j] + 1, a[j]);
		}
		ans[q[i].i] = dsu.ans;
		dsu.rollback(opNum);
		rollback(opNum2);
	}

	for (auto to : ans)
		cout << to << en;

}

int main() {
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
#endif

	int tst = 1;
	//cin >> tst;

	while (tst--) {
		solve();
	}

}
