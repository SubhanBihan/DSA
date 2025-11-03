#include <algorithm>
#include <iostream>
// #include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

double dist(const Point &a, const Point &b) {
    return hypot(a.x - b.x, a.y - b.y);
}

bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool compareY(const Point &a, const Point &b) {
    return a.y < b.y;
}

double closestPairRecursive(vector<Point> &px, vector<Point> &py) {
    int n = px.size();
    if (n <= 3) {
        double minD = 1e20;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                minD = min(minD, dist(px[i], px[j]));
        return minD;
    }

    int mid = n / 2;
    Point midPoint = px[mid];

    vector<Point> pyl, pyr;
    for (auto &p : py) {
        if (p.x <= midPoint.x)
            pyl.push_back(p);
        else
            pyr.push_back(p);
    }

    vector<Point> pxl(px.begin(), px.begin() + mid);
    vector<Point> pxr(px.begin() + mid, px.end());

    double d1 = closestPairRecursive(pxl, pyl);
    double d2 = closestPairRecursive(pxr, pyr);
    double d = min(d1, d2);

    vector<Point> strip;
    for (auto &p : py)
        if (fabs(p.x - midPoint.x) < d)
            strip.push_back(p);

    for (int i = 0; i < strip.size(); ++i)
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j)
            d = min(d, dist(strip[i], strip[j]));

    return d;
}

double closestPair(vector<Point> &points) {
    vector<Point> px = points, py = points;
    sort(px.begin(), px.end(), compareX);
    sort(py.begin(), py.end(), compareY);
    return closestPairRecursive(px, py);
}

int main() {
  size_t n;
  std::cin >> n;
  vector<Point> points(n);

  for (auto &point : points) {
    std::cin >> point.x >> point.y;
  }

  std::cout << std::fixed;
  std::cout << std::setprecision(9) << closestPair(points) << "\n";
}
