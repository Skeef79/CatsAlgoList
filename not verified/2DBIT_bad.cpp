struct BIT2D {
    int n;
    vec<ordered_set<int>>t;
 
    //limit for first dimension
    void init(int _n) {
        n = _n;
        t.resize(n);
    }
 
    void print() {
        for(int i = 0;i<n;i++) {
            for(auto to:t[i]) {
                cout<<to<<' ';
            }
            cout<<en;
        }
        cout<<en;
    }
 
    void add(int x,int y) {
        for(int i = x;i<n;i = (i|(i+1)))
            t[i].insert(y);
    }
 
    void erase(int x, int y) {
        for(int i =x;i<n;i = (i|(i+1)))
            t[i].erase(y);
    }
 
    int pref(int x, int y) {
        int res = 0;
        for(int i = x;i>=0;i = (i&(i+1))-1)
            res+=t[i].order_of_key(y+1);
 
        return res;
    }
 
    int get(int i1, int j1, int i2, int j2) {
        return pref(i2,j2) - pref(i2,j1-1) - pref(i1-1,j2) + pref(i1-1,j1-1);
    }
};
