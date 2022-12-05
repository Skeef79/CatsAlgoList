vector<point> intersectLineCircle(ld rad1, const Line& l) {
    ld d = l.getDist(point(0, 0));
 
    if (rad1 < d) {
        return {};
    }
 
    point H = point(-(l.a * l.c) / (sq(l.a) + sq(l.b)), -(l.b * l.c) / (sq(l.a) + sq(l.b)));
 
    point colinear = l.getColinearVector();
    colinear = colinear / sqrt(sq(colinear.x) + sq(colinear.y));
 
    auto len = sqrt(sq(rad1) - sq(d));
    if (len < EPS) {
        return { H };
    }
    else {
        return { H + colinear * len, H - colinear * len };
    }
}
 
vector<point> intersectCircleCircle(point middle1, ld rad1, point middle2, ld rad2) {
    if (middle1 == middle2 && abs(rad1 - rad2) < EPS) {
        return {};
    }
 
    ld shift_x = middle1.x;
    ld shift_y = middle1.y;
 
    middle1.x -= shift_x;
    middle2.x -= shift_x;
 
    middle1.y -= shift_y;
    middle2.y -= shift_y;
 
    auto res = intersectLineCircle(rad1, Line(2 * middle2.x, 2 * middle2.y, -sq(middle2.x) - sq(middle2.y) - sq(rad1) + sq(rad2)));
 
    for (auto& [x, y] : res) {
        x += shift_x;
        y += shift_y;
    }
 
    return res;
}
