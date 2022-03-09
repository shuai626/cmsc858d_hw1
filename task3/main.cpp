#include "sparse_array.h"
#include <chrono>
#include <stdlib.h>

using namespace std;

int experiment (int size, float sparsity, int operation_count, int func_type) {
    sparse_array s;

    s.create(size);

    int cap_size = floor(size * sparsity);
    int cap_length = floor(size/sparsity);

    int i;
    for (i = 0; i < cap_size; i++) {
      string x = "a";
      uint64_t pos = cap_length*i+1;

      s.append(x, pos);
    }

    auto start = chrono::high_resolution_clock::now();
    for (i = 0; i < operation_count; i++) {
      if (func_type == 0) {
        
        int r = rand() % size + 1;
        string elem;
        s.get_at_rank(r, elem);
      }
      else if (func_type == 1) {
        int r = rand() % size + 1;
        string elem;
        s.get_at_index(r, elem);
      }

    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    return duration.count();
}

int main (int argc, char **argv) {
    int i,j,k;

    int size = atoi(argv[1]);
    float sparsity = atof(argv[2]);

    int operation_count = 100;
    int trials = 100;

    float avg = 0;

    for (k = 0; k <= 1; k++) {
      for (j = 0; j < trials; j++) {
        avg += experiment(size, sparsity, operation_count, k);
      }
      avg /= trials;
      cout << "Average time for operation " << k << " (in microseconds) | sparsity ("<< sparsity << ") | length (" << size << "): " << avg << endl;
      
      avg = 0;
    } 
  

    return 0;
}