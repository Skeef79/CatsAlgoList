struct sparceTable
{
	const int K = 20;
	int n;
	vector<vector<int>>t;
	vector<int> log;
	function<int(int, int)> f;

	void build(vector<int>&a)
	{
		for (int i = 0; i < n; i++)
			t[i][0] = a[i];

		for (int j = 1; j < K; j++)
			for (int i = 0; i <= n - (1 << j); i++)
				t[i][j] = f(t[i][j - 1], t[i + (1 << (j - 1))][j - 1]);

		log[1] = 0;
		for (int i = 2; i <= n; i++)
			log[i] = log[i / 2] + 1;
	}

	void init(vector<int>&a, function<int(int, int)> _f)
	{
		f = _f;
		n = a.size();
		t = vector<vector<int>>(n, vector<int>(K));
		log = vector<int>(n + 1);
		build(a);
	}

	sparceTable() {}

	sparceTable(vector<int>&a, function<int(int, int)>_f)
	{
		init(a, _f);
	}

	int get(int l, int r)
	{
		int j = log[r - l + 1];
		return f(t[l][j], t[r - (1 << j) + 1][j]);
	}

};

int _min(int a, int b)
{
	return min(a, b);
}

struct suffixArray
{
	int n;
	vector<int>suffix, c, cnt, pos, lcp;
	string s;
	sparceTable rmq;

	suffixArray(string _s)
	{
		s = _s;
		s += "$";
		n = s.length();
		suffix.resize(n);
		c.resize(n);
		cnt.resize(n);
		pos.resize(n);
		lcp.resize(n);

		buildArray(s);
		buildLCP();
	}

	void buildArray(string s)
	{
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
			for (int i = 0; i < n; i++)
				pos[suffix[i]] = i;
		}
	}

	void buildLCP()
	{
		int k = 0;
		for (int i = 0; i < n - 1; i++)
		{
			while (s[i + k] == s[suffix[pos[i] - 1] + k])
				k++;
			lcp[pos[i]] = k;
			k = max(k - 1, 0);
		}
		rmq.init(lcp, _min);
	}

	int get_lcp(int i, int j)
	{
		i = pos[i], j = pos[j];
		if (i > j)
			swap(i, j);

		return rmq.get(i + 1, j);
	}

};
