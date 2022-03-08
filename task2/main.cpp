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
    std::bitset<SIZE> bs(0);

    rank_support r(&bs);
    int i;

    select_support s(&r);

    string file = "select_serialize";
    s.load(file);

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