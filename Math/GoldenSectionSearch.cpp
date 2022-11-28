// find the smallest value
const ld phi = (1 + sqrt(5)) / 2;
const ld resphi = 2 - phi;

{
    ld l = -INF, r = INF;
    {
        ld m1 = l + resphi * (r - l), m2 = r - resphi * (r - l);
        ld f1 = f(m1), f2 = f(m2);

        do {
            if (f1 < f2) {
                r = m2;
                m2 = m1;
                f2 = f1;
                m1 = l + resphi * (r - l);
                f1 = f(m1);
            }
            else {
                l = m1;
                m1 = m2;
                f1 = f2;
                m2 = r - resphi * (r - l);
                f2 = f(m2);
            }
        } while (abs(r - l) > EPS);
    }
}
