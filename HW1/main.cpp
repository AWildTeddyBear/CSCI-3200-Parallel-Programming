/*
    ==============================================
    Code written by AWildTeddyBear
    https://github.com/AWildTeddyBear
    Code written for educational purposes only
    For repo/class: CSCI-3200 Parallel Programming
    ==============================================

    =========================================
    Compiled via command line:
    g++ main.cpp --std=c++17 -O3 -Wall -o out
    ./out
    =========================================
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

int main(void) {
    // Start timer for exeuction time
    std::chrono::high_resolution_clock::time_point currentBefore = std::chrono::high_resolution_clock::now();

    // Make array with our fruits and define a printing function. Then output the unsorted array
    std::vector<std::string> fruits = {"banana", "apple", "orange", "strawberry", "pineapple", "watermelon", "grape", "raspberry"};
    auto printFruits = [](std::string& input) { std::cout << input << " "; };
    std::cout << "Unsorted array: "; std::for_each(fruits.begin(), fruits.end(), printFruits); std::cout << std::endl;

    // Sort our array
    std::sort(fruits.begin(), fruits.end());

    // Print sorted array
    std::cout << "Sorted array: "; std::for_each(fruits.begin(), fruits.end(), printFruits); std::cout << std::endl;

    // Finish timer for execution time
    std::chrono::high_resolution_clock::time_point currentAfter = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentAfter - currentBefore).count();

    // Output execution time
    std::cout << std::endl << "Total exeuction time: " << duration << " microseconds." << std::endl;

    return 0;
}