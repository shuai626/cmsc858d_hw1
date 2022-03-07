#include "select_support.h"
#include <chrono>
#include <stdlib.h>

using namespace std;


int experiment (int capacity, int select1_operations) {
    std::bitset<SIZE> bs_(0);
    srand(time(NULL));

    int i;
    for (i = 0; i < capacity; i++) {
      int X = rand() % SIZE;

      bs_.set(X);
    }

    rank_support r_(&bs_);
    select_support s_(&r_);

    uint64_t MAX_RANK = r_.rank1(SIZE);
    
    auto start = chrono::high_resolution_clock::now();
    for (i = 0; i < select1_operations; i++) {
      // int X = rand() % SIZE + 1;
      int X = i % MAX_RANK + 1;

      s_.select1(X);
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    return duration.count();
}


int main () {
    // string str = "10010111010010100000000000000000";
    // string str = "1001011101001010";
    // string str = "1111111111111111";
    // reverse(str.begin(), str.end());
    // Flip bits since bitset accesses values from lowest to greatest bit
    std::bitset<SIZE> bs(0);

    // cout << "Bitvector: " << bs.to_string() << endl;

    rank_support r(&bs);
    int i;
    // for (i = 1; i <= SIZE; i++) {
    //   cout << "Rank " << i << ": " << r.rank1(i) << endl;
    // }
    // cout << "Overhead (in bits): " << r.overhead() << endl;

    select_support s(&r);

    // for (i = 1; i <= r.rank1(SIZE); i++) {
    //   cout << "Select " << i << ": " << s.select1(i) << endl;
    // }
    // cout << "Overhead (in bits): " << s.overhead() << endl;

    string file = "test";
    // s.save(file);
    s.load(file);

    // for (i = 1; i <= r.rank1(SIZE); i++) {
    //   cout << "Select " << i << ": " << s.select1(i) << endl;
    // }

    int capacity = SIZE/2;
    int select1_operations = 100;
    int trials = 10000;

    float avg = 0;

    for (i = 0; i < trials; i++) {
      avg += experiment(capacity, select1_operations);
    }
    avg /= trials;
    cout << "Average time (in microseconds): " << avg << endl;
    cout << "Overhead (in bits): " << r.overhead() << endl;

    return 0;
}