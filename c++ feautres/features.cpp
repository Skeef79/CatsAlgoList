
//#include<algorithm>
// merge a and b into c 
merge(all(a), all(b), back_inserter(c));


//#include<algorithm>
//cycle shift, elements a[m...n-1] become first
rotate(a.begin(), a.begin() + m, a.end()); // 1,2,3,4,5 -> 3,4,5,1,2
rotate(a.rbegin(), a.rbegin() + m, a.rend()); // 1,2,3,4,5 -> 4,5,1,2,3

//coordinate compression
vector<ll>coords;
//add all possible values
sort(all(coords));
coords.resize(unique(all(coords)) - coords.begin());


//TODO - add operator overloading for set and hash overloading for unordered_set 

