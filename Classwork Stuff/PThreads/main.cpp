// g++ main.cpp -Wall -O3 --std=c++17 -o out
// ./out

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <future>
#include <iomanip>
#include <utility>
#include <iterator>
#include <numeric>

bool isPrime(const unsigned int n);
unsigned int countPrime(const std::vector<unsigned int>& vec);

constexpr auto SIZE = 50000000;
constexpr auto MULT = 1000000;
constexpr auto low_bound = 1;
constexpr auto up_bound = 10000;

int main(void) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine dre(seed);
    std::uniform_int_distribution<unsigned int> di(low_bound,up_bound);

    std::vector<unsigned int> data(SIZE);
    std::generate(data.begin(), data.end(), [&dre, &di]{ return di(dre); });

    const auto startSingleThread = std::clock();

    unsigned int num_single{};
    for (const auto& elem : data) if (isPrime(elem)) ++num_single;
    std::cout << "single thread prime count: " << num_single << std::endl;

    const auto finishSingleThread = std::clock();

    std::cout << std::fixed << std::setprecision(2) << "single thread cpu time used: "
              << 1000 * (finishSingleThread - startSingleThread) / CLOCKS_PER_SEC << " ms" << std::endl;

    std::vector<std::vector<unsigned int>> subs(SIZE/MULT, std::vector<unsigned int> (MULT));
    for (size_t i = 0; i < subs.size(); ++i) {
        subs[i].assign(std::make_move_iterator(data.begin() + MULT * i),
                       std::make_move_iterator(data.begin() + MULT * i + MULT));
    }

    std::vector<std::future<unsigned int>> threads{};

    const auto startMultiThread = std::clock();
    for (size_t i = 0; i < SIZE / MULT; ++i) {
        threads.emplace_back((std::async(std::launch::async, countPrime, std::move(subs[i]))));
    }

    unsigned int num_multi{};
    for (auto& elem : threads) num_multi += elem.get();
    std::cout << "multi thread prime count: " << num_multi << "\n";
    const auto finishMultiThread = std::clock();

    std::cout << std::fixed << std::setprecision(2) << "multi thread cpu time used: "
              << 1000 * (finishMultiThread - startMultiThread) / CLOCKS_PER_SEC << " ms" << std::endl;
}

bool isPrime(const unsigned int n) {
    if (n == 1) return true;
    for (int i = 2; i * i <= n; ++i) { if (!(n % i)) return false; }
    return true;
}

unsigned int countPrime(const std::vector<unsigned int>& vec) {
    unsigned int num{};
    for (const auto& elem : vec) if(isPrime(elem)) ++num;
    return num;
}