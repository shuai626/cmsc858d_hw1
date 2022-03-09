#include "select_support.h"
#include <chrono>
#include <stdlib.h>

using namespace std;


int experiment (int size, int capacity, int select1_operations) {
    sdsl::bit_vector bs_(size);
    srand(time(NULL));

    int i;
    for (i = 0; i < capacity; i++) {
      int X = rand() % size;

      bs_[X]=1;
    }

    rank_support r_(&bs_);
    select_support s_(&r_);

    uint64_t MAX_RANK = r_.rank1(size);
    
    auto start = chrono::high_resolution_clock::now();
    for (i = 0; i < select1_operations; i++) {
      int X = i % MAX_RANK + 1;

      s_.select1(X);
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    return duration.count();
}


int main (int argc, char **argv) {
    int size = atoi(argv[1]);

    sdsl::bit_vector bs(size);

    rank_support r(&bs);
    int i;

    select_support s(&r);

    int capacity = size/2;
    int select1_operations = 100;
    int trials = 100;

    float avg = 0;

    for (i = 0; i < trials; i++) {
      avg += experiment(size, capacity, select1_operations);
    }
    avg /= trials;
    cout << "Average time (in microseconds): " << avg << endl;
    cout << "Overhead (in bits): " << s.overhead() << endl;

    return 0;
}