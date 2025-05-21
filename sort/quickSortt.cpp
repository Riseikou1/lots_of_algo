#include <iostream>

int partition(int array[],int start ,int end){
    int pivot = array[end];
    int i = start-1;
    for(int j = start;j<end;j++){
        if(array[j]<pivot){
            std::swap(array[++i],array[j]);
        }
    }
    std::swap(array[i+1],array[end]);
    return i+1;
}

void quickSort(int array[],int start,int end){
    if(start>=end) return;
    int pivot = partition(array,start,end);
    quickSort(array,start,pivot-1);
    quickSort(array,pivot+1,end);
}

void printArray(const int array[],int size){
    for(int i=0;i<size;i++){
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

int main(){
    int array[] = {4, 64, 34, 25, 5, 22, 11, 90, 12};
    int size = sizeof(array) / sizeof(array[0]);

    std::cout << "Array before sorting: ";
    printArray(array, size);

    quickSort(array, 0, size - 1);

    std::cout << "Array after sorting: ";
    printArray(array, size);

    return 0;
}