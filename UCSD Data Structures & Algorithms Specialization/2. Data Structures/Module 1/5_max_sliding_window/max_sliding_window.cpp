#include <iostream>
#include <vector>
#include <deque>

std::vector<int> sliding_window_maximum(const std::vector<int>& arr, int m) {
    int n = arr.size();
    std::vector<int> result;
    std::deque<int> dq; // Store indices, not values
    
    for (int i = 0; i < n; i++) {
        // Remove indices that are out of current window
        while (!dq.empty() && dq.front() <= i - m) {
            dq.pop_front();
        }
        
        // Remove indices whose corresponding values are smaller than current element
        // (they can never be maximum while current element is in window)
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        // Add current element index
        dq.push_back(i);
        
        // If we have processed at least m elements, record the maximum
        if (i >= m - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    int m;
    std::cin >> m;
    
    std::vector<int> maximums = sliding_window_maximum(arr, m);
    
    for (int max_val : maximums) {
        std::cout << max_val << " ";
    }
    std::cout << "\n";
    
    return 0;
}