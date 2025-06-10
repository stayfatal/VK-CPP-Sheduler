#include "iostream"
#include "../../pkg/sheduler/sheduler.h"

int main(){
    Scheduler scheduler;
    scheduler.Start();

    scheduler.Add([]() {std::cout << "Hello world\n";},std::time(nullptr)+1);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    scheduler.Stop();
    return 0;
}