struct vertex {
	map<char, int>next;
	map<char, int>go;
	int link, p;
	char pch;
	bool term;
	vertex(int p, char pch) :p(p), pch(pch), term(false), link(-1) {}
};

const int N = 1e5 + 1010;
vector<vertex>t;
bool done[N];

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

int go(int v, char c);

int getLink(int v) {
	if (t[v].link == -1)
		t[v].link = (t[v].p == 0 ? 0 : go(getLink(t[v].p), t[v].pch));
	return t[v].link;
}

int go(int v, char c) {
	if (!t[v].go[c])
		if (t[v].next[c])
			t[v].go[c] = t[v].next[c];
		else
			t[v].go[c] = (v == 0 ? 0 : go(getLink(v), c));
	return t[v].go[c];
}

//t.emplace_back(0,0);
