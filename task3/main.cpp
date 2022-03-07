#include "sparse_array.h"
#include <chrono>
#include <stdlib.h>

using namespace std;


int experiment (float sparsity, int operation_count, int func_type) {
    sparse_array s;

    s.create(SIZE);

    int size = floor(SIZE * sparsity);

    int i;
    for (i = 0; i < size; i++) {
      string x = "a";
      uint64_t pos = SIZE/sparsity*i + 1; 

      s.append(x, pos);
    }

    auto start = chrono::high_resolution_clock::now();
    for (i = 0; i < operation_count; i++) {
      if (func_type == 0) {
        //append
      }
      else if (func_type == 1) {
        // get_at_rank
      }
      else if (func_type == 2) {
        // get_at_index
      }
      else if (func_type == 3) {
        // num_elem_at
      }
      else if (func_type == 4) {
        // size()
      }
      else if (func_type == 5) {
        // num_elem()
      }
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    return duration.count();
}

int main () {
    int i,j,k;

    float sparsity [5] = {.01,.05,.10,.15,.20};
    int operation_count = 100;
    int trials = 10000;

    float avg = 0;

    for (i = 0; i < 5; i++) {
      cout << "Sparsity: " << sparsity[i] << endl;;
      for (k = 0; k <= 5; k++) {
        for (j = 0; j < trials; j++) {
          avg += experiment(sparsity[i], operation_count, k);
        }
        avg /= trials;
        cout << "Average time for operation " << k << " (in microseconds): " << avg << endl;
        
        avg = 0;
      } 
    }

    return 0;
}