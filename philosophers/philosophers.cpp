#include <cstdlib>
#include <vector>
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

constexpr auto SLEEP_TIME = std::chrono::seconds(1);

std::vector<std::mutex> forks;

inline auto now() {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  auto time_info = localtime(&time);
  return std::put_time(time_info, "%T");
}

bool is_support_color = false;

std::string color(int color_number) {
  if (!is_support_color) {
    return "";
  }
  switch (color_number) {
  case -1:
    return "\033[0m"; // Сброс цвета
  case 0:
    return "\033[30m"; // Черный
  case 1:
    return "\033[31m"; // Красный
  case 2:
    return "\033[32m"; // Зеленый
  case 3:
    return "\033[33m"; // Желтый
  case 4:
    return "\033[34m"; // Синий
  case 5:
    return "\033[35m"; // Пурпурный
  case 6:
    return "\033[36m"; // Голубой
  case 7:
    return "\033[37m"; // Белый
  default:
    return ""; // Если номер цвета некорректный, возвращаем пустую строку
  }
}

inline void log(int id, std::string action) {
  auto sync_cout = std::osyncstream(std::cout);
  sync_cout << color(id) << now() << " Philosopher " << id << " starts "
            << action << color(-1) << std::endl;
}

void philosopher(int id, int number, int lifetime) {
  int lfork = id;
  int rfork = (id + 1) % number;
  std::string message;

  for (int i = 0; i < lifetime; i++) {
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
  log(id, "washed up and got a job");
}

bool solve(int number) {
  if (std::getenv("TERM") != nullptr) {
    is_support_color = true;
  }
  std::srand(std::time(nullptr));
  auto philosophers = std::vector<std::thread>(number);
  forks = std::vector<std::mutex>(number);
  for (int i = 0; i < number; i++)
    philosophers[i] = std::thread(philosopher, i, number, std::rand() % 5);

  for (int i = 0; i < number; i++)
    philosophers[i].join();
  return true;
}
