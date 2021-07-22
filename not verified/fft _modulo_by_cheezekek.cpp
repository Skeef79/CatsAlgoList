
const ll mod = 998244353;
const int root = 805775211;
const int root_1 = 46809892;
const int root_pw = 1 << 19;

void fft(vector<int>& a, bool invert) {
	int n = (int)a.size();
 
	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}
 
	for (int len = 2; len <= n; len <<= 1) {
		int wlen = invert ? root_1 : root;
		for (int i = len; i < root_pw; i <<= 1)
			wlen = int(wlen * 1ll * wlen % mod);
		for (int i = 0; i < n; i += len) {
			int w = 1;
			for (int j = 0; j < len / 2; ++j) {
				int u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
				w = int(w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		int nrev = reverse(n, mod);
		for (int i = 0; i < n; ++i)
			a[i] = int(a[i] * 1ll * nrev % mod);
	}
}
 
vector<int> mult(vector<int> a, vector<int> b) {
	int n = 1;
	while (n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	a.resize(n); b.resize(n);
 
	fft(a, 0); fft(b, 0);
	for (int i = 0; i < n; ++i)
		a[i] = (1ll * a[i] * b[i]) % mod;
	fft(a, 1);
	vector<int> res;
	for (int i = 0; i < n; ++i)
		res.emplace_back(a[i]);
	return res;
}
