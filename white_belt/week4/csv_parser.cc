#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    ifstream input("input.txt");
    int N, M;
    cout << fixed;
    if (input.is_open()) {
        input >> N >> M;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int num;
                input >> num;
                cout << setw(10) << num;
                if (j != M-1) {
                    input.ignore(1);
                    cout << " ";
                }
            }
            if (i != N-1)
                cout << endl;
        }
    }    
    return 0;
}
