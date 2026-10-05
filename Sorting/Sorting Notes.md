## Selection Sort
Selection sort is a simple, in-place comparison sorting algorithm that sorts an array by repeatedly finding the minimum (or maximum) element from the unsorted portion and moving it to the beginning.
## How Selection Sort Works
The algorithm conceptually splits the list into two parts: a sorted section on the left and an unsorted section on the right.

* Find the Minimum: It scans the unsorted section to locate the smallest element.
* Swap: It swaps this smallest element with the first element of the unsorted section.
* Shift Boundary: The boundary between the sorted and unsorted sections moves one element to the right.
* Repeat this process until the entire array is sorted.

Initial Array: [29, 10, 14, 37, 13]

Pass 1: Find min in [29, 10, 14, 37, 13] -> 10. Swap with 29.
        [10 | 29, 14, 37, 13]
Pass 2: Find min in     [29, 14, 37, 13] -> 13. Swap with 29.
        [10, 13 | 14, 37, 29]
Pass 3: Find min in         [14, 37, 29] -> 14. Already in place.
        [10, 13, 14 | 37, 29]
Pass 4: Find min in             [37, 29] -> 29. Swap with 37.
        [10, 13, 14, 29 | 37] (Sorted!)

## Algorithm Complexity & Properties

| Metric / Property | Complexity / Behavior | Description |
|---|---|---|
| Best-Case Time | O(n²) | Still scans the entire unsorted list even if already sorted. |
| Average-Case Time | O(n²) | Requires two nested loops to process elements. |
| Worst-Case Time | O(n²) | Quadratic time runtime regardless of initial order. |
| Space Complexity | O(1) | In-place algorithm; requires no extra memory. |
| Stability | Not Stable | Can change the relative order of duplicate elements. |
| Data Structure | Array / List | Works best on small datasets. |

## Pseudocode

procedure selectionSort(list A)
    n = length(A)
    
    for i from 0 to n - 1 do
        # Assume the current index holds the minimum value
        minIndex = i
        
        # Scan the unsorted part of the list to find the true minimum
        for j from i + 1 to n do
            if A[j] < A[minIndex] then
                minIndex = j
            end if
        end for
        
        # Swap the found minimum element with the first unsorted element
        if minIndex != i then
            swap(A[i], A[minIndex])
        end if
    end for
end procedure

## Advantages & Disadvantages

* Pro (Minimal Memory Writes): Performs a maximum of O(n) swaps. This makes it highly efficient if you are working with hardware where writing to memory is significantly more expensive than reading it.
* Con (Inefficient): Because its time complexity is always O(n²), it scales poorly for large datasets compared to algorithms like merge sort or quicksort.

Would you like me to add a section comparing this to Insertion Sort using pseudocode, or perhaps walk through the exact steps of making this algorithm stable? Let me know how you want to expand your Markdown file.

# Bubble Sort

**Bubble sort** is a simple, **in-place comparison sorting algorithm**. It works by repeatedly stepping through the list, comparing adjacent elements, and swapping them if they are in the wrong order. This process passes through the list repeatedly until no swaps are needed.

### How Bubble Sort Works
The algorithm conceptually pushes the largest unsorted element to its correct position at the end of the list during each pass (like bubbles rising to the surface).

* **Compare Adjacent Elements:** It starts at the beginning of the list and compares the element at index `j` with the element at `j + 1`.
* **Swap if Needed:** If the left element is greater than the right element, they swap places.
* **Shift Boundary:** After a full pass through the unsorted section, the largest element settles at the end. The unsorted boundary shrinks by one.
* **Repeat** this process until a full pass completes without a single swap occurring.

```text
Initial Array: [29, 10, 14, 37, 13]

Pass 1: (Largest element 37 bubbles to the end)
        [29, 10, 14, 37, 13] -> Compare 29, 10. Swap. -> [10, 29, 14, 37, 13]
        [10, 29, 14, 37, 13] -> Compare 29, 14. Swap. -> [10, 14, 29, 37, 13]
        [10, 14, 29, 37, 13] -> Compare 29, 37. Okay. -> [10, 14, 29, 37, 13]
        [10, 14, 29, 37, 13] -> Compare 37, 13. Swap. -> [10, 14, 29, 13 | 37]

Pass 2: (Next largest element 29 bubbles up)
        [10, 14, 29, 13 | 37] -> Passes through remaining unsorted elements.
        [10, 14, 13 | 29, 37]

Pass 3: (Next largest element 14 bubbles up)
        [10, 13 | 14, 29, 37] (Sorted!)
```

