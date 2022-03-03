#include "rank_support.h"
using namespace std;

int main () {
    // string s = "10010111010010100000000000000000";
    string s = "1001011101001010";
    reverse(s.begin(), s.end());

    // Flip bits since bitset accesses values from lowest to greatest bit
    std::bitset<N> bs(s);

    cout << "Bitvector: " << bs.to_string() << endl;

    rank_support r(&bs);
    int i;
    for (i = 1; i <= N; i++) 
    {
      cout << "Rank " << i << ": " << r.rank1(i) << endl;
    }

    cout << "Overhead (in bits): " << r.overhead() << endl;

    string file = "test";
    r.save(file);

    return 0;
}