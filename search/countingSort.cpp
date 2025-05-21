#include <iostream>
#include <vector>

void countingSort(int array[],int size);

int main() {
    int array[] = {4, 2, 2, 6, 3, 3, 1, 6, 5, 2, 3};
    int size = sizeof(array) / sizeof(array[0]);
    countingSort(array,size);
    for(int i=0;i<size;i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}

void countingSort(int array[],int size){

    int max = array[0];
    for(int i=0;i<size;i++){
        if(array[i]>max){
            max = array[i];
        }
    }
    std::vector<int> count(max+1,0);

    for(int i=0;i<size;i++){
        count[array[i]]++;
    }

    int index = 0;
    for(int i=0;i<=max;i++){
        while(count[i]>0){
            array[index++] = i;
            count[i]--;
        }
    }
}