// find the smallest value
const ld phi = (1 + sqrt(5)) / 2;
    ld l = -border, r = border;
    {
        ld resphi = 2 - phi;
        ld y1 = l + resphi * (r - l), y2 = r - resphi * (r - l);
        ld f1 = f(y1, ps), f2 = f(y2, ps);

        do {
            if (f1 < f2) {
                r = y2;
                y2 = y1;
                f2 = f1;
                y1 = l + resphi * (r - l);
                f1 = f(y1, ps);
            }
            else {
                l = y1;
                y1 = y2;
                f1 = f2;
                y2 = r - resphi * (r - l);
                f2 = f(y2, ps);
            }
        } while (abs(r - l) > EPS);
    }
