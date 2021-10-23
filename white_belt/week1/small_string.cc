#include <iostream>
#include <string>
using namespace std;

const string& choose_min_string(const string& s1, const string& s2) {
    if (s1 < s2) 
        return s1;
    return s2;
}

int main() {
    string s1, s2, s3;

    cin >> s1 >> s2 >> s3;
    
    cout << choose_min_string(choose_min_string(s1, s2), s3) << endl;   

    return 0;
}
    
