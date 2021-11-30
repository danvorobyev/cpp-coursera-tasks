#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <list>
#include <utility>
#include <vector>

using namespace std;



template <typename T>
class PriorityCollection {
public:
  using Id = int;
/* тип, используемый для идентификаторов */;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
    Id id = data.size();
    data.push_back({0, move(object)});
    sorted_objects.insert({0, id});
    return id;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    for (auto it = range_begin; it != range_end; ++it) {
      *ids_begin++ = Add(move(*it));
    }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
    return id < data.size() && id >= 0 && data[id].priority != -1;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
    return data[id].value;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
    const auto prev_priority = data[id].priority;
    const auto new_priority = ++data[id].priority;
    sorted_objects.erase({prev_priority, id});
    sorted_objects.insert({new_priority, id});
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
    auto max_obj_it = prev(sorted_objects.end());
    const auto& item = data[max_obj_it->second];
    return {item.value, item.priority};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
    auto max_obj_it = prev(sorted_objects.end());
    auto& item = data[max_obj_it->second];
    sorted_objects.erase(max_obj_it);
    const auto priority = item.priority;
    item.priority = -1;
    return {move(item.value), priority};
  }

private:
  struct ObjectData {
    int priority;
    T value;
  };

  vector<ObjectData> data;
  set<pair<int, Id>> sorted_objects;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
