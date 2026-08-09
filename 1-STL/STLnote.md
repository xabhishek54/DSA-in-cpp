# C++ STL — Complete Notes

## What is STL?
STL (**Standard Template Library**) is a collection of pre-built **algorithms, containers, iterators, and functions** in C++. It removes the need to write lengthy code for common data structures (like dynamic arrays, stacks, queues) or algorithms (like sorting) from scratch.

STL is divided into **four parts**:
1. **Algorithms**
2. **Containers**
3. **Functions**
4. **Iterators**

---

## Basic Code Skeleton

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // code here
    return 0;
}
```

- `#include <bits/stdc++.h>` includes **all standard libraries** at once (math.h, string.h, vector, etc.), so you don't need to include each one individually.
- `using namespace std` lets you write `cin`, `cout` directly instead of `std::cin`, `std::cout`.

Without `using namespace std`:
```cpp
std::cin >> a;
std::cout << a;
```

With `using namespace std`:
```cpp
cin >> a;
cout << a;
```

### Function Types

**Void function** — returns nothing:
```cpp
void print() {
    cout << "raj";
}

int main() {
    print();
}
```
Output:
````
raj
````

**Return-type function** — returns a value:
```cpp
int sum(int a, int b) {
    return a + b;
}

int main() {
    int s = sum(1, 5);
    cout << s;
}
```
Output:
````
6
````
(Return type can be any data type — `int`, `double`, `string`, etc.)

---

## Pair (from `<utility>`)

A `pair` stores **two values** together, possibly of different data types.

```cpp
pair<int, int> p = {1, 3};
cout << p.first;   // 1
cout << p.second;  // 3
```
Output:
````
1
3
````

### Nested Pairs (storing 3+ values)
```cpp
pair<int, pair<int, int>> p = {1, {3, 4}};
cout << p.first;          // 1
cout << p.second.first;   // 3
cout << p.second.second;  // 4
```
Output:
````
1
3
4
````

### Array of Pairs
```cpp
pair<int, int> arr[] = {{1,2}, {3,4}, {5,6}};
cout << arr[1].second;  // 4
```
Output:
````
4
````

---

## Vector

A **dynamic array** — its size can grow or shrink at runtime, unlike a normal array whose size is fixed.

### Declaration & Insertion
```cpp
vector<int> v;
v.push_back(1);     // adds 1 at the back
v.emplace_back(2);  // adds 2 at the back (generally faster than push_back)
```
Result: `v = {1, 2}`

For a vector of pairs:
```cpp
vector<pair<int,int>> v;
v.push_back({1, 2});   // needs curly braces
v.emplace_back(1, 2);  // no curly braces needed
```

### Declaring with a Predefined Size
```cpp
vector<int> v(5, 100);  // 5 elements, all = 100
vector<int> v(5);       // 5 elements, all = 0 (or garbage, compiler-dependent)
```

### Copying a Vector
```cpp
vector<int> v1(5, 20);
vector<int> v2(v1);   // v2 is a copy of v1
```

You can still push into a size-declared vector — it dynamically resizes:
```cpp
vector<int> v(5, 100);
v.push_back(1);  // now size 6
```

### Accessing Elements
```cpp
vector<int> v = {20, 10, 15, 5, 7};
cout << v[0];       // 20
cout << v[3];       // 5
cout << v.at(0);    // 20 (rarely used)
```

### Iterators
An iterator points to the **memory address** of an element (not the element itself).

```cpp
vector<int>::iterator it = v.begin();
cout << *it;       // dereference: prints element at v.begin() -> 20
it++;
cout << *it;       // prints 10
cout << *(it + 2); // shifts 2 more positions -> prints 5
```

- `v.begin()` → points to the first element.
- `v.end()` → points to the memory location **right after** the last element (not the last element itself).
- `v.rbegin()` / `v.rend()` → reverse iterators (rarely used in practice). `rbegin()` points to the last element; `rend()` points right before the first element. Incrementing a reverse iterator moves backward through the vector.

