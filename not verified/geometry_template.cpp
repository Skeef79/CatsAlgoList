by DimaSidorenko

Check on: 
PSU base geometry contest: https://codeforces.com/group/3SmLTwEKly/contest/303093

Правила геометрии:
- Можно в целых, лучше в целых. 
- Нельзя в целых, помним про EPS. Операторы убийцы: >= == <= 

-------------------------------------------------------------------------------------------------------------

bool get_sign(ld value) {
    if (value > EPS) { return 1; }
    if (value < -EPS) { return -1; }
    
    return 0;
}

bool get_sign(ll value) {
    if (value > 0) { return 1; }
    if (value < 0) { return -1; }

    return 0;
}

// принадлежность точки вектору
bool isPointOnRay(Point pt, Point st, Point nd) {
    auto vec1 = pt - st;
    auto ray = nd - st;

    // принадлежат одной прямой и соноправлены
    if (abs(vec1 ^ ray) < EPS && (vec1 * ray) + EPS > 0) {
        return 1;
    }

    return 0;
}

// принадлежность точки отрезку
ld isPointOnSegment(Point pt, Point seg_start,Point seg_end) {
    auto vec1 = seg_start - pt; 
    auto vec2 = seg_end - pt;

    auto segment = seg_end - seg_start;

    // Смотрим что перпендикуляр лежит между точек. 
    // Один угол <= 90, другой >= 90
    auto angle1 = vec1 * segment;
    auto angle2 = vec2 * segment;

   
    if (angle1 * angle2 <= 0) { // расстояние до перпендикуляра
        auto ln = Line(seg_start, seg_end);
        auto val1 = ln.getDist(pt);
        return val1;
    }
    else { // расстояние до крайних точек отрезка
        auto val2 = vec1.getLen();
        auto val3 = vec2.getLen();
        return min(val2, val3);
    }
}


