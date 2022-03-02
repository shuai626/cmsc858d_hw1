#include "rank_support.h"

rank_support::rank_support(bitset<N>* b)
{
  b_ = b;
  N_ = b_->size();
  S_ = floor(ceil(log2(N_))*ceil(log2(N_))/2);
  B_ = floor(ceil(log2(N_))/2);

  cout << N_ << " " << S_ << " " << B_ << endl;

  uint64_t Rs_size_ = ceil(N_/S_) - 1;
  uint64_t Rb_size_ = ceil(N_/B_) - 2;

  cout << N_/S_ << " " << N_/B_ << endl;

  cout << Rs_size_ << " " << Rb_size_ << endl;

  // Initialize the superblock and block arrays
  // The first index always stores 0, optimize by dropping it
  Rs_ = (uint64_t *) calloc(Rs_size_, sizeof(ceil(log2(N_))));
  Rb_ = (uint64_t *) calloc(Rb_size_, sizeof(ceil(log2(ceil(log2(N_))))));

  // Populate the superblock array
  uint64_t i, j;
  for (i = 0; i < Rs_size_; i++)
  {
    if (i > 0) 
    {
      Rs_[i] += Rs_[i-1];
    }
    for (j = S_*i; j < S_*(i+1); j++)
    {
      if ((*b_)[j]) 
      {
        Rs_[i] += 1;
      }
    }
    cout << "RS "<< Rs_[i] << endl;
  }
  
  // Populate the block array
  int r = floor(S_/B_ - 1);
  for (i = 0; i < Rb_size_; i++)
  {
    int Z = floor((i)/r)*S_+((i)%r)*B_;
    if (i % r != 0)
    {
      Rb_[i] += Rb_[i-1];
    }
    for (j = Z; j < Z+B_; j++)
    {
      if ((*b_)[j]) 
      {
        Rb_[i] += 1;
      }
    }
    cout << "RB "<< Rb_[i] << endl;
  }
}

/* Returns the number of 1s in the underlying bit-vector 
up to position i (inclusive). */
uint64_t rank_support::rank1(uint64_t i)
{
  if (i == N)
  {
    return b_->count();
  }

  uint64_t s = floor((i-1)/S_);
  uint64_t b = floor((i-1)/B_);

  int rank = 0;

  if (s > 0)
  {
    rank += Rs_[s-1];
  }

  int r = floor(S_/B_);
  if (b % r != 0)
  {
    int j = floor((b)/r)*(r-1) + b%r - 1;
    rank += Rb_[j];
  }

  // Use popcount for the Rp block. Extract block by building mask
  bitset<N> Rp(*b_);
  Rp >>= b*B_;
  Rp <<= (N - i + b*B_);
  Rp >>= (N - i + b*B_);

  rank += Rp.count();
  return rank;
}

/* Returns the size of the rank data structure (in bits) that is 
required to support constant-time rank on the current bitvector. */
uint64_t rank_support::overhead()
{
  return (sizeof(Rs_) + (ceil(N_/S_) - 1) * sizeof(ceil(log2(N_)))
       + sizeof(Rb_) + (ceil(N_/B_) - 2) * sizeof(ceil(log2(ceil(log2(N_)))))
       + 3 * sizeof(float)) * 8 + b_->size();
}

/* Saves the rank data structure for this bit vector to the file fname 
(your bit vector should also have a save() function). */
void rank_support::save(string& fname)
{
  // TODO:
  // store b_->to_string()
  // store N_ S_ and B_ on same line
  // store Rs_ (iterate through all values). May need to store size explicitly
  // store Rb_ (iterate through all values) May need to store size explicitly
  return;
}

/* Loads the rank data structure for this bit vector from the file fname 
(your bit vector should also have a load() function). */
void rank_support::load(string& fname)
{
  // TODO:
  // read b_->to_string() and construct new bitset with bit string
  // convert N_ S_ and B_ into floats using scanf
  // construct Rs_ and Rb_ using size, then iterate and populate with values
  return;
}

rank_support::~rank_support()
{
  free(Rs_);
  free(Rb_);
}

