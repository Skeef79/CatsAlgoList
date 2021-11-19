const int N = 1e5 + 1010;
struct point {
	int x, y, value;
};

vec<int>coords_x;
vec<int> coords_y[N];
vec<ll> t[N];
vec<point>a;

int sz;

void add(int x, int y) {
	x++;
	for (int i = x; i <= sz; i += i & -i)
		coords_y[i].pb(y);
}

ll pref(int xr, int yr) {
	int x = upper_bound(all(coords_x), xr) - coords_x.begin();
	ll res = 0;

	for (int i = x; i > 0; i -= i & -i) {
		int y = upper_bound(all(coords_y[i]), yr) - coords_y[i].begin();
		for (int j = y; j > 0; j -= j & -j)
			res += t[i][j];
	}
	return res;
}

void inc(int x, int y1, int old_value, int new_value) {
	for (int i = x; i <= sz; i += i & -i) {
		int y = lower_bound(all(coords_y[i]), y1) - coords_y[i].begin() + 1;
		for (int j = y; j < szof(t[i]); j += j & -j) {
			t[i][j] -= old_value;
			t[i][j] += new_value;
		}
	}
}


void solve() {
	int n;
	cin >> n;
	a.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y >> a[i].value;
		coords_x.pb(a[i].x);
	}

	sort(all(coords_x));
	coords_x.resize(unique(all(coords_x)) - coords_x.begin());

	sz = szof(coords_x);

	for (int i = 0; i < n; i++) {
		a[i].x = lower_bound(all(coords_x), a[i].x) - coords_x.begin();
		add(a[i].x, a[i].y);
	}

	for (int i = 1; i <= sz; i++) {
		sort(all(coords_y[i]));
		coords_y[i].resize(unique(all(coords_y[i])) - coords_y[i].begin());
		t[i].resize(szof(coords_y[i]) + 1);
	}

	for (int i = 0; i < n; i++) {
		inc(a[i].x + 1, a[i].y, 0, a[i].value);
	}
	int m;
	cin >> m;

	string type;
	int x, y;
	while (m--) {
		cin >> type >> x >> y;
		if (type == "get")
			cout << pref(x, y) << en;
		else {
			x--;
			inc(a[x].x + 1, a[x].y, a[x].value, y);
			a[x].value = y;
		}
	}
}
