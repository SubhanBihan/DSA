#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

using std::vector;
using std::swap;

// Random number generator
std::mt19937 rng(std::random_device{}());

// Partition the vector into three parts: < pivot, == pivot, > pivot
void quicksort3(std::vector<int>& arr, int low, int high) {
    if (low >= high) return;

    // Random pivot index
    std::uniform_int_distribution<int> dist(low, high);
    int pivotIndex = dist(rng);
    int pivot = arr[pivotIndex];
    std::swap(arr[low], arr[pivotIndex]);  // Move pivot to start

    int lt = low;        // arr[low..lt-1] < pivot
    int gt = high;       // arr[gt+1..high] > pivot
    int i = low + 1;     // arr[lt..i-1] == pivot

    while (i <= gt) {
        if (arr[i] < pivot) {
            std::swap(arr[i], arr[lt]);
            ++lt;
            ++i;
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[gt]);
            --gt;
        } else {
            ++i;
        }
    }

    // Recurse on < and > parts
    quicksort3(arr, low, lt - 1);
    quicksort3(arr, gt + 1, high);
}

// Entry function
void randomizedQuickSort(std::vector<int>& arr) {
    quicksort3(arr, 0, static_cast<int>(arr.size()) - 1);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomizedQuickSort(a);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
