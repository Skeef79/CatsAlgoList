struct cd {
	double a, b;
	cd(double a = 0, double b = 0) : a(a), b(b) {}
	const cd operator + (const cd &c) const {
		return cd(a + c.a, b + c.b);
	}
	const cd operator - (const cd &c) const {
		return cd(a - c.a, b - c.b);
	}
	const cd operator * (const cd &c) const {
		return cd(a * c.a - b * c.b, a * c.b + b * c.a);
	}
};

const int LOG = 19;
const int N = (1 << LOG);

cd w[N];
cd ta[N], tb[N];
void precalcW() {
	for (int i = 0; i < N; i++) {
		double angle = 2 * M_PI*i / N;
		w[i] = cd(cos(angle), sin(angle));
	}
}

void fft(cd* a, int logn, bool inv = 0) {
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
				cd add = a[i + j + len] * w[j*(1 << (LOG - k))];
				a[i + j + len] = a[i + j] - add;
				a[i + j] = a[i + j] + add;
			}
		}
	}

	if (inv) {
		for (int i = 0; i < n; i++)
			a[i].a /= n;
		reverse(a + 1, a + n);
	}
}

vec<ll> mult(vec<ll> a, vec<ll> b) {
	int logn = 0;
	while ((1 << logn) < 2 * max(szof(a), szof(b)))
		logn++;

	int n = (1 << logn);
	for (int i = 0; i < n; i++) {
		ta[i] = (i < szof(a) ? cd(a[i], 0) : cd(0, 0));
		tb[i] = (i < szof(b) ? cd(b[i], 0) : cd(0, 0));
	}

	fft(ta, logn, 0);
	fft(tb, logn, 0);

	for (int i = 0; i < n; i++)
		ta[i] = ta[i] * tb[i];

	fft(ta, logn, 1);

	vec<ll>ans(n);
	for (int i = 0; i < n; i++)
		ans[i] = round(ta[i].a);
	return ans;
}

//precalcW()
