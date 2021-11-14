#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Deque {
public:
    Deque() {}

    size_t Size() const {
        return front.size() + back.size();
    }

    bool Empty() const {
        return front.empty() && back.empty();
    }

    T& operator[](size_t index) {
        return index < front.size() ? front[front.size() - index - 1] : back[index - front.size()];
    }

    const T& operator[](size_t index) const {
        return index < front.size() ? front[front.size() - index - 1] : back[index - front.size()];
    }

    T& At(size_t index) {
        check_index(index);
        return (*this)[index];
    }

    const T& At(size_t index) const {
        check_index(index);
        return (*this)[index];
    }

    T& Front() {
        return front.empty() ? back.front() : front.back();
    }

    const T& Front() const {
        return front.empty() ? back.front() : front.back();
    }

    T& Back() {
        return back.empty() ? front.front() : back.back();
    }

    const T& Back() const {
        return back.empty() ? front.front() : back.back();
    }

    void PushFront(const T& t) {
        front.push_back(t);
    }

    void PushBack(const T& t) {
        back.push_back(t);
    }


private:
    vector<T> front;
    vector<T> back;

    void check_index(size_t index) const {
        if (index >= Size())
            throw out_of_range("");
    }
};