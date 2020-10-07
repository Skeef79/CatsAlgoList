pair<ll, vector<int>> hungarianAlgorithm(vector<vector<ll>> a)
{
	int n = a.size() - 1;
	int m = a[0].size() - 1;

	vector<int> pl(n + 1, 0), pr(n + 1, 0), mt(n + 1, 0), way(n + 1, 0);
	for (int row = 1; row <= n; row++) 
	{
		mt[0] = row;
		vector<int> minv(n + 1, INF);
		vector<bool> used(n + 1, false);
		int col = 0;
		do 
		{
			used[col] = true;
			int v = mt[col], delta = INF, nextcol;
			for (int i = 1; i <= n; i++) 
			{
				if (used[i])
					continue;
				int x = a[v][i] - pl[v] - pr[i];
				if (x < minv[i])
					minv[i] = x, way[i] = col;
				if (minv[i] < delta)
					delta = minv[i], nextcol = i;
			}
			for (int i = 0; i <= n; i++) 
			{
				if (used[i])
					pl[mt[i]] += delta, pr[i] -= delta;
				else
					minv[i] -= delta;
			}
			col = nextcol;
		} while (mt[col] != 0);

		do 
		{
			int nextcol = way[col];
			mt[col] = mt[nextcol];
			col = nextcol;
		} while (col);
	}

	vector<int> res(n+1);
	for (int i = 1; i <= m; i++)
		res[mt[i]] = i;

	return { -pr[0],res };

}
