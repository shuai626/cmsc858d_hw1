## Interface

* void create(uint64_t size)

Creates an empty `sparse_array` structure of length `size`. `size` cannot be greater than the `SIZE` constant defined in `../task1/rank_support.h`.

* void append(string elem, uint64_t pos)

Appends the element `elem` at index `pos` of the sparse array. `pos` is **1-indexed**: i.e. `1 <= pos <= SIZE`.

* bool get_at_rank(uint64_t r, string& elem)

Places a reference to the `r-th` present item in the array in the reference `elem`. It returns `true` if there were `>= r` items. Otherwise, it returns `false`.

`r` is **1-indexed**: i.e. `1 <= r <= num_elem()`.

* bool get_at_index(uint64_t r, string& elem)

Returns `true` and places a reference to the item at the `r-th` index of the sparse bitvector into `elem` if it exists. Otherwise, it returns `false`.

`r` is **1-indexed**: i.e. `1 <= r <= SIZE`.

* uint64_t num_elem_at(uint64_t r)

Returns the count of present elements up to and including the index `r`.

`r` is **1-indexed**: i.e. `1 <= r <= SIZE`.

* uint64_t size()

Returns the size of the sparse array.

* uint64_t num_elem()

Returns the number of present elements in the sparse array.

* void save(string& fname)

Serializes the `sparse_array` class into file `task3/<fname>`.

The file follows the following format:
```
line1: <bitvector as string>
line2: <size of sparse_array>
line3: <non-empty elem1 of sparse_array> <elem2> <elem3> ...
```

* void load(string& fname)

Deserializes the file `filename` into the `sparse_array` class.

## Compilation Instructions

Perform the following from within the `task3` directory

1. Modify the `SIZE` const variable found in `../task1/rank_support.h` to the size of your bitvector
2. Call `make` 
3. Run `sparse_array.exe`