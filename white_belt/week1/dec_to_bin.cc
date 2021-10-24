#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

string dec_to_bin(int a) {
    stringstream s;
    vector<int> bins;
    while (a != 0) {
        bins.push_back(a % 2);
        a /= 2;
    }

    for (int i = bins.size() - 1; i >= 0; i--)
        s << bins[i];

    return s.str();
}

int main() {
    int a;

    cin >> a;

    assert(a > 0);

    cout << dec_to_bin(a) << endl;
    return 0;
}
