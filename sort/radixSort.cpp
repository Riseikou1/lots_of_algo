#include <iostream>
#include <vector>
#include <algorithm>

void radixSort(std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int exp = 1;

    while (maxVal / exp > 0) {
        std::vector<std::vector<int>> radixArray(10);

        // Distribute elements into buckets
        for (int num : arr) {
            int radixIndex = (num / exp) % 10;
            radixArray[radixIndex].push_back(num);
        }

        // Collect elements back into arr
        int index = 0;
        for (auto& bucket : radixArray) {
            for (int num : bucket) {
                arr[index++] = num;
            }
        }

        exp *= 10;
    }
}

int main() {
    std::vector<int> myArray = {170, 45, 75, 90, 802, 24, 2, 66};

    std::cout << "Original array: ";
    for (int num : myArray) std::cout << num << " ";
    std::cout << std::endl;

    radixSort(myArray);

    std::cout << "Sorted array: ";
    for (int num : myArray) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
