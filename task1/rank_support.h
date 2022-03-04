#ifndef RANK_SUPPORT
#define RANK_SUPPORT

#include <bit> // For popcount
#include <bitset> // For bit vectors
#include <iostream> // For save and load function
#include <fstream> // For save and load function
#include <sstream> // For load function
#include <math.h> // For log2 function
#include <algorithm> // For reversing bit string

using namespace std;

// TODO: CONSIDER USING sdsl FOR BIT VECTOR

// Modify N to change size of bit vector
const int SIZE = 16;

class rank_support {
  bitset<SIZE>* b_;
  uint64_t* Rs_;
  uint64_t* Rb_;

public:
  rank_support(bitset<SIZE>* b);
  ~rank_support();
  uint64_t rank1(uint64_t i);
  uint64_t overhead();
  void save(string& fname);
  void load(string& fname);
};

#endif