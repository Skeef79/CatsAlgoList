//тут решается задача на минимум (надо менять знаки чтобы на максимум и если надо максимум то k должны быть в порядке возрастания
//очень важно чтобы прямые добавлялись в отсорченном порядке по k, иначе не работает

struct Line {
	ll k, b;
	ll get(ll x) {
		return k * x + b;
	}
	ld intersect(Line p) {
		//y1 = k1*x + b1
		//y2 = k2*x + b2
		//k1*x +b1 = k2*x + b2
		//x*(k1-k2) = b2 - b1
		//x = (b2-b1)/(k1-k2)
		return (ld)(b - p.b) / (p.k - k);
	}
};

//k-s should be sorted in decreasing order
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
