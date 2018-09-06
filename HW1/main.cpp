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
#include <ctime>
#include <chrono>

#define RST "\x1B[0m" //Reset (No colour)
#define KRED "\x1B[31m" //Red
#define KGRN "\x1B[32m" //Green
#define KYEL "\x1B[33m" //Yellow
#define KBLU "\x1B[34m" //Blue
#define KMAG "\x1B[35m" //Magenta
#define KCYN "\x1B[36m" //Cyan
#define KWHT "\x1B[37m" //White
#define KUNDL "\x1B[4m" //Underlined
#define KBOLD "\x1B[1m" //Bold
#define FRED(x) KRED x RST //Red + Reset
#define FGRN(x) KGRN x RST //Green + Reset
#define FYEL(x) KYEL x RST //Yellow + Reset
#define FBLU(x) KBLU x RST //Blue + Reset
#define FMAG(x) KMAG x RST //Magenta + Reset
#define FCYN(x) KCYN x RST //Cyan + Reset
#define FWHT(x) KWHT x RST //White + Reset
#define BOLD(x) "\x1B[1m" x RST //Bold + Reset
#define UNDL(x) "\x1B[4m" x RST //Underlined + Reset

// Function prototypes
void mergeSort(int arr[], int leftIndex, int rightIndex), merge(int arr[], int leftIndex, int middle, int rightIndex);

int main(void){
    // Seed our random number generator
    srand((unsigned) time(0));

    // Randomly generate an array 1000 elements long for sorting
    int randomArr[] = {0, 3, 41, 20, 24, 5, 2, 49, 28, 49, 23, 23, 4, 69, 43, 34}, arrSize = (sizeof(randomArr) / sizeof(randomArr[0])) - 1;
    //for (int i = 0; i < 1000; randomArr[i++] = (rand() % 1000) + 1);

    // Print our inital array to use it as a visual reference
    std::cout << KBOLD << KGRN << "Inital Array: " << RST << KMAG << std::endl;
    for (int i = 0; i < arrSize; i++) std::cout << randomArr[i] << " "; 
    std::cout << RST << std::endl << std::endl;

    // Call our mergesort function -- pass our array, and beginning and end index
    // Also measure the execution time of the function
    std::chrono::high_resolution_clock::time_point currentBefore = std::chrono::high_resolution_clock::now();
    std::cout << "mergeSort(" << randomArr << ", " << 0 << ", " << arrSize << "); [CALL FROM MAIN]" << std::endl;
    mergeSort(randomArr, 0, arrSize);

    std::chrono::high_resolution_clock::time_point currentAfter = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentAfter - currentBefore).count();

    // Print our our sorted array
    std::cout << KBOLD << KGRN << "Sorted Array: " << RST << KCYN << std::endl;
    for (int i = 0; i < arrSize; i++) std::cout << randomArr[i] << " ";
    std::cout << RST << std::endl << std::endl << FMAG("Total exeuction time of mergeSort with ") << "[" << KGRN << arrSize + 1 << RST << "] " << FMAG("elements in the array: ") << KRED << KUNDL << duration << RST << KMAG << " microseconds." << RST << std::endl;

    return 0;
}

void mergeSort(int arr[], int leftIndex, int rightIndex){
    std::cout << "mergeSort(" << arr << ", " << leftIndex << ", " << rightIndex << ");" << std::endl;

    if (leftIndex < rightIndex){
        int middle = leftIndex + (rightIndex - leftIndex) / 2;

        mergeSort(arr, leftIndex, middle);
        mergeSort(arr, middle + 1, rightIndex);

        merge(arr, leftIndex, middle, rightIndex);
    }
}

void merge(int arr[], int leftIndex, int middle, int rightIndex){
    int n1 = middle - leftIndex + 1, n2 = rightIndex - middle, leftArr[n1], rightArr[n2], i = 0, j = 0, k = leftIndex;

    std::cout << "merge(" << arr << ", " << leftIndex << ", " << middle << ", " << rightIndex << ");" << std::endl;

    for (int i = 0; i < n1; leftArr[i] = arr[leftIndex + i], ++i);
    for (int i = 0; i < n2; rightArr[i] = arr[middle + 1 + i], ++i);
    for (; i < n1 && j < n2; arr[k++] = leftArr[i] <= rightArr[j] ? leftArr[i++] : rightArr[j++]);
    for (; i < n1 || j < n2; arr[k++] = i < n1 ? leftArr[i++] : rightArr[j++]);
}