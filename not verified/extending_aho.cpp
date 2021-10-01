struct Aho {
	struct vertex {
		map<char, int>next;
		int link, p, cnt;
		char pch;
		bool term;
		vertex(int p, char pch) :p(p), pch(pch), link(-1), term(false), cnt(-1) {}
	};
 
	Aho() {
		t.emplace_back(0, 0);
	};
 
	void clear() {
		t.clear();
		t.emplace_back(0, 0);
	}
 
	vec<vertex>t;
	void addString(string &s) {
		int v = 0;
		for (auto c : s) {
			if (!t[v].next[c]) {
				t[v].next[c] = szof(t);
				t.emplace_back(v, c);
			}
			v = t[v].next[c];
		}
		t[v].term = true;
	}
 
	int getCnt(int v) {
		if (t[v].cnt == -1)
			t[v].cnt = (v == 0 ? 0 : getCnt(getLink(v)) + t[v].term);
		return t[v].cnt;
	}
 
	void build(vec<string>a) {
		for (auto s : a)
			addString(s);
	}
 
	int go(int v, char c) {
		if (!t[v].next[c])
			return (v == 0 ? 0 : go(getLink(v), c));
		return t[v].next[c];
	}
 
	int getLink(int v) {
		if (t[v].link == -1)
			t[v].link = (t[v].p == 0 ? 0 : go(getLink(t[v].p), t[v].pch));
		return t[v].link;
	}
 
};
 
struct extendingAho {
	const int K = 19;
	vec<Aho>ver;
	vec<vec<string>>data;
	extendingAho() {
		ver.resize(K);
		data.resize(K);
	}
 
	void add(string s) {
		data[0].pb(s);
		for (int i = 0; i < K; i++) {
			if (szof(data[i]) == (1 << (i + 1))) {
				for (auto to : data[i])
					data[i + 1].pb(to);
				data[i].clear();
				ver[i].clear();
			}
			else {
				ver[i].clear();
				ver[i].build(data[i]);
				break;
			}
		}
	}
 
	int get(string s) {
		int ans = 0;
		for (int i = 0; i < K; i++) {
			if (data[i].empty())
				continue;
			int v = 0;
			for (auto c : s) {
				v = ver[i].go(v, c);
				ans += ver[i].getCnt(v);
			}
		}
		return ans;
	}
 
};

/*
extendingAho t1, t2;
	int n;
	cin >> n;

	while (n--) {
		int type;
		string s;
		cin >> type >> s;
		if (type == 1) {
			t1.add(s);
		}
		if (type == 2) {
			t2.add(s);
		}
		if (type == 3) {
			cout << t1.get(s) - t2.get(s) << endl;
		}
	}
*/
