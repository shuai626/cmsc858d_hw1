#ifndef SELECT_SUPPORT
#define SELECT_SUPPORT

#include "../task1/rank_support.h"

using namespace std;

class select_support {
  rank_support* r_;

public:
  select_support(rank_support* r);
  uint64_t select1(uint64_t i);
  uint64_t overhead();
  void save(string& fname);
  void load(string& fname);
};

#endif