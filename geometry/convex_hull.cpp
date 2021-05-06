struct point {
	ll x, y;
	point(ll _x = 0, ll _y = 0) {
		x = _x;
		y = _y;
	}
	
	point operator - (point p) {
		return point(x - p.x, y - p.y);
	}

	//dot product(скалярное произведение)
	ll operator * (point p) {
		return x * p.x + y * p.y;
	}
	
	//cross product(векторное произведение)
	ll operator ^ (point p) {
		return x * p.y - y * p.x;
	}
	
	//значение вектора
	ll len2() {
		return 1ll * x * x + 1ll * y * y;
	}

	bool operator != (point p) {
		return x != p.x || y != p.y;
	}

	bool operator == (point p) {
		return x == p.x && y == p.y;
	}
};


istream& operator >> (istream &in, point &p) {
	in >> p.x >> p.y;
	return in;
}

ostream& operator << (ostream &out, point& p) {
	out << p.x << " " << p.y;
	return out;
}


//s - самая левая точка из всех и самая нижняя из всех самых левых.
point s;

bool operator < (point a, point b) {
	a = a - s;
	b = b - s;
	if ((a ^ b) != 0) {
		return (a ^ b) > 0;
	}
	return a.len2() < b.len2();
}

// возвращает выпуклую оболочку
vector<point> Graham(vector<point> p) {
	int n = p.size();

	//находим самую левую(нижнюю точку)
	s = p[0];
	for (int i = 1; i < n; i++) {
		if (p[i].x < s.x) {
			s = p[i];
		}
		if (p[i].x == s.x && p[i].y < s.y) {
			s = p[i];
		}
	}

	sort(p.begin(), p.end());

	//находим внутреннюю оболочку
	vector<point> ans;

	ans.push_back(p[0]);

	for (int i = 1; i < n; i++) {
		while (ans.size() > 1) {
			int j = ans.size() - 1;
			point a = ans[j] - ans[j - 1]; // последний вектор, взятый в оболочку
			point b = p[i] - ans[j]; // текущий вектор
			if ((a ^ b) <= 0) {
				ans.pop_back();
			}
			else {
				break;
			}
		}
		ans.push_back(p[i]);
	}
	return ans;
}
