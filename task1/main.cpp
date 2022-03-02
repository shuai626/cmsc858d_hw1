#include "rank_support.h"
using namespace std;

int main () {
    string s = "10010111010010100000000000000000";
    // string s = "10010111111101";
    reverse(s.begin(), s.end());

    // Flip bits since bitset accesses values from lowest to greatest bit
    std::bitset<N> bs(s);

    cout << "COUNT" << bs.count() << endl;

    rank_support r(&bs);
    int i;
    for (i = 1; i <= N; i++) 
    {
      cout << r.rank1(i) << endl;
    }

    cout <<  r.overhead() << endl;

    return 0;
}