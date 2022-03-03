#include "rank_support.h"

rank_support::rank_support(bitset<SIZE>* b) {
  b_ = b;
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  uint64_t Rs_size_ = ceil(N/S) - 1;
  uint64_t Rb_size_ = ceil(N/B) - 2;

  // Initialize the superblock and block arrays
  // The first index always stores 0, optimize by dropping it
  Rs_ = (uint64_t *) calloc(Rs_size_, sizeof(ceil(log2(N))));
  Rb_ = (uint64_t *) calloc(Rb_size_, sizeof(ceil(log2(ceil(log2(N))))));

  // Populate the superblock array
  uint64_t i, j;
  for (i = 0; i < Rs_size_; i++) {
    if (i > 0) {
      Rs_[i] += Rs_[i-1];
    }
    for (j = S*i; j < S*(i+1); j++) {
      if ((*b_)[j]) {
        Rs_[i] += 1;
      }
    }
  }
  
  // Populate the block array
  int r = floor(S/B - 1);
  for (i = 0; i < Rb_size_; i++) {
    int Z = floor((i)/r)*S+((i)%r)*B;
    if (i % r != 0) {
      Rb_[i] += Rb_[i-1];
    }
    for (j = Z; j < Z+B; j++) {
      if ((*b_)[j]) {
        Rb_[i] += 1;
      }
    }
  }
}

/* Returns the number of 1s in the underlying bit-vector 
up to position i (inclusive). */
uint64_t rank_support::rank1(uint64_t i) {
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  if (i == N) {
    return b_->count();
  }

  uint64_t s = floor((i-1)/S);
  uint64_t b = floor((i-1)/B);

  int rank = 0;

  if (s > 0) {
    rank += Rs_[s-1];
  }

  int r = floor(S/B);

  if (b % r != 0) {
    int j = floor((b)/r)*(r-1) + b%r - 1;
    rank += Rb_[j];
  }

  // Use popcount for the Rp block. Extract block by building mask
  bitset<SIZE> Rp(*b_);
  Rp >>= b*B;
  Rp <<= (N - i + b*B);
  Rp >>= (N - i + b*B);

  rank += Rp.count();
  return rank;
}

/* Returns the size of the rank data structure (in bits) that is 
required to support constant-time rank on the current bitvector. */
uint64_t rank_support::overhead() {
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  return (sizeof(Rs_) + (ceil(N/S) - 1) * sizeof(ceil(log2(N)))
       + sizeof(Rb_) + (ceil(N/B) - 2) * sizeof(ceil(log2(ceil(log2(N))))))
        * 8 + b_->size();
}

/* Saves the rank data structure for this bit vector to the file fname 
(your bit vector should also have a save() function). */
void rank_support::save(string& fname) {
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  ofstream out;
  out.open(fname);
  out << (b_->to_string()) << endl;

  uint64_t i;
  uint64_t Rs_size_ = ceil(N/S) - 1;
  for (i = 0; i < Rs_size_; i++) {
    if (i > 0) {
      out << " ";
    }
    out << Rs_[i];
  }
  out << endl;

  uint64_t Rb_size_ = ceil(N/B) - 2;
  for (i = 0; i < Rb_size_; i++) {
    if (i > 0) {
      out << " ";
    }
    out << Rb_[i];
  }
  out << endl;

  out.close();

  return;
}

/* Loads the rank data structure for this bit vector from the file fname 
(your bit vector should also have a load() function). */
void rank_support::load(string& fname) {
  ifstream in(fname);
  string line;

  getline(in, line);

  bitset<SIZE> new_b(line);
  *b_ &= 0b0;
  *b_ |= new_b;

  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  uint64_t Rs_size_ = ceil(N/S) - 1;
  uint64_t Rb_size_ = ceil(N/B) - 2;

  getline(in, line);
  free(Rs_);
  Rs_ = (uint64_t *) calloc(Rs_size_, sizeof(ceil(log2(N))));
  stringstream Rs_text_stream(line);
  string Rs_item;
  int i = 0;
  while (std::getline(Rs_text_stream, Rs_item, ' ')) {
      Rs_[i] = stoll(Rs_item);
      i++;
  }

  getline(in, line);
  free(Rb_);
  Rb_ = (uint64_t *) calloc(Rb_size_, sizeof(ceil(log2(ceil(log2(N))))));
  stringstream Rb_text_stream(line);
  string Rb_item;
  i = 0;
  while (std::getline(Rb_text_stream, Rb_item, ' ')) {
      Rb_[i] = stoll(Rb_item);
      i++;
  }

  in.close();

  return;
}

rank_support::~rank_support() {
  free(Rs_);
  free(Rb_);
}

