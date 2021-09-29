#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<pair<long long, long long>, null_type, less<pair<long long, long long>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

//здесь вместо pair<long long, long long> можно писать любой тип (обязательно поменять его в less)

//еще один варианты это через шаблоны:
template <typename num_t>
using ordered_set = tree<num_t, null_type, less_equal<num_t>, rb_tree_tag, tree_order_statistics_node_update>;
//less_equal для мультисета, less для сета
//тогда можем создавать так: ordered_set<int> st;

ordered_set st;

st.find_by_order(index) //возвращает указатель на элемент с индексом index, если больше то возвращает st.end()
st.order_of_key(value) //индекс первого больше либо равного элеамента 
