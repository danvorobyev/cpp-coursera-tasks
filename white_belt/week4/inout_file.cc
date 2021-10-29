#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line;
    if (input.is_open() && output.is_open()) {
        while(getline(input, line)) {
            output << line << endl; 
        }
    }
    return 0;
}
