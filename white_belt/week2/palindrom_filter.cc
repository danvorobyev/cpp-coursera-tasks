bool IsPalindrom(string s) {
    for (int i = 0; i < s.length() / 2; i++) {
        if (s[i] != s[s.length() - i - 1])
            return false;
    }
    return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength) {
    vector<string> filtered_words;
    for (string word : words)
        if (word.length() >= minLength && IsPalindrom(word))
            filtered_words.push_back(word);
    return filtered_words;
}