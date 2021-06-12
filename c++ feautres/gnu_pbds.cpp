#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<long long, long long>, null_type, less<pair<long long, long long>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

//здесь вместо pair<long long, long long> можно писать любой тип (обязательно поменять его в less)

ordered_set st;

st.find_by_order(index) //возвращает указатель на элемент с индексом index, если больше то возвращает st.end()
st.order_of_key(value) //индекс первого больше либо равного элеамента 
