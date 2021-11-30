#pragma once

#include <string_view>
#include <sstream>
using namespace std;

struct HttpRequest {
  HttpRequest(string_view method_, string_view uri_, string_view protocol_) {
    method = method_;
    uri = uri_;
    protocol = protocol_;
  }
  string_view method, uri, protocol;
};