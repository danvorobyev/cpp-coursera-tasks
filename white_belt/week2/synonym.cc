#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

map<string, set<string> > synonyms;

void add(const string& word1, const string& word2) {
    synonyms[word1].insert(word2);
    synonyms[word2].insert(word1);
}

void count(const string& word) {
    cout << synonyms[word].size() << endl;
}

void check(const string& word1, const string& word2) {
    if (synonyms[word1].count(word2) == 0)
        cout << "NO" << endl;
    else 
        cout << "YES" << endl;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string op;
        cin >> op;
        if (op == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;
            add(word1, word2);
        }
        else if (op == "COUNT") {
            string word;
            cin >> word;
            count(word);
        } else {
            string word1, word2;
            cin >> word1 >> word2;
            check(word1, word2);
        }
    }
    return 0;
}