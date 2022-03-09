#include "rank_support.h"

rank_support::rank_support(sdsl::bit_vector* b) {
  b_ = b;
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  uint64_t Rs_size_ = ceil(N/S);
  uint64_t Rb_size_ = ceil(N/B);

  // Initialize the superblock and block arrays
  // The first index always stores 0, optimize by dropping it
  Rs_ = (uint64_t *) calloc(Rs_size_, ceil(sizeof(ceil(log2(N))))/8);
  Rb_ = (uint64_t *) calloc(Rb_size_, ceil(sizeof(ceil(log2(ceil(log2(N))))))/8);

  
  uint64_t i;
  uint64_t j = 0;
  uint64_t c = 0;
  uint64_t _S = floor(S);
  uint64_t _B = floor(B);

  // Populate the superblock array
  for (i = 0; i < N; i++) {
    if (i % _S == 0) {
      Rs_[j] = c;
      j++;
    }

    if ((*b_)[i] == 1) {
      c++;
    }
  }

  // Populate the block array
  j = 0;
  c = 0;
  for (i = 0; i < N; i++) {
    if (i % _S == 0) {
      c = 0;
    }
    if (i % _B == 0) {
      Rb_[j] = c;
      j++;
    }
    
    if ((*b_)[i] == 1) {
      c++;
    }
  }
}

/* Returns the number of 1s in the underlying bit-vector 
up to position i (inclusive). */
uint64_t rank_support::rank1(uint64_t i) {
  
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  uint64_t Rs_size_ = ceil(N/S);
  uint64_t Rb_size_ = ceil(N/B);

  uint64_t s = floor((i)/S);
  uint64_t b = floor((i)/B);

  if (i/S >= Rs_size_) {
    s = Rs_size_ - 1;
  }
  if (i/B >= Rb_size_) {
    b = Rb_size_ - 1;
  }

  int rank = Rs_[s] + Rb_[b];

  // Use popcount for the Rp block. Extract block by building mask
  uint64_t x = floor(B);
  uint64_t l = i - b*x;
  if (l > 64) {

  }
  uint64_t v = b_->get_int(b*x, l);

  rank += popcount(v);
  return rank;
}

/* Returns the size of the rank data structure (in bits) that is 
required to support constant-time rank on the current bitvector. */
uint64_t rank_support::overhead() {
  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  return (sizeof(Rs_) + (ceil(N/S)) * ceil(sizeof(ceil(log2(N)))/8)
       + sizeof(Rb_) + (ceil(N/B)) * ceil(sizeof(ceil(log2(ceil(log2(N)))))/8))
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
  string bv_fname = fname + "_bv";
  sdsl::store_to_file(*b_, bv_fname);
  out << bv_fname << endl;

  uint64_t i;
  uint64_t Rs_size_ = ceil(N/S);
  for (i = 0; i < Rs_size_; i++) {
    if (i > 0) {
      out << " ";
    }
    out << Rs_[i];
  }
  out << endl;

  uint64_t Rb_size_ = ceil(N/B);
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
  sdsl::bit_vector b__;
  sdsl::load_vector_from_file(b__, line, 0);
  *b_ = b__;

  float N = b_->size();
  float S = floor(ceil(log2(N))*ceil(log2(N))/2);
  float B = floor(ceil(log2(N))/2);

  uint64_t Rs_size_ = ceil(N/S);
  uint64_t Rb_size_ = ceil(N/B);

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

