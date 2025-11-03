#include <iostream>
#include <vector>

using std::vector;

// Merge function that counts inversions
long long mergeAndCount(std::vector<int>& arr, int left, int mid, int right) {
    long long inv_count = 0;

    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Merge and count inversions
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            inv_count += (n1 - i);  // All remaining elements in L[] are > R[j]
        }
    }

    // Copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    return inv_count;
}

// Recursive merge sort with inversion counting
long long mergeSortAndCount(std::vector<int>& arr, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;

    long long inv_count = 0;
    inv_count += mergeSortAndCount(arr, left, mid);
    inv_count += mergeSortAndCount(arr, mid + 1, right);
    inv_count += mergeAndCount(arr, left, mid, right);

    return inv_count;
}

// Wrapper function
long long countInversions(std::vector<int>& arr) {
    return mergeSortAndCount(arr, 0, static_cast<int>(arr.size()) - 1);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  // vector<int> b(a.size());
  std::cout << countInversions(a) << '\n';
}
