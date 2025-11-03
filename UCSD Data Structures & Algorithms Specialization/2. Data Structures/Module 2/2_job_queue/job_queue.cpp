#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::make_pair;

struct Worker {
    long long next_free_time;
    int id;

    Worker(long long t, int i) : next_free_time(t), id(i) {}

    bool operator>(const Worker &other) const {
        if (next_free_time == other.next_free_time)
            return id > other.id; // smaller ID first if tie
        return next_free_time > other.next_free_time; // smaller time first
    }
};

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());

        // Min-heap based on (next_free_time, worker_id)
        priority_queue<Worker, vector<Worker>, std::greater<Worker>> pq;

        // Initialize all workers as free at time 0
        for (int i = 0; i < num_workers_; ++i) {
            pq.emplace(0, i);
        }

        for (int i = 0; i < jobs_.size(); ++i) {
            Worker w = pq.top();
            pq.pop();

            assigned_workers_[i] = w.id;
            start_times_[i] = w.next_free_time;

            // Update worker's next free time and push back
            w.next_free_time += jobs_[i];
            pq.push(w);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
