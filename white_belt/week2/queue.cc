#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<bool> is_worried;

int get_op_num() {
    int num;
    cin >> num;
    return num;
}

void worry() {
    int i = get_op_num();
    is_worried[i] = true;
}

void quiet() {
    int i = get_op_num();
    is_worried[i] = false;
}

void come() {
    int k = get_op_num();
    is_worried.resize(is_worried.size() + k, false);
}

void worry_count() {
    cout << count(begin(is_worried), end(is_worried), true) << endl;
}

int main() {
    int n;
    cin >> n;
    string op;
    
    for (int i = 0; i < n; i++) {
        cin >> op;
        if (op == "WORRY")
            worry();
        else if (op == "QUIET") 
            quiet();
        else if (op == "COME")
            come();
        else
            worry_count();
    }
    return 0;
}