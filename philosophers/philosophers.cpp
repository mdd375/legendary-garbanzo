#define _CRT_SECURE_NO_WARNINGS

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <syncstream>
#include <thread>
#include <time.h>

constexpr int N = 5;
constexpr auto SLEEP_TIME = std::chrono::seconds(1);

std::mutex forks[N];

inline auto now() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto time_info = localtime(&time);
    return std::put_time(time_info, "%T");
}

inline void log(int id, std::string action) {
    auto sync_cout = std::osyncstream(std::cout);
    sync_cout << now() << " Philosopher " << id << " starts " << action << std::endl;
}

void philosopher(int id) {
    int lfork = id;
    int rfork = (id + 1) % N;
    std::string message;

    while (true) {
        bool llocked = forks[lfork].try_lock();
        if (!llocked) {
            log(id, "thinking");
            std::this_thread::sleep_for(SLEEP_TIME);
            continue;
        }
        bool locked = forks[rfork].try_lock();
        if (!locked) {
            forks[lfork].unlock();
            log(id, "thinking");
            std::this_thread::sleep_for(SLEEP_TIME);
            continue;
        }
        log(id, "eating");
        std::this_thread::sleep_for(SLEEP_TIME);
        forks[lfork].unlock();
        forks[rfork].unlock();
    }
}

int main() {
    std::thread philosophers[N];
    for (int i = 0; i < N; i++)
        philosophers[i] = std::thread(philosopher, i);

    for (int i = 0; i < N; i++)
        philosophers[i].join();

    return 0;
}