```cpp
cout << v.back();  // last element, e.g. for v = {10,20,30} -> 30
```

### Printing a Vector

Method 1 — index loop:
```cpp
for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
```

Method 2 — iterator loop:
```cpp
for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    cout << *it << " ";
```

Method 3 — `auto` (auto-detects data type):
```cpp
for (auto it = v.begin(); it != v.end(); it++)
    cout << *it << " ";
```

Method 4 — range-based for-each loop:
```cpp
for (auto it : v) cout << it << " ";
```

For `v = {10, 20, 30}`, all methods above give:
Output:
````
10 20 30
````

### Deletion — `erase()`

Single element:
```cpp
vector<int> v = {10, 20, 12, 23};
v.erase(v.begin() + 1);  // deletes element at index 1 (20)
```
Result: `v = {10, 12, 23}`

Range of elements (start included, end excluded):
```cpp
vector<int> v = {10, 20, 12, 23, 35};
v.erase(v.begin() + 2, v.begin() + 4);  // deletes index 2 and 3
```
Result: `v = {10, 20, 35}`

### Insertion — `insert()`

Single element:
```cpp
vector<int> v(2, 100);    // {100, 100}
v.insert(v.begin(), 300); // insert at start
```
Result: `v = {300, 100, 100}`

Multiple copies of one value:
```cpp
vector<int> v = {10, 20, 30, 40};
v.insert(v.begin() + 1, 2, 5);  // insert two 5's at index 1
```
Result: `v = {10, 5, 5, 20, 30, 40}`

Insert another vector (whole or partial):
```cpp
vector<int> v1 = {30, 10, 10, 100, 100};
vector<int> copy = {50, 50};
v1.insert(v1.begin(), copy.begin(), copy.end());
```
Result: `v1 = {50, 50, 30, 10, 10, 100, 100}`

### Other Common Functions
| Function | Meaning |
|---|---|
| `v.size()` | number of elements |
| `v.pop_back()` | removes the last element |
| `v.swap(v2)` | swaps contents of two vectors |
| `v.clear()` | empties the vector completely |
| `v.empty()` | returns `true` if vector has 0 elements, else `false` |

---

## List

Similar to vector, but implemented as a **doubly linked list**, so it supports efficient **front operations**.

```cpp
list<int> l;
l.push_back(4);
l.push_front(5);
l.emplace_front(6);
```

- `push_front()` — inserts at front (cheap for `list`, O(1); costly for `vector`, since it requires shifting all elements).
- `emplace_front()` — same as push_front, generally faster.
- All other functions (`begin`, `end`, `rbegin`, `rend`, `size`, `clear`, `empty`) work the same as vector.

---

## Deque (Double-Ended Queue)

Similar to vector/list — supports insertion/deletion from **both ends**.

```cpp
deque<int> dq;
dq.push_back(1);
dq.push_front(2);
dq.pop_back();
dq.pop_front();
dq.back();
dq.front();
```
All other functions are same as vector/list.

---

## Stack — LIFO (Last In, First Out)

The last element pushed is the first one popped.

```cpp
stack<int> st;
st.push(1);
st.push(2);
st.push(3);
st.emplace(5);   // same as push

cout << st.top();   // 5 (last inserted, still present)
st.pop();            // removes 5
cout << st.top();   // 3
cout << st.size();  // 3
cout << st.empty(); // false (0)
```
Output:
````
5
3
3
0
````

- Only `push`, `pop`, `top` are the core functions.
- No random/index access is allowed (`st[0]` is invalid).
- `st1.swap(st2)` swaps two stacks.
- All operations run in **O(1)** time.

---

## Queue — FIFO (First In, First Out)

The first element inserted is the first one removed (like a ticket line).

```cpp
queue<int> q;
q.push(1);
q.push(2);
q.push(4);

q.back() += 5;   // modifies last element: 4 -> 9

cout << q.back();   // 9
cout << q.front();  // 1
q.pop();              // removes front (1)
cout << q.front();  // 2
```
Output:
````
9
1
2
````
All operations run in **O(1)** time.

