#include "select_support.h"

select_support::select_support(rank_support* r) {
  r_ = r;
}

uint64_t select_support::select1(uint64_t i) {
  uint64_t low = 1;
  uint64_t high = r_->b_->size();
  uint64_t mid = 0;
  uint64_t rank = 0;


  while (low <= high) {
    mid = low + (high - low)/2;

    rank = r_->rank1(mid);

    if (i == rank) {
      // mid will always have neighbors, otherwise mid == 1 or b_->size() which 
      // would break the while loop condition
      uint64_t rank_l = r_->rank1(mid - 1);

      if (rank_l < rank) {
        return mid;
      }
      else {
        high = mid - 1;
      }
    }
    else if (i < rank) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }

  return mid;
}

uint64_t select_support::overhead() {
  return r_->overhead() + sizeof(rank_support*)*8;
}

void select_support::save(string& fname) {
  r_->save(fname);
}

void select_support::load(string& fname) {
  r_->load(fname);
}