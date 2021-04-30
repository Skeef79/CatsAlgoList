
//#include<algorithm>
// merge a and b into c 
merge(all(a), all(b), back_inserter(c));


//#include<algorithm>
//cycle shift, elemnts a[m...n-1] become first
rotate(a.begin(), a.begin() + m, a.end()); // 1,2,3,4,5 -> 3,4,5,1,2
rotate(a.rbegin(), a.rbegin() + m, a.rend()); // 1,2,3,4,5 -> 4,5,1,2,3

//TODO - add operator overloading for set and hash overloading for unordered_set 
