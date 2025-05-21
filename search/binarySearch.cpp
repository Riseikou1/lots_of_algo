#include <iostream>
#include <vector>
#include <chrono>

// Binary Search Function
int binarySearch(const std::vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevents integer overflow
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1; // Not found
}

int main() {
    constexpr int SIZE = 100'000'000; // Large dataset
    constexpr int TARGET = 7'777'787; // Number to find

    // Creating a large sorted array efficiently
    std::vector<int> arr(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = i; // Sorted values
    }

    // Measure execution time
    auto start = std::chrono::high_resolution_clock::now();
    
    int index = binarySearch(arr, TARGET);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output Results
    if (index != -1) {
        std::cout << "Element found at index: " << index << "\n";
    } else {
        std::cout << "Element wasn't found.\n";
    }
    
    std::cout << "Execution time: " << elapsed.count() << " seconds\n";

    return 0;
}