### Algorithm Complexity & Properties

| Metric / Property | Complexity / Behavior | Description |
| :--- | :--- | :--- |
| **Best-Case Time** | O(n) | Happens if the array is already sorted (using an optimized swap flag). |
| **Average-Case Time** | O(n²) | Requires nested loops to compare adjacent elements. |
| **Worst-Case Time** | O(n²) | Happens when the array is sorted in reverse order. |
| **Space Complexity** | O(1) | In-place algorithm; requires no extra memory allocations. |
| **Stability** | **Stable** | Does not change the relative order of duplicate elements. |
| **Data Structure** | Array / List | Best suited for small datasets or nearly sorted collections. |

### Pseudocode
```text
procedure bubbleSort(list A)
    n = length(A)
    
    # Outer loop decreases the unsorted boundary size from right to left
    for i from n - 1 down to 1 do
        # Track if any swap happened during this pass
        swapped = false
        
        # Inner loop compares adjacent elements up to the unsorted boundary
        for j from 0 to i - 1 do
            if A[j] > A[j + 1] then
                swap(A[j], A[j + 1])
                swapped = true
            end if
        end for
        
        # Optimization: If no elements were swapped, the list is already sorted
        if swapped == false then
            break
        end if
    end for
end procedure
```

### Advantages & Disadvantages
* **Pro (Adaptive & Stable):** It is highly efficient for collections that are already sorted or nearly sorted, achieving a best-case runtime of O(n). It preserves the relative placement of duplicate items (stable).
* **Con (Heavy Memory Writes):** Unlike selection sort, bubble sort writes to memory continuously via frequent adjacent swaps, making it highly inefficient on large datasets or systems where writing to memory is expensive.


# Insertion Sort

**Insertion sort** is a simple, **in-place comparison sorting algorithm**. It works similarly to the way you sort playing cards in your hands: the array is virtually split into a sorted and an unsorted part, and values from the unsorted part are picked and placed into the correct position in the sorted part.

### How Insertion Sort Works
The algorithm builds the final sorted array one item at a time by shifting elements out of the way to insert the current item.

* **Pick the Element:** It loops from the second element (index 1) to the end of the array, picking one element at a time to insert.
* **Scan Backward:** It compares the picked element with the elements to its left (the sorted sub-array).
* **Swap/Shift:** If the picked element is smaller than the item on its left, they swap places. This continues backward until it reaches a value smaller than itself or hits the beginning of the list.
* **Repeat** for all remaining unsorted items.

```text
Initial Array:

Pass 1: Pick 10. Compare with 29. Swap.
        [10, 29 | 14, 37, 13]
Pass 2: Pick 14. Compare with 29. Swap. Compare with 10. Stop.
        [10, 14, 29 | 37, 13]
Pass 3: Pick 37. Compare with 29. Stop (already greater).
        [10, 14, 29, 37 | 13]
Pass 4: Pick 13. Compare and shift backward until placed between 10 and 14.
        [10, 13, 14, 29, 37] (Sorted!)
```

### Algorithm Complexity & Properties

| Metric / Property | Complexity / Behavior | Description |
| :--- | :--- | :--- |
| **Best-Case Time** | O(n) | Happens when the array is already fully sorted (no swaps occur). |
| **Average-Case Time** | O(n²) | Requires scanning and shifting elements on average. |
| **Worst-Case Time** | O(n²) | Happens when the array is sorted in reverse order. |
| **Space Complexity** | O(1) | In-place algorithm; does not require extra memory allocations. |
| **Stability** | **Stable** | Does not change the relative order of duplicate elements. |
| **Data Structure** | Array / List | Exceptionally fast for small or nearly sorted datasets. |

### Pseudocode
```text
procedure insertionSort(list A)
    n = length(A)
    
    # Outer loop starts at index 1 as the first element is already "sorted"
    for i from 1 to n - 1 do
        # Inner loop steps backward from the current index i down to 1
        for j from i down to 1 do
            # Compare current element with its left neighbor
            if A[j] < A[j - 1] then
                swap(A[j], A[j - 1])
            else
                # If it's already in the correct place, break early for this pass
                break
            end if
        end for
    end for
end procedure
```

### Advantages & Disadvantages
* **Pro (Highly Adaptive):** Like Bubble Sort, it is extremely efficient for nearly sorted data, running in O(n) time. It also features very low overhead, outperforming more complex algorithms (like Quicksort) on small array sizes.
* **Con (High Shifting Cost):** Because elements must be swapped step-by-step to the left, it performs a high number of operations on completely unsorted or reversed large datasets.
