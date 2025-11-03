#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;

struct Segment {
  int start, end;
};

void fast_count_segments(vector<Segment> &segments, std::map<int, unsigned> &unique_points) {
  std::sort(segments.begin(), segments.end(), [](const Segment &x,  const Segment &y){ return (x.start < y.start) || (x.start == y.start && x.end < y.end); });

  auto start_it = segments.begin();
  
  for (auto &[point, count] : unique_points) {
    // for (auto &segment : segments) {
    //   if (segment.start > point) break;

    //   if (segment.end >= point) count++;
    // }

    for (auto it = start_it; it != segments.end(); it++) {
      if (it->start > point) break;

      // WRONG
      if (it->end < point) start_it++;
      else count++;

    }
  }
}

// vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
//   vector<int> cnt(points.size());
//   for (size_t i = 0; i < points.size(); i++) {
//     for (size_t j = 0; j < starts.size(); j++) {
//       cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
//     }
//   }
//   return cnt;
// }

int main() {
  int n, m;
  std::cin >> n >> m;

  vector<Segment> segments(n);
  for (auto &segment : segments) {
    std::cin >> segment.start >> segment.end;
  }

  vector<int> points(m);
  std::map<int, unsigned> unique_points;
  for (auto &point : points) {
    std::cin >> point;
    unique_points[point] = 0;
  }

  fast_count_segments(segments, unique_points);
  
  //use fast_count_segments
  for (const auto &point : points) {
    std::cout << unique_points[point] << " ";
  }
}
