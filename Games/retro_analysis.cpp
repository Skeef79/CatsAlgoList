vector<vector<int>> e;
vector<bool> used;
vector<int> degree;
vector<char> state; // w- win, l = lose, d = draw

void dfs(int v)
{
	used[v] = true;
	for (auto to : e[v])
	{
		if (!used[to])
		{
			if (state[v] == 'l') // если мы стоим в проигрышной вершины, то след вершина - выиграшная
				state[to] = 'w';
			else
				if ( ++degree[to] == e[to].size()) // если из v ребра ведут только в выигршные вершины, то она проигрышная
					state[to] = 'l';
				else
					continue; 
			dfs(to);
		}
	}
}
