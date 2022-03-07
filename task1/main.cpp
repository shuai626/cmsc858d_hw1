#include "rank_support.h"
#include <chrono>
#include <stdlib.h>

using namespace std;

int experiment (int capacity, int rank1_operations) {
    std::bitset<SIZE> bs_(0);
    srand(time(NULL));

    int i;
    for (i = 0; i < capacity; i++) {
      int X = rand() % SIZE;

      bs_.set(X);
    }

    rank_support r_(&bs_);
    

    auto start = chrono::high_resolution_clock::now();
    for (i = 0; i < rank1_operations; i++) {
      // int X = rand() % SIZE + 1;
      int X = i % SIZE + 1;

      r_.rank1(X);
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    return duration.count();
}

int main () {
    int i;
    // string s = "10010111010010100000000000000000";
    // string s = "1001011101001010";
    // string s = "0100100001000000";
    // reverse(s.begin(), s.end());
    // Flip bits since bitset accesses values from lowest to greatest bit
    std::bitset<SIZE> bs(0);

    // cout << "Bitvector: " << bs.to_string() << endl;

    rank_support r(&bs);

    string file = "test";
    r.load(file);

    for (i = 1; i <= SIZE; i++) {
      cout << "Rank " << i << ": " << r.rank1(i) << endl;
    }

    int capacity = SIZE/2;
    int rank1_operations = 100;
    int trials = 10000;

    float avg = 0;

    for (i = 0; i < trials; i++) {
      avg += experiment(capacity, rank1_operations);
    }
    avg /= trials;
    cout << "Average time (in microseconds): " << avg << endl;
    cout << "Overhead (in bits): " << r.overhead() << endl;

    return 0;
}