---

## Priority Queue (Max-Heap by default)

Keeps the **largest** element at the top. Internally implemented as a tree (heap), not a linear structure.

```cpp
priority_queue<int> pq;
pq.push(5);
pq.push(2);
pq.push(8);
pq.push(10);

cout << pq.top();  // 10
pq.pop();            // removes 10
cout << pq.top();  // 8
```
Output:
````
10
8
````

Min-Heap version (smallest element at top):
```cpp
priority_queue<int, vector<int>, greater<int>> pq;
pq.push(5);
pq.push(2);
pq.push(8);
pq.push(10);

cout << pq.top();  // 2
```
Output:
````
2
````

### Time Complexity
| Operation | Complexity |
|---|---|
| `push` | O(log n) |
| `top` | O(1) |
| `pop` | O(log n) |

---

## Set

Stores elements in **sorted order** and only **unique** values (duplicates are ignored). Internally implemented as a balanced tree.

```cpp
set<int> s;
s.insert(1);
s.emplace(2);
s.insert(2);   // ignored, duplicate
s.insert(4);
s.insert(3);
```
Result (internally sorted): `{1, 2, 3, 4}`

### Key Functions

```cpp
auto it = s.find(3);   // returns iterator pointing to element 3
auto it2 = s.find(6);  // 6 not present -> returns s.end()

s.erase(5);             // erases the element with value 5 (by value)
s.erase(it);             // erases using an iterator

cout << s.count(1);    // 1 if present, 0 if not (since unique)
```

### Range Erase
```cpp
set<int> s = {1, 2, 3, 4, 5};
s.erase(s.find(2), s.find(4));  // deletes 2 and 3 (4 excluded)
```
Result: `s = {1, 4, 5}`

- `begin`, `end`, `size`, `empty`, `swap` — same as vector.
- `lower_bound` and `upper_bound` are also available for sets.
- All operations run in **O(log n)**.

---

## Multiset

Same as `set` (sorted), but **allows duplicate values**.

```cpp
multiset<int> ms;
ms.insert(1);
ms.insert(1);
ms.insert(1);

ms.erase(1);            // erases ALL occurrences of 1
ms.erase(ms.find(1));    // erases only ONE occurrence of 1

cout << ms.count(1);   // counts how many times 1 occurs
```

To erase a specific number of duplicate occurrences (e.g., 2 out of 3 ones):
```cpp
auto it = ms.find(1);
ms.erase(it, next(it, 2));  // erases 2 occurrences starting from the first found
```
All other functions same as `set`.

---

## Unordered Set

Same as `set` — stores **unique** elements — but **does not maintain sorted order** (order is randomized/undefined).

```cpp
unordered_set<int> us;
us.insert(1);
us.insert(5);
us.insert(2);
us.insert(3);
us.insert(6);
// order is unpredictable, but all elements are unique
```

- All operations same as `set` (`insert`, `erase`, `find`, `count`), except `lower_bound` and `upper_bound` do **not** work.
- Average time complexity: **O(1)** for all operations.
- Worst case (rare): **O(n)**.

---

## Map

Stores data as **key–value pairs**. Keys are **unique** and stored in **sorted order** (by key). Values can repeat.

```cpp
map<int, int> mp;
mp[1] = 2;                 // key 1 -> value 2
mp.emplace(3, 1);           // key 3 -> value 1
mp.insert({2, 4});          // key 2 -> value 4
```
Internal storage (sorted by key): `{1:2, 2:4, 3:1}`

- Key and value can be of **any data type** (int, string, pair, etc.).

```cpp
map<pair<int,int>, int> mp2;
mp2[{2, 3}] = 10;  // key = pair(2,3), value = 10
```

### Traversal
```cpp
for (auto it : mp)
    cout << it.first << " " << it.second << endl;
```
For `mp = {1:2, 2:4, 3:1}`:
Output:
````
1 2
2 4
3 1
````

### Access
```cpp
cout << mp[1];   // 2 (exists)
cout << mp[5];   // 0 (key doesn't exist -> returns default value 0)
```

