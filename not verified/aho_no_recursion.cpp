const int N = 1e5 + 1010;

struct vertex {
	int next[26];
	int go[26];
	int link, cnt;
	vertex() :link(-1), cnt(0) {
		for (int i = 0; i < 26; i++) {
			next[i] = 0;
			go[i] = 0;
		}
	}
};

vector<vertex>t;

void addString(string &s) {
	int v = 0;
	for (auto c : s) {
		if (!t[v].next[c - 'a']) {
			t[v].next[c - 'a'] = szof(t);
			t.pb(vertex());
		}
		v = t[v].next[c - 'a'];
	}
	t[v].cnt++;

}

void pushLinks() {
	queue<int>q;
	q.push(0);
	t[0].link = -1;

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < 26; i++) {
			if (t[v].next[i]) {

				int to = t[v].next[i];

				int u = t[v].link;
				while (u != -1 && !t[u].next[i]) {
					u = t[u].link;
				}

				if (u == -1)
					t[to].link = 0;
				else {
					t[to].link = t[u].next[i];
					t[to].cnt += t[t[to].link].cnt;
				}
				q.push(to);
			}

			if (t[v].next[i])
				t[v].go[i] = t[v].next[i];
			else
				if (v != 0)
					t[v].go[i] = t[t[v].link].go[i];
				else
					t[v].go[i] = 0;
		}
	}
}

/*
t.push_back(vertex());
addString
push_links()
*/
