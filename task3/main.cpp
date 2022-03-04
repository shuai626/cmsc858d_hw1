#include "sparse_array.h"
using namespace std;

int main () {
    // string str = "10010111010010100000000000000000";
    // string str = "1001011101001010";
    string str = "1111111111111111";
    reverse(str.begin(), str.end());

    // Flip bits since bitset accesses values from lowest to greatest bit
    std::bitset<SIZE> bs(str);

    cout << "Bitvector: " << bs.to_string() << endl;

    rank_support r(&bs);
    int i;
    for (i = 1; i <= SIZE; i++) {
      cout << "Rank " << i << ": " << r.rank1(i) << endl;
    }
    cout << "Overhead (in bits): " << r.overhead() << endl;

    select_support s(&r);

    for (i = 1; i <= r.rank1(SIZE); i++) {
      cout << "Select " << i << ": " << s.select1(i) << endl;
    }
    cout << "Overhead (in bits): " << s.overhead() << endl;

    

    return 0;
}