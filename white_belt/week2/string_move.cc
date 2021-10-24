void MoveStrings(vector<string>& source, vector<string>& dest) {
    for (string word : source)
        dest.push_back(word);
    source.clear();
}