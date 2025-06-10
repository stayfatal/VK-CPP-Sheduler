#include "sheduler.h"

void Scheduler::Add(std::function<void()> task, std::time_t timestamp) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.push({task, timestamp});
    cv_.notify_one();  // будим наш шедулер 
}

void Scheduler::Start() {
    std::thread(&Scheduler::Run, this).detach();  
}

void Scheduler::Run() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex_);

        // ждет пока его разбудят
        cv_.wait(lock, [this]() {
            return !tasks_.empty() || stop_;
        }); 

        if (stop_) break;

        auto next_task = tasks_.top();
        auto now = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now()
        );

        if (now >= next_task.time) {
            next_task.func();
            tasks_.pop();
        } else {
            // ждет пока придет время таски
            cv_.wait_until(lock, 
                std::chrono::system_clock::from_time_t(next_task.time)
            );
        }
    }
}

void Scheduler::Stop() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    // будим все шедулеры чтобы они остановились
    cv_.notify_all();  
}