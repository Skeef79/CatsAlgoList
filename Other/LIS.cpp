vector<ll> findLIS(vector<ll> a) {
	int n = a.size();
	vector<ll> d(n + 1,LINF), pos(n+1,-1), prev(n);
	int length = 0;
	d[0] = -LINF;
	
	for (int i = 0; i < n; i++) {
		int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();

		if (d[j - 1] < a[i] && a[i] < d[j]) {
			d[j] = a[i];
			pos[j] = i;
			prev[i] = pos[j - 1];
			length = max(length, j);
		}
	}

	vector<ll> ans;
	int p = pos[length];
	for (int p = pos[length]; p != -1; p = prev[p])
		ans.pb(a[p]);

	reverse(all(ans));
	return ans;
}
