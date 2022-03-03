#ifndef RANK_SUPPORT
#define RANK_SUPPORT

#include <bit> // For popcount
#include <bitset> // For bit vectors
#include <iostream> // For save and load files
#include <fstream> // For save and load files
#include <math.h> // For log2 function
#include <algorithm> // For reversing bit string

using namespace std;

// Modify N to change size of bit vector
const int N = 16;

class rank_support {
  bitset<N>* b_;
  uint64_t* Rs_;
  uint64_t* Rb_;
  float N_;
  float S_;
  float B_;

public:
  rank_support(bitset<N>* b);
  ~rank_support();
  uint64_t rank1(uint64_t i);
  uint64_t overhead();
  void save(string& fname);
  void load(string& fname);
};

#endif