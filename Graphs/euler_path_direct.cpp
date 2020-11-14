vector<vector<int>> g;
vector<bool>used; 
map<ll, int> idx;
vector<int>d_in, d_out;
 
int sz = 0;
int start1 = -1;
int start2 = -1;

//из графа удаляются ребра по факту

bool check()
{
    int cnt = 0;
    for (int i = 0; i < g.size(); i++)
        if (d_out[i] - d_in[i] == 1)
        {
            cnt++;
            if (start1 == -1)
                start1 = i;
            else
                return false;
        }
        else
            if (d_out[i] - d_in[i] == -1)
            {
                cnt++;
                if (start2 == -1)
                    start2 = i;
                else
                    return false;
            }
            else
                if (abs(d_in[i] - d_out[i]) == 0)
                    continue;
                else
                    return false;
 
    if (cnt == 0 || cnt == 2)
        return true;
    else
        return false;
}
 
int start;
int good_sz = 0;
 
vector<int> euler_path()
{
    vector<int> path;
    vector<int> stk;
    int at = start;
    stk.push_back(at);
 
    while (true)
    {
        if (g[at].empty()) 
        {
            path.push_back(stk.back());
            stk.pop_back();
            if (stk.size()) 
            {
                at = stk.back();
            }
            else
            {
                break;
            }
        }
        else
        {
            int to = g[at].back();
            g[at].pop_back();
            stk.push_back(to);
            at = to;
        }
    }
 
    if ((int)path.size() <= good_sz)
    {
        cout << "No";
        exit(0);
    }
 
    reverse(path.begin(), path.end());
    return path;
}
