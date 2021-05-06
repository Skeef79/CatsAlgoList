vector<int> g[N], ans;

void dfs(int v) {
	while(!g[v].empty()) {
		auto to = g[v].back();
		g[v].pop_back();
		dfs(to);
	}
	ans.pb(v);
}
 
 
void solve(){
	//...
 
	vector<int> in(N), out(N);
 
	for (int i = 0; i < n; i++) {
		//ввод графа
 
		g[u].pb(v);
		in[v]++;
		out[u]--;
	}
 
	int st = -1, end = -1;
	bool is = true;
	for (int i = 0; i < N; i++) {
		if (in[i] == -out[i]) {
			continue;
		}
		
		if (in[i] + 1 == -out[i]) {
			if (st != -1) {
				cout << "NO" << en;
				return;
			}
			st = i;
		}
		if (in[i] - 1 == -out[i]) {
			if (end != -1) {
				cout << "NO" << en;
				return;
			}
			end = i;
		}
	}
 
	if (st == -1) {
		for (int i = 0; i < N; i++) {
			if (in[i] > 0) {
				st = i;
				break;
			}
		}
	}
 
	dfs(st);

	//проверка: размер ответа == кол-ву ребер 
