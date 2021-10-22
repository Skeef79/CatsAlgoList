vec<int> pf(string s) {
	int n = szof(s);
	vec<int>pi(n);

	for (int i = 1; i < n; i++) {
		int j = pi[j - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])
			j++;
		pi[i] = j;
	}

	return pi;
}
