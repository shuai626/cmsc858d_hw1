## Interface

* select_support(rank_support* r)

Initializes a `select_support` structure with a pointer to a `rank_support`.
The `SIZE` variable of the underlying bitset can be modified in `../task1/rank_support.h`.

* uint64_t select1(uint64_t i)

Returns the index of the bitset element with rank `i`. `i` is **1-indexed**: i.e. `1 <= i <= r->rank1(SIZE)`.

* uint64_t overhead()

Return the number of bits that the `select_support` class uses.

* void save(string& fname)

Serializes the `select_support` class into file `task2/<fname>`.

The file follows the same format as the `rank_support` class (See `../task1/README.md`).

* void load(string& fname)

Deserializes the file `filename` into the `select_support` class.

## Compilation Instructions

Perform the following from within the `task2` directory

1. Modify the `SIZE` const variable found in `../task1/rank_support.h` to the size of your bitvector
2. Call `make` 
3. Run `select.exe`