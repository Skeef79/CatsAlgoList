//helper functions
ll cross(ll x1, ll y1, ll x2, ll y2) {
	//don't forget about overflow
	return x1 * y2 - x2 * y1;
}

ll len(ll x, ll y) {
	//and here also can  be overflow
	return x * x + y * y;
}

//check if vectors clockwise
ll cw(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return cross(x2 - x1, y2 - y1, x3 - x2, y3 - y2) < 0;
}

struct HullCompare {
	bool operator() (const  pll &a, const pll &b) const {
		if (cross(a.first, a.second, b.first, b.second) == 0)
			return len(a.first, a.second) < len(b.first, b.second);
		return cross(a.first, a.second, b.first, b.second) < 0;
	}
};

//upper convex hull, increasing on x and decreasing on y, sorted by angle
//it support only adding points
struct DynamicHull {
	set<pll, HullCompare>hull;

	bool inside(ll x, ll y) {
		if (hull.empty())
			return false;
  
    //add fictive points to avoid corner cases
		hull.insert({ 0, hull.begin()->second });
		hull.insert({ hull.rbegin()->first, 0 });
		auto it = hull.lower_bound({ x,y });

		auto right = it;
		auto left = prev(it);

		bool res = !cw(left->first, left->second, x, y, right->first, right->second);
    
    //delete fictive points
		hull.erase(hull.begin());
		hull.erase((--hull.end()));
		return res;
	}

	void add(ll x, ll y) {
		if (inside(x, y))
			return;

		if (hull.empty()) {
			hull.insert({ x,y });
			return;
		}
    
    //add fictive points to avoid corner cases
		hull.insert({ 0, hull.begin()->second });
		hull.insert({ hull.rbegin()->first, 0 });
  
    //delete left part
		auto it = hull.upper_bound({ x,y });
		while (it != hull.begin() && prev(it) != hull.begin()) {
			auto last1 = prev(it);
			auto last2 = prev(prev(it));

			if (cw(last2->first, last2->second, last1->first, last1->second, x, y))
				break;
			hull.erase(last1);
			it = hull.upper_bound({ x,y });
		}
    
    //delete right part
		it = hull.upper_bound({ x,y });
		while (it != hull.end() && next(it) != hull.end()) {
			auto next1 = it;
			auto next2 = next(it);
			if (cw(x, y, next1->first, next1->second, next2->first, next2->second))
				break;
			hull.erase(next1);
			it = hull.upper_bound({ x,y });
		}
  
    //delete fictive points
		hull.erase(hull.begin());
		hull.erase((--hull.end()));
		hull.insert({ x,y });
	}

	void print() {
		for (auto[x, y] : hull) {
			cout << x << ' ' << y << en;
		}
		cout << en;
	}

	DynamicHull() {}
	~DynamicHull() {
		hull.clear();
	}
};

//tested on https://official.contest.yandex.com/ptz-winter-2022/contest/34820/problems/H4/?success=65071442#7/2022_02_04/thdUZbh3Jw
