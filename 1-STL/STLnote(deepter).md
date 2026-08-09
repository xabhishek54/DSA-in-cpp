# C++ STL — Deeper Concepts (Addendum)

## 1. Vector Internals — Size vs Capacity, and Reallocation

A `vector` is NOT just "an array that magically grows." Internally it maintains two numbers:
- **size** — how many elements are actually stored
- **capacity** — how much memory is currently allocated (often more than size)

When you `push_back()` and the vector is already at full capacity, it does **not** just add one more slot. It:
1. Allocates a **new, larger block of memory** (typically **double** the old capacity).
2. **Copies (or moves) every existing element** into the new block.
3. Deletes the old block.
4. Adds the new element.

```cpp
vector<int> v;
cout << v.capacity(); // 0
v.push_back(1);
cout << v.capacity(); // 1
v.push_back(2);
cout << v.capacity(); // 2
v.push_back(3);
cout << v.capacity(); // 4  (doubled, even though size is only 3)
```
Output:
````
0
1
2
4
````

**Why this matters:** a single `push_back` can occasionally cost O(n) (during a reallocation), but because doubling happens rarely, the **average cost per push_back over many calls is O(1)** — this is called **amortized O(1)**. This is exactly why `insert()` in the middle of a vector is expensive (O(n)): every element after the insertion point has to be physically shifted one position to the right in memory — this is unrelated to reallocation and happens every single time, not just occasionally.

This also explains why elements in a vector are stored in **contiguous memory** — which is why pointer arithmetic like `it + 2` or `a + 4` works cleanly for vectors and arrays, but would NOT make logical sense for `list`, `set`, or `map` (their elements are scattered across memory, linked via pointers/tree nodes, not laid out back-to-back).

---

## 2. What an Iterator Actually Is

Loosely, an iterator behaves like a **generalized pointer**. For a vector/array, it basically *is* a pointer — `v.begin()` is functionally close to `&v[0]`.

```cpp
vector<int> v = {20, 10, 15, 5, 7};
auto it = v.begin();   // points to the memory holding 20
```

