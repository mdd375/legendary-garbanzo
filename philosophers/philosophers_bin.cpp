#include <iostream>
#include <string>
#include "philosophers/philosophers.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Введите число философов" << std::endl;
        return 0;
    }

    int num = std::stoi(argv[1]);
    if (num < 1) {
        std::cout << "Ура! Никаких философов!" << std::endl;
        return 0;
    }
    solve(num);
    return 0;
}