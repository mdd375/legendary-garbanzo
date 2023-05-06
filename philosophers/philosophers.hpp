#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <syncstream>
#include <thread>
#include <time.h>
#include <vector>

inline auto now();

std::string color(int color_number);

inline void log(int id, std::string action);

void philosopher(int id, int lifetime);

bool solve(int number);