### Find
```cpp
auto it = mp.find(3);      // iterator to key 3
cout << it->second;        // 1

auto it2 = mp.find(5);     // key doesn't exist -> returns mp.end()
```

- `lower_bound`, `upper_bound`, `erase`, `swap`, `size`, `empty` — all available, working the same conceptual way as in `set`.
- Time complexity: **O(log n)** for most operations.

---

## Multimap

Same as `map`, but allows **duplicate keys**, still stored in sorted order.

```cpp
multimap<int,int> mm;
mm.insert({1, 2});
mm.insert({1, 3});  // duplicate key allowed
```

---

## Unordered Map

Same as `map` — unique keys — but **not sorted**; order is randomized.

```cpp
unordered_map<int,int> um;
um[1] = 2;
um[3] = 1;
```

- `map` → O(log n); `unordered_map` → average **O(1)**, worst case O(n).

---

## Algorithms

### Sort
```cpp
int a[] = {1, 5, 3, 2};
sort(a, a + 4);   // sorts entire array; range = [a, a+4) -> a+4 not included
```
Result: `{1, 2, 3, 5}`

Sort a portion:
```cpp
int a[] = {1, 3, 2, 5, 2};
sort(a + 2, a + 4);  // sorts only indices 2 and 3
```

Sort in descending order:
```cpp
int a[] = {1, 3, 5, 2};
sort(a, a + 4, greater<int>());
```
Result: `{5, 3, 2, 1}`

For a vector:
```cpp
sort(v.begin(), v.end());
```

### Custom Comparator

Example: sort an array of pairs by **increasing second element**; if second elements are equal, sort by **decreasing first element**.

```cpp
bool comparator(pair<int,int> p1, pair<int,int> p2) {
    if (p1.second < p2.second) return true;
    else if (p1.second > p2.second) return false;
    else {
        if (p1.first > p2.first) return true;
        else return false;
    }
}

pair<int,int> arr[] = {{1,2}, {2,1}, {4,1}};
sort(arr, arr + 3, comparator);
```
Result: `{4,1}, {2,1}, {1,2}`

How to think about writing a comparator:
- The function returns `true` if `p1` should come **before** `p2` (i.e., they're already in the correct order), and `false` otherwise (triggers a swap).
- Always reason about just **two** elements (`p1` and `p2`) at a time, applying the given sort rule — never think in terms of the whole array.

### `__builtin_popcount`
Returns the count of **set bits (1s)** in the binary representation of a number.

```cpp
cout << __builtin_popcount(7);   // binary 111 -> 3
cout << __builtin_popcount(6);   // binary 110 -> 2
```
Output:
````
3
2
````
For `long long` numbers, use `__builtin_popcountll()`.

### `next_permutation`
Generates the **next lexicographically greater permutation** of a sequence. Returns `false` when there are no more permutations (sequence is in fully descending order).

```cpp
string s = "123";
sort(s.begin(), s.end());  // must start from the sorted (smallest) permutation
do {
    cout << s << endl;
} while (next_permutation(s.begin(), s.end()));
```
Output:
````
123
132
213
231
312
321
````
Important: to print **all** permutations, always start from the sorted sequence — starting from the middle (e.g., `"231"`) only prints permutations from that point onward.

### `max_element` / `min_element`
Returns an **iterator** pointing to the maximum/minimum element in a range.

```cpp
int a[] = {1, 9, 5, 6};
cout << *max_element(a, a + 4);  // 9
cout << *min_element(a, a + 4);  // 1
```
Output:
````
9
1
````

---

## Quick Reference — Time Complexities

| Container | Insert/Erase | Search |
|---|---|---|
| Vector / List / Deque | O(1) amortized at back, O(n) elsewhere | O(n) |
| Stack / Queue | O(1) | — |
| Priority Queue | O(log n) | O(1) for top |
| Set / Map / Multiset / Multimap | O(log n) | O(log n) |
| Unordered Set / Unordered Map | O(1) average, O(n) worst case | O(1) average |
````
