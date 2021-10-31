#include <map>
#include <stdexcept>

template <typename Key, typename Value> 
Value& GetRefStrict(map<Key, Value>& m, const Key& key) {
    if (m.find(key) == m.end())
        throw runtime_error("Key not found");
    return m.at(key);
}