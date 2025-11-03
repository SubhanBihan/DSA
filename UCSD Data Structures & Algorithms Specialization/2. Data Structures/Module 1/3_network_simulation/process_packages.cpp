#include <iostream>
#include <vector>
#include <queue>

struct Packet {
    int arrival_time;
    int processing_time;
};

std::vector<int> process_packets(int buffer_size, const std::vector<Packet>& packets) {
    std::vector<int> results;
    std::queue<int> finish_times; // Times when packets finish processing
    
    for (const Packet& packet : packets) {
        int current_time = packet.arrival_time;
        
        // Remove packets that have finished processing
        while (!finish_times.empty() && finish_times.front() <= current_time) {
            finish_times.pop();
        }
        
        // Check if buffer has space
        if (finish_times.size() < buffer_size) {
            // Add packet to buffer
            int start_time;
            if (finish_times.empty()) {
                // Processor is free, start immediately
                start_time = current_time;
            } else {
                // Processor is busy, start after the last packet in queue
                start_time = finish_times.back();
            }
            
            int finish_time = start_time + packet.processing_time;
            finish_times.push(finish_time);
            results.push_back(start_time);
        } else {
            // Buffer is full, drop the packet
            results.push_back(-1);
        }
    }
    
    return results;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int buffer_size, n;
    std::cin >> buffer_size >> n;
    
    std::vector<Packet> packets(n);
    for (int i = 0; i < n; i++) {
        std::cin >> packets[i].arrival_time >> packets[i].processing_time;
    }
    
    std::vector<int> results = process_packets(buffer_size, packets);
    
    for (int result : results) {
        std::cout << result << "\n";
    }
    
    return 0;
}