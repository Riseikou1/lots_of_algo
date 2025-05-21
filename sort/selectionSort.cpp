#include <iostream>
using namespace std;

// Selection Sort Function
void selectionSort(int* array, const int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (*(array + j) < *(array + minIndex)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(*(array + i), *(array + minIndex));
        }
    }
}

// Print Array Function
void printArray(const int* array, const int size) {
    for (int i = 0; i < size; i++) {
        cout << *(array + i) << " ";  // Use pointer arithmetic here
    }
    cout << endl;
}

int main() {
    int array[] = {4, 64, 34, 25, 5, 22, 11, 90, 12};
    int size = sizeof(array) / sizeof(array[0]);

    cout << "Array before sort: ";
    printArray(array, size);

    selectionSort(array, size);  // Sort the array using selection sort

    cout << "Array after sorting: ";
    printArray(array, size);  // Print the sorted array

    return 0;
}
