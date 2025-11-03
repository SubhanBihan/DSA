#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  std::sort(segments.begin(), segments.end(), [](const Segment &x,  const Segment &y){ return x.start < y.start; });
  int current_point = segments[0].end;
  for (auto &segment : segments) {
    if (segment.start > current_point) {    // Need to place one more point
      points.push_back(current_point);
      current_point = segment.end;
    }
    else current_point = std::min(current_point, segment.end);    // No need to add a point, just reposition current point to as far right as possible (intersection allows)
  }
  points.push_back(current_point);
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
