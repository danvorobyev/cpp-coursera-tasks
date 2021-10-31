#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;


int main() {
    int N, P;
    cin >> N >> P;

    uint64_t total_mass = 0;

    for(int i = 0; i < N; i++) {
        int64_t X, Y, Z;

        cin >> X >> Y >> Z;

        total_mass += X * Y * Z;
    }

    total_mass *= P;

    cout << total_mass << endl;
    return 0;      
}
