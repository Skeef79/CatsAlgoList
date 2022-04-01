// counter clockwise direction
bool ccw(Point p1, Point p2, Point p3) {
    return ((p2 - p1) ^ (p3 - p2)) > 0;
}

vec<Point> Graham(vec<Point> p) {
    int n = p.size();

    //find the leftmost point
    Point s = p[0];
    for (int i = 1; i < n; i++)
        if (p[i].x < s.x || p[i].x == s.x && p[i].y < s.y)
            s = p[i];

    auto cmp = [&](Point p, Point q) {
        p = p - s;
        q = q - s;
        if ((p ^ q) != 0)
            return (p ^ q) > 0;
        return p.getLenSq() < q.getLenSq();
    };

    // sorting on polar angle
    sort(all(p), cmp);

    vector<Point> ans;
    for (int i = 0; i < n; i++) {
        while (ans.size() > 1 && !ccw(ans[ans.size() - 2], ans[ans.size() - 1], p[i]))
            ans.pop_back();
        ans.push_back(p[i]);
    }

    return ans;
}
