by DimaSidorenko

Check on: 
PSU base geometry contest: https://codeforces.com/group/3SmLTwEKly/contest/303093

Правила геометрии:
- Можно в целых, лучше в целых. 
- Нельзя в целых, помним про EPS. Операторы убийцы: >= == <= 

-------------------------------------------------------------------------------------------------------------

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

