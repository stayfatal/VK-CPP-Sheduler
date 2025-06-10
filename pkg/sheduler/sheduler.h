#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

class Scheduler {
public:
    void Add(std::function<void()> task, std::time_t timestamp);
    
    void Start();
    
    void Stop();

private:
    void Run();  
    
    struct Task {
        std::function<void()> func;
        std::time_t time;
        
        bool operator < (const Task& other) const {
            return time > other.time;  
        }
    };

    std::priority_queue<Task> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
};