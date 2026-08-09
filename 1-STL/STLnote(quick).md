# C++ STL — Quick Syntax Reference

## Setup
```cpp
#include <bits/stdc++.h>
using namespace std;
```

## Pair
```cpp
pair<int,int> p = {1, 3};
p.first; p.second;                        // access
pair<int,pair<int,int>> p2 = {1,{3,4}};   // nested for 3+ values
```

## Vector (dynamic array)
```cpp
vector<int> v;
v.push_back(1); v.emplace_back(2);        // insert at back
vector<int> v(5,100);                     // 5 elements = 100
vector<int> v2(v1);                       // copy
v[0]; v.at(0); v.back();                  // access
vector<int>::iterator it = v.begin();     // or auto it
*it; it++;                                 // deref / move
v.end();                                   // one-past-last
for(auto x : v) cout<<x;                  // range-based print
v.erase(v.begin()+1);                     // delete index 1
v.erase(v.begin(), v.begin()+3);          // delete range [start,end)
v.insert(v.begin(), 300);                 // insert single at front
v.insert(v.begin()+1, 2, 5);              // insert 2 copies of 5
v.insert(v.begin(), v2.begin(), v2.end()); // insert another vector
v.size(); v.pop_back(); v.swap(v2);
v.clear(); v.empty();
```

## List (doubly linked list)
```cpp
list<int> l;
l.push_back(4); l.push_front(5); l.emplace_front(6);
// begin,end,size,clear,empty same as vector
```

## Deque
```cpp
deque<int> dq;
dq.push_back(1); dq.push_front(2);
dq.pop_back(); dq.pop_front();
dq.back(); dq.front();
```

## Stack (LIFO)
```cpp
stack<int> st;
st.push(1); st.emplace(5);
st.top(); st.pop();
st.size(); st.empty(); st.swap(st2);
```

## Queue (FIFO)
```cpp
queue<int> q;
q.push(1);
q.back(); q.front(); q.pop();
q.size(); q.empty();
```

## Priority Queue (max-heap default)
```cpp
priority_queue<int> pq;
pq.push(5); pq.top(); pq.pop();
priority_queue<int, vector<int>, greater<int>> minpq;  // min-heap
```

## Set (sorted, unique)
```cpp
set<int> s;
s.insert(1); s.emplace(2);
s.find(3);                 // iterator, or s.end() if absent
s.erase(5);                // by value
s.erase(it);                // by iterator
s.erase(s.find(2), s.find(4)); // range erase
s.count(1);                 // 0 or 1
s.lower_bound(x); s.upper_bound(x);
```

## Multiset (sorted, duplicates allowed)
```cpp
multiset<int> ms;
ms.insert(1);
ms.erase(1);                // erases ALL occurrences
ms.erase(ms.find(1));       // erases ONE occurrence
ms.count(1);
```

## Unordered Set (unique, unsorted)
```cpp
unordered_set<int> us;
us.insert(1); us.find(1); us.erase(1); us.count(1);
// no lower_bound/upper_bound
```

## Map (key-value, unique+sorted keys)
```cpp
map<int,int> mp;
mp[1] = 2;
mp.emplace(3,1); mp.insert({2,4});
for(auto it : mp) it.first, it.second;
mp[key];                    // 0/default if absent (also inserts it!)
mp.find(3);                 // iterator; it->second
mp.count(key);
mp.lower_bound(x); mp.upper_bound(x);
mp.erase(key); mp.size(); mp.empty(); mp.swap(mp2);
```

## Multimap (duplicate keys, sorted)
```cpp
multimap<int,int> mm;
mm.insert({1,2}); mm.insert({1,3});
```

## Unordered Map (unique keys, unsorted)
```cpp
unordered_map<int,int> um;
um[1] = 2;
```

## Algorithms
```cpp
sort(a, a+n);                        // ascending, range [a, a+n)
sort(a, a+n, greater<int>());        // descending
sort(v.begin(), v.end());            // for vector

bool cmp(pair<int,int> p1, pair<int,int> p2){   // custom comparator
    if(p1.second != p2.second) return p1.second < p2.second;
    return p1.first > p2.first;
}
sort(arr, arr+n, cmp);

__builtin_popcount(x);               // count set bits (int)
__builtin_popcountll(x);             // for long long

string s = "123";
sort(s.begin(), s.end());            // start from smallest perm
do { cout<<s; } while(next_permutation(s.begin(), s.end()));

*max_element(a, a+n);
*min_element(a, a+n);

lower_bound(v.begin(), v.end(), x);  // first elem >= x (sorted range)
upper_bound(v.begin(), v.end(), x);  // first elem > x
```

## Complexity Cheat-Sheet
| Container | Insert/Erase | Search |
|---|---|---|
| vector/list/deque | O(1) back, O(n) elsewhere | O(n) |
| stack/queue | O(1) | — |
| priority_queue | O(log n) | O(1) top |
| set/map/multiset/multimap | O(log n) | O(log n) |
| unordered_set/map | O(1) avg, O(n) worst | O(1) avg |
````