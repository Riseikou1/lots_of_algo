#include <iostream>
using namespace std;

// Merge function to combine two sorted arrays
void merge(int array[], int* left, int leftSize, int* right, int rightSize) {
    int i = 0, j = 0, k = 0;

    // Merge the left and right arrays into the original array
    while (i < leftSize && j < rightSize) {
        if (left[i] < right[j]) {
            array[k++] = left[i++];
        } else {
            array[k++] = right[j++];
        }
    }

    // If there are remaining elements in the left array, copy them
    while (i < leftSize) {
        array[k++] = left[i++];
    }

    // If there are remaining elements in the right array, copy them
    while (j < rightSize) {
        array[k++] = right[j++];
    }
}

// MergeSort function to divide and sort the array
void mergeSort(int array[], int size) {
    if (size <= 1) return; // Base case for recursion

    int middle = size / 2;

    // Dynamically allocate memory for left and right arrays using pointers
    int* left = new int[middle];
    int* right = new int[size - middle];

    // Manually copy data to left and right arrays using pointers
    int* leftPtr = left;
    int* rightPtr = right;
    for (int i = 0; i < middle; i++) {
        *leftPtr++ = array[i];  // Copy to left array
    }
    for (int i = middle; i < size; i++) {
        *rightPtr++ = array[i]; // Copy to right array
    }

    // Recursively sort the left and right subarrays
    mergeSort(left, middle);
    mergeSort(right, size - middle);

    // Merge the sorted left and right arrays into the original array
    merge(array, left, middle, right, size - middle);

    // Free dynamically allocated memory
    delete[] left;
    delete[] right;
}

int main() {
    int array[] = {4, 64, 34, 25, 5, 22, 11, 90, 12};
    int size = sizeof(array) / sizeof(array[0]);

    cout << "Array before sort: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    // Perform merge sort
    mergeSort(array, size);

    cout << "Array after sorting: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}
