#pragma once

#include "http_request.h"

#include <string_view>
#include <string>
#include <map>
#include <array>
using namespace std;

class StatsPiece {
public:
  template <typename Container> StatsPiece(const Container& known_keys, string_view default_key) :
    default_key(default_key) {
    for (string_view key : known_keys)
        stats[key] = 0;
    stats[default_key] = 0;
  }

  void Add(string_view key);

  const map<string_view, int>& GetStats() const;

private:
    const string_view default_key;
    map<string_view, int> stats;
};

class Stats {
public:
  Stats() {}

  void AddMethod(string_view method);

  void AddUri(string_view uri);

  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;

private:
  inline static const array<string, 4> known_methods = {"GET", "POST", "DELETE", "PUT"};
  inline static const string default_method= "UNKNOWN";

  inline static const array<string, 5> known_uris = {"/", "/product", "/basket", "/help", "/order"};
  inline static const string default_uri = "unknown";

  StatsPiece uri_stats = {known_uris, default_uri};
  StatsPiece method_stats = {known_methods, default_method};
};

HttpRequest ParseRequest(string_view str);