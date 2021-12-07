vector<ll> xor_transform(vector<ll>a, bool inv = false) { //a.size() shoult be power of 2
	for (int len = 1, n = a.size(); len < a.size(); len <<= 1)
		for (int i = 0; i < n; i += (2 * len))
			for (int j = 0; j < len; j++) { //we need to evaluate x^0*A + x^1*B at (1,-1)
				ll add = a[i + j + len];
				a[i + j + len] = a[i + j] - add;
				a[i + j] = a[i + j] + add;
			}

	if (inv)
		for (int i = 0, n = a.size(); i < n; i++)
			a[i] /= n;

	return a;
}
