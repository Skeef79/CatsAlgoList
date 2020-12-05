struct sparceTable2D
{
	int n, m;
	vector<vector<vector<vector<int>>>>t;

	vector<int>log;
	function<int(int, int)>f;
	int K1, K2;

	void calc_log()
	{
		log[1] = 0;
		for (int i = 2; i <= max(n, m); i++)
			log[i] = log[i / 2] + 1;
		K1 = log[n]+1;
		K2 = log[m]+1;
	}

	void build(vector<vector<int>>&a)
	{
		for(int i = 0;i<K1;i++)
			for (int j = 0; j < K2; j++)
			{
				int ux = n - (1 << i);
				int uy = m - (1 << j);
				for(int x=0;x<=ux;x++)
					for (int y = 0; y <= uy; y++)
					{
						if (i == 0 && j == 0)
							t[i][j][x][y] = a[x][y];
						else
							if (i == 0)
								t[i][j][x][y] = f(t[i][j - 1][x][y], t[i][j - 1][x][y + (1 << (j - 1))]);
							else
								t[i][j][x][y] = f(t[i - 1][j][x][y], t[i - 1][j][x + (1 << (i - 1))][y]);
					}
			}

	}

	sparceTable2D(vector<vector<int>>&a, function<int(int, int)> _f)
	{
		f = _f;
		n = a.size();
		m = a[0].size();
		log = vector<int>(max(n, m) + 1);
		calc_log();
		t = vector<vector<vector<vector<int>>>>(K1, vector<vector<vector<int>>>(K2, vector<vector<int>>(n, vector<int>(m))));
		build(a);
	}

	int get(int x1, int y1, int x2, int y2)
	{
		int kx = log[x2-x1+1];
		int ky = log[y2-y1+1];
		x2 -= (1 << kx) - 1;
		y2 -= (1 << ky) - 1;
		return f(f(t[kx][ky][x1][y1], t[kx][ky][x1][y2]), f(t[kx][ky][x2][y1], t[kx][ky][x2][y2]));
	}
};

inline int _max(int a, int b)
{
	return max(a, b);
}

//sparceTable2D st(a,_max);
