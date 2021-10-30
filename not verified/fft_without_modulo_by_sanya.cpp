struct Compl {
    ld x, y;
    Compl() {}
    Compl(ld x, ld y): x(x), y(y) {}
    Compl operator * (const Compl& a) const {
        return {x * a.x - y * a.y, x * a.y + y * a.x};
    }
    Compl operator + (const Compl& a) const {
        return {x + a.x, y + a.y};
    }
    Compl operator - (const Compl& a) const {
        return {x - a.x, y - a.y};
    }
    Compl operator / (const ld k) const {
        return {x / k, y / k};
    }
} w[N];
 
int rev[N];
Compl ara[N], arb[N];
 
void initFFT() {
    rev[0] = 0;
    int maxbit = 0;
    int n = (1 << LOG);
    for (int i = 1; i < n; i++) {
        if (i == (1 << (maxbit + 1)))
            maxbit++;
        rev[i] = rev[i ^ (1 << maxbit)] + (1 << (LOG - maxbit - 1));
    }
 
    for (int i = 0; i < n; i++) {
        ld ang = 2 * PI * i / n;
        w[i] = {cos(ang), sin(ang)};
    }
}
 
void fft(Compl* a, int logn, bool isback = false) {
    assert(logn <= LOG);
    int n = (1 << logn);
 
    for (int i = 1; i < n - 1; i++) {
        int j = (rev[i] >> (LOG - logn));
        if (j > i) {
            swap(a[i], a[j]);
        }
    }
 
    for (int loglen = 0; loglen < logn; loglen++) {
        int len = (1 << loglen);
        for (int l = 0; l < n; l += (2 * len)) {
            for (int i = 0; i < len; i++) {
                Compl tmp = w[i * (1 << (LOG - loglen - 1))] * a[l + i + len];
                a[l + len + i] = a[l + i] - tmp;
                a[l + i] = a[l + i] + tmp;
            }
        }
    }
 
    if (isback) {
        reverse(a + 1, a + n);
        for (int i = 0; i < n; i++)
            a[i] = a[i] / n;
    }
}
 
vector<ll> mult(vector<ll>& a, vector<ll>& b) {
    int n = a.size();
    int m = b.size();
    int logn = 0;
    while ((1 << logn) < 2 * max(n, m))
        logn++;
    fill(ara, ara + (1 << logn), Compl(0, 0));
    fill(arb, arb + (1 << logn), Compl(0, 0));
    for (int i = 0; i < n; i++)
        ara[i] = Compl(a[i], 0);
    for (int i = 0; i < m; i++)
        arb[i] = Compl(b[i], 0);
 
    fft(ara, logn);
    fft(arb, logn);
 
    for (int i = 0; i < (1 << logn); i++)
        ara[i] = ara[i] * arb[i];
 
    fft(ara, logn, true);
 
    vector<ll> ans(1 << logn);
    for (int i = 0; i < (1 << logn); i++)
        ans[i] = round(ara[i].x);
    return ans;
}
