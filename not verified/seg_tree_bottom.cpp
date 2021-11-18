struct node {
	int len;
	int open_b, closed_b;
	node() :len(0), closed_b(0), open_b(0) {}
	node(char c) {
		len = 0;
		open_b = c == '(';
		closed_b = c == ')';
	}
};
 
node combine(const node a, const node b) {
	node res;
	int t = min(a.open_b, b.closed_b);
	res.len = a.len + b.len + t;
	res.open_b = a.open_b + b.open_b - t;
	res.closed_b = a.closed_b + b.closed_b - t;
	return res;
}
 
const int N = 1e6 + 10;
node t[2 * N];
 
void build(string s) {
	for (int i = 0; i < szof(s); i++)
		t[N + i] = node(s[i]);
	for (int i = N - 1; i > 1; i--)
		t[i] = combine(t[2 * i], t[2 * i + 1]);
}
 
//[l,r)
node query(int l, int r) {
	node ansl, ansr;
	l += N, r += N;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1)
			ansl = combine(ansl, t[l++]);
		if (r & 1)
			ansr = combine(t[--r], ansr);
	}
	return combine(ansl, ansr);
}

void modify(int pos, int value) {
	pos += N;
	t[pos] = value;
	for (; pos > 1; pos >>= 1) {
		t[pos >> 1] = combine(t[pos], t[pos ^ 1]);
	}
}
