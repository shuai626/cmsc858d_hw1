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

    std::bitset<SIZE> bs(0);

    rank_support r(&bs);
    string file = "rank_serialize";
    r.load(file);

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