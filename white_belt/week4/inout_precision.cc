#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream input("input.txt");
    double num;
    cout << fixed << setprecision(3);
    if (input.is_open()) {
        while(input >> num)
            cout << num << endl; 
    }
    return 0;
}
