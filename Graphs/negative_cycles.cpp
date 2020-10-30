//копипаст емакса

struct edge {
	int a, b, cost;
};
 
int n, m;
vector<edge> e;
const int INF = 1000000000;
 
void solve() {
	vector<int> d (n);
	vector<int> p (n, -1);
	int x;
	for (int i=0; i<n; ++i) {
		x = -1;
		for (int j=0; j<m; ++j)
			if (d[e[j].b] > d[e[j].a] + e[j].cost) {
				d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
				p[e[j].b] = e[j].a;
				x = e[j].b;
			}
	}
 
	if (x == -1)
		cout << "No negative cycle found.";
	else {
		int y = x;
		for (int i=0; i<n; ++i)
			y = p[y];
 
		vector<int> path;
		for (int cur=y; ; cur=p[cur]) {
			path.push_back (cur);
			if (cur == y && path.size() > 1)  break;
		}
		reverse (path.begin(), path.end());
 
		cout << "Negative cycle: ";
		for (size_t i=0; i<path.size(); ++i)
			cout << path[i] << ' ';
	}
  
  //можно применить флойда и сделать
  for (int i=0; i<n; ++i)
	  for (int j=0; j<n; ++j)
		  for (int t=0; t<n; ++t)
			  if (d[i][t] < INF && d[t][t] < 0 && d[t][j] < INF)
				  d[i][j] = -INF;
