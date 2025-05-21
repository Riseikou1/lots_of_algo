array = [4, 64, 34, 25, 5, 22, 11, 90, 12]

def quickSort(array,start,end):
    if start >= end : return
    pivot = partition(array,start,end)
    quickSort(array,start,pivot-1)
    quickSort(array,pivot+1,end)

def partition(array,start,end):
    pivot = array[end]
    i = start-1
    for j in range(start,end):
        if array[j] < pivot :
            i += 1
            array[i], array[j] = array[j], array[i]
    
    array[i+1],array[end] = array[end], array[i+1]
    return i+1

print("array before sorted: ")
print(array)

print("array after being sorted: ")
quickSort(array,0,len(array)-1)
print(array)
