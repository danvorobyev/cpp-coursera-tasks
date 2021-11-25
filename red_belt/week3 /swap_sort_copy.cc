#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
void Swap(T* first, T* second) {
  T tmp = *first;
  *first = *second;
  *second = tmp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
  sort(pointers.begin(), pointers.end(),
    [](T* lhs, T* rhs) { return *lhs < *rhs; });
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
  auto source_begin = source;
  auto source_end = source + count;
  auto dest_begin = destination;

  for (size_t i = 0; i < count; i++) {
    T* source_curr = source_end - i - 1;
    T* dest_curr = dest_begin + i;

    // Не пересекающаяся часть диапазонов — смело "копируем" элемент на
    // требуемую позицию
    if (dest_curr < source_begin || dest_curr >= source_end) {
      *dest_curr = *source_curr;
    // Пересекающаяся часть диапазонов — разворачиваем её до/относительно центра
    } else if (dest_curr < source_curr) {
      Swap(source_curr, dest_curr);
    }
  }
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // Области памяти могут перекрываться
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
      int nums[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    ReversedCopy(nums, 6, nums + 3);
    for (size_t i = 0; i < 10; ++i)
        cout << nums[i] << ' ';
  return 0;
}
