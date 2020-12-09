struct suffixArray
{
	int n;
	vector<int>suffix, c, cnt;
	string s;

	suffixArray(string _s)
	{
		s = _s;
		n = s.length() + 1;
		suffix.resize(n);
		c.resize(n);
		cnt.resize(n);
		build(_s);
	}

	void build(string s)
	{
		s += "$";
		iota(all(suffix), 0);
		sort(all(suffix), [&](int a, int b) { return s[a] < s[b]; });
		for (int i = 1; i < n; i++)
			c[suffix[i]] = (s[suffix[i]] == s[suffix[i - 1]] ? c[suffix[i - 1]] : i);

		for (int k = 1; k < n; k *= 2)
		{
			iota(all(cnt), 0);
			vector<int>new_c(c), new_suffix(suffix);
			for (int i = 0; i < n; i++)
			{
				int j = (new_suffix[i] - k + n) % n;
				suffix[cnt[new_c[j]]++] = j;
			}
			c[suffix[0]] = 0;
			for (int i = 1; i < n; i++)
			{
				bool same = new_c[suffix[i]] == new_c[suffix[i - 1]]
					&& new_c[(suffix[i] + k) % n] == new_c[(suffix[i - 1] + k) % n];
				c[suffix[i]] = same ? c[suffix[i - 1]] : i;
			}
		}
	}
};
