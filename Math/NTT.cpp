const ll mod = 998244353;
const ll root = 805775211;

const int LOG = 19;
const int N = (1 << LOG);

ll w[N];
ll ta[N], tb[N];
void precalcW() {
	w[0] = 1;
	for (int i = 1; i < N; i++) {
		w[i] = (w[i - 1] * root) % mod;
	}
}

ll binpow(ll x, ll n) {
	ll p = 1;
	while (n) {
		if (n & 1)
			p = (p*x) % mod;
		n /= 2;
		x = (x*x) % mod;
	}
	return p;
}

void fft(ll* a, int logn, bool inv = 0) {
	int n = (1 << logn);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (j > i)
			swap(a[j], a[i]);
	}

	for (int k = 1; k <= logn; k++) {
		int len = (1 << (k - 1));
		for (int i = 0; i < n; i += (2 * len)) {
			for (int j = 0; j < len; j++) {
				ll add = (a[i + j + len] * w[j*(1 << (LOG - k))]) % mod;
				a[i + j + len] = a[i + j] - add >= 0 ? a[i + j] - add : a[i + j] - add + mod;
				a[i + j] = (a[i + j] + add) <= mod ? a[i + j] + add : a[i + j] + add - mod;
			}
		}
	}

	if (inv) {
		ll rn = binpow(n, mod - 2);
		for (int i = 0; i < n; i++)
			a[i] = (a[i] * rn) % mod;
		reverse(a + 1, a + n);
	}
}

vec<ll> mult(vec<ll> a, vec<ll> b) {
	int logn = 0;
	while ((1 << logn) < 2 * max(szof(a), szof(b)))
		logn++;

	int n = (1 << logn);
	for (int i = 0; i < n; i++) {
		ta[i] = (i < szof(a) ? a[i] : 0);
		tb[i] = (i < szof(b) ? b[i] : 0);
	}

	fft(ta, logn, 0);
	fft(tb, logn, 0);

	for (int i = 0; i < n; i++)
		ta[i] = (ta[i] * tb[i]) % mod;

	fft(ta, logn, 1);

	int sz = szof(a) + szof(b) - 1;
	vec<ll>ans(sz);
	for (int i = 0; i < sz; i++)
		ans[i] = ta[i];
	return ans;
}

//precalcW()
