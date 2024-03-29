struct vertex {
	map<char, int>next;
	map<char, int>go;
	int link, termLink, p;
	char pch;
	bool term;
	vertex(int p, char pch) :p(p), pch(pch), term(false), link(-1), termLink(-1) {}
};

vector<vertex>t;

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

//ссылка на ближайшую терминальную вершину
int getTermLink(int v) {
	if (t[v].termLink != -1)
		return t[v].termLink;

	int u = getLink(v);
	if (u == 0)
		t[v].termLink = 0;
	else
		t[v].termLink = (t[u].term ? u : getTermLink(u));

	return t[v].termLink;
}

//t.emplace_back(0,0);
