#include <iostream>

void insertionSort(int* array, int size) {
    for (register int i = 1; i < size; i++) {
        int temp = array[i];
        int j = i - 1;

        // Move elements of array[0..i-1] that are greater than temp
        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j]; // Shift right
            j--;
        }
        array[j + 1] = temp; // Insert at correct position
    }
}

void displayArray(const int* array, const int size) {
    for (const int* ptr = array; ptr < array + size; ptr++) {
        std::cout << *ptr << " ";
    }
    std::cout << "\n";
}

int main() {
    int my_array[] = {4, 64, 34, 25, 5, 22, 11, 90, 12};
    int size = sizeof(my_array) / sizeof(my_array[0]);

    std::cout << "Actual Array: ";
    displayArray(my_array, size);

    insertionSort(my_array, size);

    std::cout << "Sorted Array: ";
    displayArray(my_array, size);

    return 0;
}
