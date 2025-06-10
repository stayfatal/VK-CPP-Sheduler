cmake_minimum_required(VERSION 3.10)  
project(VK-CPP-Scheduler)  

set(CMAKE_CXX_STANDARD 17)  
set(CMAKE_CXX_FLAGS "-Wall -Wextra")  

add_library(scheduler STATIC  
    pkg/sheduler/sheduler.cpp
)  

add_executable(vk-scheduler  
    cmd/app/main.cpp  
)  

target_link_libraries(vk-scheduler PRIVATE scheduler)  