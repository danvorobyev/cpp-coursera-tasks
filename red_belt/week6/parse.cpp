#include "parse.h"
#include <iostream>
#include <algorithm>

using namespace std;

string_view Strip(string_view s) {
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && isspace(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

vector<string_view> SplitBy(string_view s, char sep) {
    vector<string_view> result;
    while (!s.empty()) {
        size_t pos = s.find(sep);
        result.push_back(s.substr(0, pos));
        s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
    }
    return result;
}

string_view ReadToken(string_view& line) {
    size_t token_begin = line.find_first_not_of(' ');
    size_t token_end = line.find(' ', token_begin);

    if (token_begin == line.npos) 
      return string_view();

    auto token = line.substr(token_begin, token_end - token_begin);
    line.remove_prefix(min(token_end, line.size()));
    return token;
}

vector<string_view> SplitIntoWords(string_view line) {
    vector<string_view> result;

    for(auto token = ReadToken(line); !token.empty(); token = ReadToken(line)) {
      result.push_back(token);
    }
    return result;
}