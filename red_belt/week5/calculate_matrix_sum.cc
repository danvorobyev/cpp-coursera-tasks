#include "test_runner.h"
#include <vector>
#include <future>
using namespace std;


template<typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator f, Iterator l)
  : first(f), last(l) {}

  Iterator begin() const { return first; }

  Iterator end() const { return last; }

  size_t size() const {
    return distance(first, last);
  }

private:
  Iterator first;
  Iterator last;
};

template <typename Iterator>
class Paginator {
public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (auto page_start_it = begin; page_start_it != end;) {
      size_t current_page_size =  min(page_size, static_cast<size_t>(distance(page_start_it, end)));
      auto page_end_it = next(page_start_it, current_page_size);
      page_ranges.emplace_back(page_start_it, page_end_it);
      page_start_it = page_end_it;
    }
  }

  size_t size() const {
    return page_ranges.size();
  }

  typename vector<IteratorRange<Iterator>>::iterator begin() {
    return page_ranges.begin();
  }

  typename vector<IteratorRange<Iterator>>::iterator end() {
    return page_ranges.end();
  }

private:
  vector<IteratorRange<Iterator>> page_ranges;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator{c.begin(), c.end(), page_size};
}

template <typename Container>
int64_t SumSingleThread(const Container& c) {
    int64_t sum = 0;
    for (const auto& row : c) {
        for (const auto e : row) {
            sum += e;
        }
    }
    return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    auto paginator = Paginate(matrix, 2000);
    vector<future<int64_t>> futures;
    for (auto page : paginator) {
        futures.push_back(async([=](){ return SumSingleThread(page); }));
    }
    int64_t total = 0;
    for (auto& f : futures) {
        total += f.get();
    }
    return total;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
