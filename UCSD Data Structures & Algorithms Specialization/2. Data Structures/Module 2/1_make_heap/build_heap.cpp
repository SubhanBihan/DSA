#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
    vector<int> data_;
    vector<pair<int, int>> swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (auto &sw : swaps_) {
            cout << sw.first << " " << sw.second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void SiftDown(int i) {
        int minIndex = i;
        int left = 2 * i + 1;
        if (left < (int)data_.size() && data_[left] < data_[minIndex])
            minIndex = left;

        int right = 2 * i + 2;
        if (right < (int)data_.size() && data_[right] < data_[minIndex])
            minIndex = right;

        if (i != minIndex) {
            swap(data_[i], data_[minIndex]);
            swaps_.push_back(make_pair(i, minIndex));
            SiftDown(minIndex);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        // Start from the last internal node and sift down to build heap in O(n)
        for (int i = (int)data_.size() / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
