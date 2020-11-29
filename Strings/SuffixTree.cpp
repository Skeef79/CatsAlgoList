
int posnow = 0;
int need_spusk = 0;
int curv = 0;

struct node {
    map<int, int> to; // ребра из вершины
    // len и pos описывает ребро в эту вершину
    int len;
    int pos;
    int sufflink;
    node() {
        len = 0;
        pos = 0;
        sufflink = 0;
    }
};

node SuffixTree[1000000];
int text[1000000];
int cnt = 1;

void go_edges() {
    int e = text[posnow - need_spusk];
    int nextv = SuffixTree[curv].to[e];
    while (need_spusk > SuffixTree[nextv].len) {
        need_spusk -= SuffixTree[nextv].len;
        curv = nextv;
        e = text[posnow - need_spusk];
        nextv = SuffixTree[curv].to[e];
    }
}

int make_node(int pos, int len) {
    SuffixTree[cnt].pos = pos;
    SuffixTree[cnt].len = len;
    cnt++;
    return cnt - 1;
}

int nowq = 0; 
void add_letter(int c) {
    text[posnow] = c;
    posnow++;
    need_spusk++;
    int last = 0;
    while (need_spusk > 0) {
        go_edges();
        int e = text[posnow - need_spusk]; // по какому ребру спускаемся
        int to = SuffixTree[curv].to[e];
        int t = text[SuffixTree[to].pos + need_spusk - 1]; // какая буква на той позиции в которую спусимся по ребру
        if (to == 0) { // мы уже стоим в вершине и надо отпочковать лист
            SuffixTree[curv].to[e] = make_node(posnow - need_spusk, inf); // отпочковали литст
            SuffixTree[last].sufflink = curv; // поставили ссылку
            last = 0;
        }
        else if (t == c) { // если этот символ уже есть, то ставим ссылку и завершаем итерацию
            SuffixTree[last].sufflink = curv; //
            return;
        }
        else {
            // сначала крафтим разветвление у которого сейчас номер cnt
            int wasto = to; // в середине какого ребра будет развилка
            int razvetvlenie = make_node(SuffixTree[wasto].pos, need_spusk - 1); // крафтим разветвление
            SuffixTree[razvetvlenie].to[c] = make_node(posnow - 1, inf); // из него ответвляем лист
            SuffixTree[razvetvlenie].to[t] = wasto; // и ребро в восту
            SuffixTree[wasto].len -= need_spusk - 1; // теперь ребро в нее уменьшилось
            SuffixTree[wasto].pos += need_spusk - 1; // теперь ребро из разветвления, которое начинается на нид спуск позже
            SuffixTree[curv].to[e] = razvetvlenie; // теперь из курвы мы идем по этому символу в разветвление
            SuffixTree[last].sufflink = razvetvlenie;
            last = razvetvlenie;
        }
        if (curv == 0)
            need_spusk--;
        else
            curv = SuffixTree[curv].sufflink;
    }
}


bool is_substring(string s) { // есть ли такая подстрока
    int nowv = 0;
    int pos = 0;
    int to = SuffixTree[0].to[s[0] - 'a'];
    if (to == 0) {
        return false;
    }
    int gone = 0;
    while (true) {
        if (pos == s.length())
            return true;
        int c = s[pos] - 'a';
        int t = text[SuffixTree[to].pos + gone];
        if (t != c) {
            return false;
        }
        gone++;
        pos++;
        if (pos == s.length()) {
            return true;
        }
        if (gone == SuffixTree[to].len && pos != s.length()) {
            int e = s[pos] - 'a';
            to = SuffixTree[to].to[e];
            gone = 0;
            if (to == 0) {
                return false;
            }
        }
    }
}

void AddWord(string& s) {
    need_spusk = 0;
    curv = 0;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        add_letter(s[i] - 'a');
    }
    add_letter(100 + nowq);
    nowq++;
}

void solve() {
    SuffixTree[0].len = inf;
}
