//массив должен быть посорчен по k, причем нужно учитывать что запрос можем делать в любой точке, но добавляться должен так, чтобы следующее k было оптимально на +inf
//то есть на миниммум это нужно посортить по убыванию k, а на максимум по возрастанию k
// stress-tested on 3 tasks from cf and atcoder

struct Line {
	ll k, b;
	ll get(ll x) {
		return k * x + b;
	}
	ld intersect(Line p) {
		return (ld)(b - p.b) / (p.k - k);
	}
};

struct Hull {
	vec<Line> lines;
	vec<int>idx;

	void add(Line p) {
		while (szof(lines) > 1 && lines[szof(lines) - 1].intersect(p) <= lines[szof(lines) - 2].intersect(lines[szof(lines) - 1])) {
			lines.pop_back();
			idx.pop_back();
		}
		lines.pb(p);
		idx.pb(szof(idx));
	}

	ll get(ll x) {
		auto cmp = [&](int i, ll x) {
			return lines[i].intersect(lines[i + 1]) < x;
		};

		int i = *lower_bound(idx.begin(), idx.begin() + szof(lines) - 1, x, cmp);
		return lines[i].get(x);
	}
};

//Hull hull;
//hull.add({0,0}) - иногда помогает инициализировать
