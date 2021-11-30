#include "stats.h"

void StatsPiece::Add(string_view key) {
    if (stats.find(key) != stats.end())
        stats[key]++;
    else 
        stats[default_key]++;
}

const map<string_view, int>& StatsPiece::GetStats() const {
    return stats;
}

void Stats::AddMethod(string_view method) {
  method_stats.Add(method);
}

void Stats::AddUri(string_view uri) {
  uri_stats.Add(uri);
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return method_stats.GetStats();
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uri_stats.GetStats();
}

string_view ParseToken(string_view& str) {
    size_t token_begin = str.find_first_not_of(' ');
    size_t token_end = str.find(' ', token_begin);
    auto token = str.substr(token_begin, token_end - token_begin);
    str.remove_prefix(token_end);
    return token;
}

HttpRequest ParseRequest(string_view str) {
    return HttpRequest{ParseToken(str), ParseToken(str), ParseToken(str)};
};