vector<vector<int>>g;
int maxlevel = 0;
set<int> c;
int n;

void find_center()
{
	vector<int> lvl(n);
	vector<int> degree(n);
	queue<int> q;
	for (int i = 0; i < n; i++)
	{
		degree[i] = g[i].size();
		if (degree[i] == 1)
			q.push(i);
	}
	
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (auto to : g[v])
		{
			degree[to]--;
			if (degree[to] == 1)
			{
				q.push(to);
				lvl[to] = lvl[v] + 1;
				maxlevel = max(maxlevel, lvl[to]);
			}
		}
	}

	for (int i = 0; i < n; i++)
		if (lvl[i] == maxlevel)
			c.insert(i);
	
	//diameter = 2*maxlevel + |c|-1
	//radius = (diameter+1)/2
}
