vec<vec<int>>g;
int n;
vec<int>tin, fup;
vec<bool>used;
int timer = 1;
int maxColor = 0;
map<int, vec<pii>>mp;

//сначала насчитываем tin и fup обычным дфсом, после этого вызываем функцию paint

pii tie(int u, int v) {
	return { min(u,v),max(u,v) };
}

void paint(int v, int color, int p = -1) {
	used[v] = true;
	int cnt = 0;
	for (auto to : g[v]) {
		if (to == p)
			continue;

		if (used[to]) {
			if (tin[to] < tin[v])
				mp[color].pb(tie(v, to));
		}
		else {
			cnt++;
			int ncolor = color;
			if (p != -1 && fup[to] >= tin[v] || p == -1 && cnt > 1) {
				ncolor = ++maxColor;
				mp[ncolor].pb(tie(v, to));
			}
			else
				mp[ncolor].pb(tie(v, to));

			paint(to, ncolor, v);
		}
	}
}

/*
for (int i = 0; i < n; i++)
		if (!used[i])
			dfs(i);

	fill(all(used), false);
	for (int i = 0; i < n; i++)
		if (!used[i])
			paint(i, ++maxColor);

*/

//теперь все компоненты лежат в мапе для каждого цвета своя компонента из ребер. 
