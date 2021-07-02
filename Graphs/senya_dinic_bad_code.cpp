
struct edge{
    int ost_pass;
    int to;
    edge *obr;
    
    edge(int p, int t){
        ost_pass = p;
        to = t;
    }
};

int n, m, s, t;
vec<vec<edge*>> g;
vec<int> d;
vec<vec<edge*>> OstSet;
bool flag = false;
ll ans = 0;

void bfs(){
    queue<int> q;
    for0(i, n)
        d[i] = -100;
    d[0] = 0;
    q.push(0);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto e : g[v]){
            if(e->ost_pass == 0 || d[e->to] != -100)
                continue;
            d[e->to] = d[v] + 1;
            q.push(e->to);
        }
    }
}

void CreateOstSet(){
    for0(v, n){
        OstSet[v].clear();
        for(auto &e : g[v]){
            if(e->ost_pass == 0)
                continue;
            if(d[e->to] == d[v] + 1){
                OstSet[v].push_back(e);
            }
        }
    }
}

int dfs(int v, int mini = inf, int p = -1){
    int mi;
    if(v == t){
        flag = true;
        return mini;
    }
    if(OstSet[v].size() == 0){
        return - 1;
    }
    for(int i = OstSet[v].size()-1; i >= 0; i--){
        if(OstSet[v][i]->ost_pass == 0 || OstSet[v][i]->to == p){
            OstSet[v].pop_back();
            continue;
        }
        int to = OstSet[v][i]->to;
        //cout << OstSet[v][i]->ost_pass<< en;
        auto it =OstSet[v][i];
        mi = dfs(to, min(mini, OstSet[v][i]->ost_pass), v);
        if(!flag){
            OstSet[v].pop_back();
            continue;
        }
        OstSet[v][i]->ost_pass -= mi;
        OstSet[v][i]->obr->ost_pass += mi;
        if(OstSet[v][i]->ost_pass == 0)
            OstSet[v].pop_back();
        break;
    }
    if(flag)
        return mi;
    return -1;
}

bool MakePhase(){
    bfs();
    if(d[t] == -100){
        return false;
    }
    CreateOstSet();
    while(true){
        int plus = dfs(s);
        flag =false;
        if(plus == -1)
            break;
        ans += plus;
    }
    return true;
}

ll GetMaxFlow(){
    while(MakePhase()){
        int kek;
    }
    return ans;
}

void solve(){
    cin >> n >> m;
    s = 0, t = n - 1;
    g = vec<vec<edge*>>(n);
    d = vec<int>(n, -100);
    OstSet = vec<vec<edge*>>(n);
    for0(i, m){
        int a, b, w;
        cin >> a >> b >> w;
        a--;b--;
        g[a].push_back(new edge(w, b));
        g[b].push_back(new edge(0, a));
        g[a].back()->obr = g[b][g[b].size()-1];
        g[b].back()->obr = g[a][g[a].size()-1];
        /* g[a].push_back(new edge(0, b));
        g[b].push_back(new edge(w, a));
        g[a].back()->obr = g[b][g[b].size()-1];
        g[b].back()->obr = g[a][g[a].size()-1];*/
    }
    cout <<GetMaxFlow();
}
