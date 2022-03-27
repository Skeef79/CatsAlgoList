/*
Проверенно на:
https://codeforces.com/contest/228/problem/E
https://codeforces.com/contest/27/problem/D
https://codeforces.com/contest/1475/problem/F
https://codeforces.com/contest/776/problem/D
https://codeforces.com/contest/468/problem/B
*/

struct twoSat {
	int n; //кол-во переменных

	vec<vec<int>>g, gr; //x - четное, !x - нечетеное
	vec<int>c;
	vec<bool>used;
	vec<int>order;
	vec<bool>ans; //ответ на задачу, для каждой переменной 1 или 0
	//все добавленные условия должны выполнятся

	twoSat(int n) :n(n) {
		g.resize(2 * n);
		gr.resize(2 * n);
		c.resize(2 * n);
		used.resize(2 * n);
		ans.resize(n);
	}

	//важное свойство: если есть ребро x->y, то должно быть ребро !y -> !x
	void add_edge(int i, bool ni, int j, bool nj) { //i,j - переменные, ni, nj - нужно ли брать отрицание
		g[2 * i + ni].pb(2 * j + nj);
		gr[2 * j + nj].pb(2 * i + ni);
	}

	void add_or(int x, bool nx, int y, bool ny) { //(x or y)
		add_edge(x, !nx, y, ny);
		add_edge(y, !ny, x, nx);
	}

	void add_xor(int x, bool nx, int y, bool ny) { //(x xor y)
		add_or(x, nx, y, ny);
		add_or(x, !nx, y, !ny);
	}

	void add_and(int x, bool nx, int y, bool ny) { //(x and y)
		add_xor(x, nx, y, !ny);
	}

	void add_eq(int x, bool nx, int y, bool ny) { //(x == y)
		add_or(x, !nx, y, ny);
		add_or(x, nx, y, !ny);
	}

	void dfs(int v) {
		used[v] = true;
		for (auto to : g[v]) {
			if (!used[to])
				dfs(to);
		}
		order.pb(v);
	}

	void dfs2(int v, int cl) {
		used[v] = true;
		c[v] = cl;
		for (auto to : gr[v]) {
			if (!used[to])
				dfs2(to, cl);
		}
	}

	bool satisfiable() {
		fill(all(used), false);
		fill(all(ans), false);

		order.clear();
		for (int i = 0; i < 2 * n; i++)
			if (!used[i])
				dfs(i);

		fill(all(used), false);
		fill(all(c), 0);
		reverse(all(order));
		int cl = 0;
		for (auto v : order) {
			if (!used[v]) {
				dfs2(v, cl);
				cl++;
			}
		}

		for (int i = 0; i < n; i++) {
			int x = 2 * i;
			int nx = 2 * i + 1;
			if (c[x] == c[nx])
				return false;
			ans[i] = (c[x] < c[nx] ? false : true);
		}
		return true;
	}
};
