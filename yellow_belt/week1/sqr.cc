#include <iostream>
#include <utility> 
#include <map> 
#include <vector>
#include <exception>
using namespace std;

template <typename T> T Sqrt(const T& t);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename T> vector<T> Sqr(const vector<T>& v);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);

template <typename T> T Sqr(const T& t) {
    return t * t;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}
template <typename T>
vector<T> Sqr(const vector<T>& v)  {
    vector<T> res;
    for (const T& t : v) {
        res.push_back(Sqr(t));
    }
    return res;
}
template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
    map<Key, Value> res;
    for (const auto& [key, value] : m) {
        res[key] = Sqr(value);
    }
    return res;
}