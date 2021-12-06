const ld EPS = 1e-8;

typedef ld TCoord;

class Point {
public:
    TCoord x, y;
    Point(TCoord xx = 0, TCoord yy = 0): x(xx), y(yy) {}
    Point operator-(const Point &a) const { return Point(x - a.x, y - a.y); }
    Point operator+(const Point &a) const { return Point(x + a.x, y + a.y); }
    Point operator*(ld a) const { return Point(x * a, y * a); }
    ld getLen() const { return sqrtl(x * x + y * y); }
    Point setLen(ld new_len) const { return (*this) * (new_len / getLen()); }
    TCoord getLenSq() const { return x * x + y * y; }
    
    Point turn90() const { return Point(-y, x); }
    Point turn(double sn, double cs) const {  return Point(x * cs - y * sn, x * sn + y * cs); }
    Point turn(double ang) const { return turn(sin(ang), cos(ang)); }
    Point inverse() const { return Point(-x, -y); }
    
    TCoord operator%(const Point &p) const { return x * p.y - y * p.x; }
    TCoord operator*(const Point &p) const { return x * p.x + y * p.y; }
   
    
    bool operator!=(const Point &p) const { return fabsl(x - p.x) > EPS || fabsl(y - p.y) > EPS; }
    bool operator==(const Point &p) const { return fabsl(x - p.x) < EPS && fabsl(y - p.y) < EPS; }
    
    friend bool cmpAngle(const Point &a, const Point &b) {
        TCoord m = a % b;
        return (fabsl(m) > EPS ? m > 0 : a.getLenSq() < b.getLenSq());
    }
    friend bool cmpCoord(const Point &a, const Point &b) {
        return a.x + EPS < b.x || (fabsl(a.x - b.x) < EPS && a.y + EPS < b.y);
    }
    friend ostream& operator<<(ostream &fo, Point p) {
        fo << "(" << p.x << "," << p.y << ")";
        return fo;
    }
    friend istream& operator>>(istream &fi, Point &p) {
        fi >> p.x >> p.y;
        return fi;
    }
};
 

class Line {
public:
    ld a, b, c;
    Line(ld aa = 0, ld bb = 0, ld cc = 0): a(aa), b(bb), c(cc) {}
    Line(const Point &p1, const Point &p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
    }
    Point getNormVector() const { return Point(a, b); }
    Point getColinearVector() const { return Point(-b, a); }
    ld getOrientDist(const Point &p) const { return (a * p.x + b * p.y + c) / sqrtl(a * a + b * b); }
    ld getDist(const Point &p) const { return fabsl(getOrientDist(p)); }
    Point operator&(const Line &l) const {
        ld denom = a * l.b - b * l.a;
        return Point((b * l.c - c * l.b) / denom, (c * l.a - a * l.c) / denom);
    }
};