- `*it` → dereferences → gives you the **value** stored at that address (`20`)
- `it++` → moves the iterator to point to the **next contiguous memory slot** (`10`)
- `it + 2` → jumps two memory slots ahead (only valid for **random-access iterators** — vector, deque, array; NOT valid for `list` or `set`, where you can only do `it++` one step at a time, because their elements aren't contiguous)

`v.end()` is a **deliberately invalid** iterator — it points one-past-the-last element. This is intentional: it gives you a clean, unambiguous stopping condition (`it != v.end()`) without ever dereferencing memory that doesn't logically belong to the container.

### Reverse Iterators — `rbegin()` / `rend()`
```cpp
vector<int> v = {10, 20, 30, 40};
for (auto it = v.rbegin(); it != v.rend(); it++)
    cout << *it << " ";
```
Output:
````
40 30 20 10
````
- `rbegin()` points to the **last** element (`40`), but internally it's implemented so that incrementing it (`it++`) moves **backward** through the container.
- `rend()` points to one-position-**before** the first element (the mirror image of `end()`).
- Rarely used explicitly in day-to-day code (people usually just reverse-loop with indices), but it's good to recognize in others' code.

### Iterator Invalidation (important, commonly a source of bugs)
Calling `erase()` or `insert()` on a vector can invalidate existing iterators, because the underlying memory may shift or be reallocated:

```cpp
vector<int> v = {1, 2, 3, 4};
auto it = v.begin();
v.erase(v.begin() + 1);
cout << *it;   // UNDEFINED / unreliable — 'it' may no longer be valid
```
**Rule of thumb:** after any `insert`/`erase` on a vector, re-fetch your iterator — don't reuse an old one. `erase()` actually returns a valid iterator to the element right after the one removed, so the safe pattern is:
```cpp
it = v.erase(it);  // reassign, don't just call erase and keep using old 'it'
```

---

## 3. `push_back` vs `emplace_back` — the real difference

`push_back` takes an already-constructed object and **copies (or moves)** it into the container.
`emplace_back` takes the **raw arguments** and constructs the object **directly inside** the container's memory — no separate temporary object, no copy.

```cpp
vector<pair<int,int>> v;
v.push_back(make_pair(1, 2));  // pair is built first, THEN copied in
v.emplace_back(1, 2);           // pair is built directly inside the vector
```
For simple types like `int`, the difference is negligible. For heavier objects (strings, custom classes, pairs), `emplace_back` avoids an unnecessary copy/move step — which is why it's generally recommended.

---

## 4. Why `list` Beats `vector` at the Front

A `vector` is backed by one contiguous memory block — inserting at the front means **shifting every other element one slot to the right**, an O(n) operation.

A `list` is a **doubly linked list**: every element ("node") stores its value **plus two pointers** — one to the previous node, one to the next node. To insert at the front, you just:
1. Create a new node.
2. Point its `next` to the old first node.
3. Point the old first node's `prev` back to the new node.
4. Update the list's "head" pointer.

No shifting of other elements needed — that's why `push_front()` is O(1) for `list` but O(n) for `vector`.

**Trade-off:** because list nodes are scattered in memory (not contiguous), you lose fast random access — `l[3]` isn't a valid operation on a `list` the way it is on a `vector`. You'd have to walk the list node by node.

---

## 5. Stack and Queue Are "Adapters," Not Real Containers

`stack` and `queue` don't have their own storage logic — by default, they're built **on top of a `deque`** internally (you can even change the underlying container). They simply restrict which operations you're allowed to call:
- `stack` only exposes `push`/`pop`/`top` at one end → forces LIFO behavior.
- `queue` only exposes push at the back and pop/read at the front → forces FIFO behavior.

This is why neither supports indexed access — the restriction is deliberate, not a missing feature.

---

## 6. Priority Queue — What's Actually Happening Inside

A `priority_queue` is a **binary heap** stored inside a `vector` — specifically a **max-heap** by default. Key heap property: **every parent node is ≥ its children** (for max-heap).

Instead of pointers, a heap is stored as a flat array where, for a node at index `i`:
- left child is at index `2i + 1`
- right child is at index `2i + 2`
- parent is at index `(i - 1) / 2`

When you `push()`, the new element is placed at the end, then **"bubbled up"** — swapped with its parent repeatedly until the heap property holds. That's the `O(log n)` — the height of the tree is `log n`, and in the worst case the element bubbles all the way up.

When you `pop()`, the top (root) is removed, the last element is moved to the root position, and it's **"bubbled down"** (swapped with its larger child repeatedly) until the heap property holds again — also `O(log n)`.

`top()` is `O(1)` simply because the max element always sits at index 0 — no searching needed.

---

## 7. Set and Map — The Actual Data Structure (Red-Black Tree)

The video mentions "a tree is maintained" but doesn't name it: `set`, `multiset`, `map`, and `multimap` are implemented using a **self-balancing binary search tree**, specifically a **Red-Black Tree**.

Why this matters:
- A plain BST can degrade to a straight line (O(n) operations) if you insert sorted data (e.g., 1, 2, 3, 4, 5...).
- A **self-balancing** tree automatically re-arranges itself (via rotations) after every insert/delete to guarantee its height stays close to `log n`, no matter what order you insert in.
- That guaranteed height is *exactly* why `find`, `insert`, `erase` are all a reliable **O(log n)** — not just "usually," but **always**, even in the worst case. This is the key contrast with `unordered_set`/`unordered_map`.

---

## 8. `lower_bound` and `upper_bound` — Actually Explained

The video repeatedly says "watch another video for this" — here's the direct explanation, since these are extremely commonly used in DSA problems.

Both work on **sorted** containers (or sorted ranges) and return an **iterator**:

- **`lower_bound(x)`** → returns an iterator to the **first element that is NOT less than `x`** (i.e., the first element `>= x`).
- **`upper_bound(x)`** → returns an iterator to the **first element that is strictly greater than `x`**.

```cpp
set<int> s = {10, 20, 30, 30, 40};   // note: set stores unique -> effectively {10,20,30,40}

auto lb = s.lower_bound(30);  // points to 30 (first element >= 30)
auto ub = s.upper_bound(30);  // points to 40 (first element > 30)

cout << *lb;  // 30
cout << *ub;  // 40
```
Output:
````
30
40
````

If `x` is bigger than every element, both return the container's `end()`.

```cpp
set<int> s = {10, 20, 30};
auto it = s.lower_bound(100);
cout << (it == s.end());  // true (1)
```
Output:
````
1
````

**Why it's fast:** because the underlying tree is sorted and balanced, `lower_bound`/`upper_bound` walk down the tree in **O(log n)**, similar to binary search — this is precisely why they **don't work on `unordered_set`/`unordered_map`** (no meaningful order to binary-search through).

For plain sorted arrays/vectors, the free-function versions work the same way:
```cpp
vector<int> v = {10, 20, 30, 40};
auto it = lower_bound(v.begin(), v.end(), 25);  // first element >= 25 -> points to 30
cout << *it;
```
Output:
````
30
````

---

## 9. `map[key]` Has a Hidden Side Effect

This is a classic gotcha the video mentions in passing ("if it does not exist, it gives you zero") but doesn't flag as dangerous.

```cpp
map<int,int> mp;
mp[1] = 2;
cout << mp.size();   // 1

cout << mp[5];        // prints 0 — but ALSO silently INSERTS key 5 with value 0!
cout << mp.size();   // 2 now — a new entry was created just by reading it
```
Output:
````
1
0
2
````

If you only want to **check** whether a key exists without accidentally creating it, use `find()` or `count()` instead of `[]`:
```cpp
if (mp.find(5) != mp.end()) { /* key exists */ }
if (mp.count(5)) { /* key exists */ }
```

---

## 10. Unordered Containers — Why "Usually O(1), Sometimes O(n)"

`unordered_set`/`unordered_map` use a **hash table**, not a tree.

- Each key is passed through a **hash function**, which converts it into an index into an internal array (of "buckets").
- To find/insert a key, you compute its hash, jump straight to that bucket — **O(1) on average**, no tree traversal needed.
- **Collisions**: two different keys can hash to the same bucket. When that happens, the colliding keys are stored together in that bucket (commonly as a small list), and multiple keys landing in the same bucket must be scanned one by one.
- **Worst case**: if many/all keys collide into the same bucket (rare, but possible with adversarial or unlucky data), lookup degrades to scanning that whole bucket — **O(n)**.

This is the concrete reason behind "average O(1), worst case O(n)" — it's not a vague disclaimer, it's a direct consequence of how hashing and collisions work.

---

## 11. Comparator Logic — The Rule Beneath the Example

The video's pair-sorting example follows a general contract that's worth stating explicitly: a comparator function passed to `sort` must define what's called a **strict weak ordering** — essentially:

> `comparator(a, b)` returns `true` if and only if `a` must appear **strictly before** `b` in the final order.

Practical checklist when writing one:
1. If `a` and `b` are equal by your rule → return `false` (never return `true` for equal elements; doing so can cause undefined behavior in some STL implementations).
2. Never write logic where `comparator(a,b)` and `comparator(b,a)` can **both** return `true` — that's a contradiction, and `sort` will misbehave or crash unpredictably.
3. Build it rule by rule, in priority order: check the primary condition first (`return`/`else if` for the deciding factor), then fall through to the tie-breaker only when the primary condition is exactly equal.

This is why the video's structure was:
```cpp
if (p1.second < p2.second) return true;        // primary rule strictly satisfied
else if (p1.second > p2.second) return false;   // primary rule strictly violated
else {                                            // primary rule tied -> use secondary rule
    if (p1.first > p2.first) return true;
    else return false;
}
```
Notice the `else` block never returns `true` when `p1.first == p2.first` — that's the "equal → false" rule being followed correctly.

---

## 12. `next_permutation` — What's Actually Happening

`next_permutation` doesn't brute-force generate all permutations and pick the next one — it uses a specific in-place algorithm:
1. Scan from the right, find the first index `i` where `a[i] < a[i+1]` (the first place the sequence stops being non-increasing from the right).
2. If no such index exists, the sequence is in fully descending order — this is the **last** permutation, so return `false`.
3. Otherwise, scan from the right again to find the smallest element to the right of `i` that is still **greater** than `a[i]`, and swap them.
4. Reverse everything to the right of position `i` (since that portion is guaranteed to be in descending order at this point, reversing makes it ascending — the smallest possible arrangement for that suffix).

This is why you must start from the **sorted (ascending)** sequence to enumerate *all* permutations — sorted-ascending is the unique starting point that has no "earlier" permutation.
````
