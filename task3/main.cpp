#include "sparse_array.h"
using namespace std;

int main () {
    sparse_array s;

    s.create(SIZE);

    string s1 = "foo";
    string s2 = "bar";
    string s3 = "baz";
    // s.append(s1,2);
    // s.append(s2,5);
    // s.append(s3,10);

    string e = "NONE";
    int i;

    for (i = 1; i <= s.num_elem() + 4; i++) {
      cout << "Get rank at " << i << ": " << s.get_at_rank(i, e) << "| Value: " << e << endl;
      e = "NONE";
    }

    for (i = 1; i <= s.size(); i++) {
      cout << "Get index at " << i << ": " << s.get_at_index(i, e) << "| Value: " << e << endl;
      e = "NONE";
    }

    string fname = "test";
    s.load(fname);

    for (i = 1; i <= s.num_elem() + 4; i++) {
      cout << "Get rank at " << i << ": " << s.get_at_rank(i, e) << "| Value: " << e << endl;
      e = "NONE";
    }

    for (i = 1; i <= s.size(); i++) {
      cout << "Get index at " << i << ": " << s.get_at_index(i, e) << "| Value: " << e << endl;
      e = "NONE";
    }

    return 0;
}