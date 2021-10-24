vector<int> Reversed(const vector<int>& v) {
    vector<int> reversed_v;
    for (int i = v.size() - 1; i >= 0; i--)
        reversed_v.push_back(v[i]);
    return reversed_v;
}