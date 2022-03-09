#ifndef RANK_SUPPORT
#define RANK_SUPPORT

#include <bit> // For popcount
#include <iostream> // For save and load function
#include <fstream> // For save and load function
#include <sstream> // For load function
#include <math.h> // For log2 function
#include <algorithm> // For reversing bit string
#include <sdsl/bit_vectors.hpp> // For bit vector

using namespace std;

class rank_support {
  uint64_t* Rs_;
  uint64_t* Rb_;

public:
  sdsl::bit_vector* b_;

  rank_support(sdsl::bit_vector* b);
  ~rank_support();
  uint64_t rank1(uint64_t i);
  uint64_t overhead();
  void save(string& fname);
  void load(string& fname);
};

#endif