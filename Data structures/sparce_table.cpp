const int K = 20;

struct sparceTable
{
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

	sparceTable(vector<int>&a, function<int(int,int)>_f)
	{
		f = _f;
		n = a.size();
		t = vector<vector<int>>(n, vector<int>(K));
		log = vector<int>(n + 1);
		build(a);
	}

	int get(int l, int r)
	{
		int j = log[r - l + 1];
		return f(t[l][j], t[r - (1 << j) + 1][j]);
	}

};
