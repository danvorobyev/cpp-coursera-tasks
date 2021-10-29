#include <sstream>
#include <exception>

void EnsureEqual(const string& left, const string& right) {
    if (left != right) {
        stringstream error;
        error << left << " != " << right;
        throw runtime_error(error.str());
    }
}