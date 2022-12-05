// find dist betweeen point O and segment AB
ld distToSegment(Point O, Point A, Point B) {
    if ((O - A) * (B - A) >= 0 && (O - B) * (A - B) >= 0) {
        return abs((O - A) ^ (B - A)) / (A - B).getLen();
    }
    else {
        return min((O - A).getLen(), (O - B).getLen());
    }
}
