#include <tuple>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

auto GetRegionKey(
    const Region& region) {
    return tie(region.population, region.std_name,
                      region.parent_std_name, region.names);
}

bool operator<(const Region& lhs, const Region& rhs) {
    return GetRegionKey(lhs) < GetRegionKey(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
    map<Region, unsigned> region_count;
    unsigned result = 0;
    for (const Region& region : regions) {
      region_count[region]++;
      result = max(result, region_count[region]);
    }
    return result;
}