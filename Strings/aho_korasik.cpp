struct trie{
    int next[26]; // переход по ребру в символ
    int go[26]; // хитрый переход при движении по тексту + для получения суфссылок
    int p; // предок
    int SufLink; // суфссылка
    int TermLink;// В какую терминальную вершину придем по суфссылкам
    char pch; // символ по которому пришли в вершину
    bool terminal; // терминальная ли вершина
    int num; // номер строки
    
    trie(char ch, int par){
        p = par;
        pch = ch;
        SufLink = -1;
        TermLink = - 1;
        terminal = false;
        for0(i, 26)
            go[i] = -1, next[i] = -1;
    }
};

vec<trie> t;

void AddString(string &str, int &num){
    int v = 0;
    for0(i, str.length()){
        int pos = str[i] - 'a';
        if(t[v].next[pos] == -1){
            t[v].next[pos] = t.size();
            t.push_back(trie(str[i], v));
        }
        v = t[v].next[pos];
    }
    t[v].terminal = true;
    t[v].num = num;
}

int go(int v, char ch); // куда перейдем в поиске по тексту по символу ch

int GetSufLink(int v){
    if(t[v].SufLink == -1){
        if(v == 0 || t[v].p == 0) // ссылка в корень
            t[v].SufLink = 0;
        else
            t[v].SufLink = go(GetSufLink(t[v].p), t[v].pch); // идем по суфссылке отца и пытаемся сделать переход по символу текущей вершини
    }
    return t[v].SufLink;
}

int go(int v, char ch){
    int pos = ch - 'a';
    if(t[v].go[pos] == -1){
        if(t[v].next[pos] != -1) // если есть ребро из текущей вершины
            t[v].go[pos] = t[v].next[pos];
        else if(v == 0) // корень
            t[v].go[pos] = 0;
        else // Если нет ребра, то опять идем по суфссылке и пытаемся сходить по ch
            t[v].go[pos] = go(GetSufLink(v), ch);
    }
    return t[v].go[pos];
}

// ЭТОГО НЕТ НА ЕМАКСЕ 
// Терминальная ссылка - ссылка в терминальную вершину, которая является самой близкой при переходе по суфссылкам
int GetTermLink(int v){
    if(t[v].TermLink != -1) // если уже нашли
        return t[v].TermLink;
    if(v == 0) // из корня ссылка в себя
        t[v].TermLink = 0;
    else if(t[GetSufLink(v)].terminal) // если перейдем по суфссылке в терминал, то этот терминал нам и нужен
        t[v].TermLink = GetSufLink(v);
    else
        t[v].TermLink = GetTermLink(GetSufLink(v)); // иначе переходим по суфссылке и ищем термссылку из нее, она будет подходить и нашей вершине
    return t[v].TermLink;
}
