typedef ll ptype;
struct point {
	ptype x, y;
	point(ptype x = 0, ptype y = 0) : x(x), y(y) {}

	point operator -(point p) {
		return point(x - p.x, y - p.y);
	}

	ptype operator*(point p) {
		return x * p.x + y * p.y;
	}

	ptype operator^(point p) {
		return x * p.y - y * p.x;
	}

	ptype len2() {
		return x * x + y * y;
	}

	friend istream& operator >>(istream &in, point &p) {
		in >> p.x >> p.y;
		return in;
	}

	friend ostream& operator <<(ostream &out, point &p) {
		out << p.x << ' ' << p.y;
		return out;
	}
};

bool ccw(point p1, point p2, point p3) {
	return ((p2 - p1) ^ (p3 - p2)) > 0;
}

vec<point> graham(vec<point> p) {
	int n = p.size();
	point s = p[0];
	for (int i = 1; i < n; i++)
		if (p[i].x < s.x || p[i].x == s.x && p[i].y < s.y)
			s = p[i];

	auto cmp = [&](point p, point q) {
		p = p - s;
		q = q - s;
		if ((p^q) != 0)
			return (p ^ q) > 0;
		return p.len2() < q.len2();
	};

	sort(all(p), cmp);
	vec<point> ans;
	for (int i = 0; i < n; i++) {
		while (ans.size() > 1 && !ccw(ans[ans.size() - 2], ans[ans.size() - 1], p[i]))
			ans.pop_back();
		ans.pb(p[i]);
	}

	return ans;
}
