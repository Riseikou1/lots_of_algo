#include <iostream>

void bubbleSort(int array[],int size){

    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(array[j]>array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
void printArray(int array[],int size){
    for(int i=0;i<size;i++){
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

int main(){
    int array[] = {4, 64, 34, 25, 5, 22, 11, 90, 12};
    int size = sizeof(array) / sizeof(array[0]);

    std::cout << "Array before sort: ";
    printArray(array,size);

    std::cout << "Array after sorting: ";
    bubbleSort(array,size);
    printArray(array,size);

    return 0;
}