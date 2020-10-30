vec<int> SufArray;
 
vec<int> cnt;
 
void calc_cnt(vec<int> &cnt) {
    int pref_sum = 0;
    for (int i = 0; i < cnt.size(); i++) {
        int plus = cnt[i];
        cnt[i] = pref_sum;
        pref_sum += plus;
    }
}
 
vec<int> CreateSufArray(string &str) {
    str.push_back(0);
    cnt = vec<int>(max(256, int(str.length())), 0);
    for (auto ch : str) {
        cnt[ch]++;
    }
    calc_cnt(cnt);
 
    vec<int> p = vec<int>(str.length());
    vec<int> c = vec<int>(str.length());
    vec<int> SortedBy2(str.length());
    for0(i, str.length()) {
        p[cnt[str[i]]++] = i;
    }
    int clas = 0;
    c[p[0]] = 0;
    for (int i = 1; i < str.length(); i++) {
        if (str[p[i]] != str[p[i - 1]]) {
            clas++;
        }
        c[p[i]] = clas;
    }
    int curlen = 1;
    while (curlen <= str.length()) {
        for (int i = 0; i < str.length(); i++) {
            SortedBy2[i] = (p[i] + str.length() - curlen) % str.length();
        }
        for0(i, cnt.size()) {
            cnt[i] = 0;
        }
        for (int i = 0; i < SortedBy2.size(); i++) {
            cnt[c[i]]++;
        }
        calc_cnt(cnt);
        for (int i = 0; i < str.length(); i++) {
            p[cnt[c[SortedBy2[i]]]++] = SortedBy2[i];
        }
        int clas = 0;
        vec<int> newc(c.size(), -1);
        newc[p[0]] = 0;
        for (int i = 1; i < str.length(); i++) {
            int pos1 = (p[i - 1] + curlen) % str.length();
            int pos2 = (p[i] + curlen) % str.length();
            if (c[p[i]] != c[p[i - 1]] || c[pos1] != c[pos2])
                clas++;
            newc[p[i]] = clas;
        }
        c = newc;
        curlen *= 2;
    }
    str.pop_back();
    return p;
}
