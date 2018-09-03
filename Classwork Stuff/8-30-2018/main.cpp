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

// Function prototypes
void mergeSort(int arr[], int leftIndex, int rightIndex), merge(int arr[], int leftIndex, int middle, int rightIndex);

int main(void){
    // Seed our random number generator
    srand((unsigned) time(0));

    // Randomly generate an array 1000 elements long for sorting
    int randomArr[1000], arrSize = (sizeof(randomArr) / sizeof(randomArr[0])) - 1;
    for (int i = 0; i < 1000; randomArr[i++] = (rand() % 1000) + 1);

    // Print our inital array to use it as a visual reference
    std::cout << "Inital Array: " << std::endl;
    for (int i = 0; i < arrSize; i++) std::cout << randomArr[i] << " "; 
    std::cout << std::endl << std::endl;

    // Call our mergesort function -- pass our array, and beginning and end index
    // Also measure the execution time of the function
    std::chrono::high_resolution_clock::time_point currentBefore = std::chrono::high_resolution_clock::now();
    mergeSort(randomArr, 0, arrSize);
    std::chrono::high_resolution_clock::time_point currentAfter = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentAfter - currentBefore).count();

    // Print our our sorted array
    std::cout << "Sorted Array: " << std::endl;
    for (int i = 0; i < arrSize; i++) std::cout << randomArr[i] << " ";
    std::cout << std::endl << std::endl << "Total exeuction time of mergeSort with [" << arrSize + 1 << "] elements in the array: " << duration << " microseconds." << std::endl;

    return 0;
}

void mergeSort(int arr[], int leftIndex, int rightIndex){
    if (leftIndex < rightIndex){
        int middle = leftIndex + (rightIndex - leftIndex) / 2;

        mergeSort(arr, leftIndex, middle);
        mergeSort(arr, middle + 1, rightIndex);

        merge(arr, leftIndex, middle, rightIndex);
    }
}

void merge(int arr[], int leftIndex, int middle, int rightIndex){
    int n1 = middle - leftIndex + 1, n2 = rightIndex - middle, leftArr[n1], rightArr[n2], i = 0, j = 0, k = leftIndex;

    for (int i = 0; i < n1; leftArr[i] = arr[leftIndex + i], ++i);
    for (int i = 0; i < n2; rightArr[i] = arr[middle + 1 + i], ++i);
    for (; i < n1 && j < n2; arr[k++] = leftArr[i] <= rightArr[j] ? leftArr[i++] : rightArr[j++]);
    for (; i < n1 || j < n2; arr[k++] = i < n1 ? leftArr[i++] : rightArr[j++]);
}