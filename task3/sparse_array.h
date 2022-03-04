#ifndef SPARSE_ARRAY
#define SPARSE_ARRAY

#include "../task2/select_support.h"

using namespace std;

class sparse_array {
  select_support* s_;

public:
  void create(uint64_t size);
  void append(string elem, uint64_t pos);
  bool get_at_rank(uint64_t r, string& elem);
  bool get_at_index(uint64_t r, string& elem);
  uint64_t num_elem_at(uint64_t r);
  uint64_t size();
  uint64_t num_elem();
  void save(string& fname);
  void load(string& fname);
};

#endif