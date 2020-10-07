vector<vector<int>> g;
int start = 0;

bool check() //проверяем по критерию (если все степени четны - эйлеров цикл, если 2 нечетны - путь, иначе -гг)
{
	int cnt = 0;
	for (int i = 1; i < g.size(); i++)
		if (g[i].size() % 2 != 0)
		{
			cnt++;
			start = i;
		}

	if (cnt == 0 || cnt == 2)
		return true;
	else
		return false;
}

vector<int> euler_path()
{
	stack<int> st;
	vector<int> ans;

	st.push(start);
	set<pair<int, int>> used; // удаленные ребра

	while (!st.empty())
	{
		int v = st.top();
		for (auto to : g[v]) //находим первое неудаленное ребро и переходим в него
		{
			if (!used.count({ min(to,v),max(to,v) }))
			{
				st.push(to);
				used.insert({ min(to,v),max(to,v) });
				break;
			}
		}
		if (v == st.top()) // если мы не смогли перейти ни в одно из ребер, то добавляем вершину в ответ
		{
			st.pop();
			ans.pb(v);
		}
	}

	reverse(all(ans));
	return ans;
}
