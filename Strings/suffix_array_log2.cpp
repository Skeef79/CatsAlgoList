struct suffixArray
{
	int n;
	vector<int>suffix, c;
	vector<pii>tmp;
	string s;

	suffixArray(string _s)
	{
		s = _s;
		n = s.length()+1;
		suffix = vector<int>(n);
		c = vector<int>(n);
		tmp = vector<pii>(n);
		build(_s);
	}

	void build(string s)
	{
		s += "$";
		iota(all(suffix), 0);
		sort(all(suffix), [&](int a, int b) { return s[a] < s[b]; });
		for (int i = 1; i < n; i++)
			c[suffix[i]] = c[suffix[i - 1]] + (s[suffix[i]] != s[suffix[i - 1]]);

		for (int k = 1; k < n; k *= 2)
		{
			sort(all(suffix), [&](int a, int b)
			{ 
				return make_pair(c[a], c[(a + k) % n]) < make_pair(c[b], c[(b + k) % n]);
			});

			for (int i = 0; i < n; i++)
				tmp[i] = { c[i],c[(i + k) % n] };

			c[suffix[0]] = 0;
			for (int i = 1; i < n; i++)
				c[suffix[i]] = c[suffix[i - 1]] + (tmp[suffix[i]]!=tmp[suffix[i-1]]);
		}
	}
};
