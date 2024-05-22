#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fillArray(int arr[], int size) {
    srand(time(NULL)); 

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

int compare(const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quicksort(int arr[], int low, int high) {
  if (low < high) {
        int pivotIndex = high;
        int i = low;
        for(int j = low; j < high; ++j) {
            if(compare(&arr[j], &arr[pivotIndex]) < 0) {
                swap(&arr[i], &arr[j]);
                ++i;
            }
        }
        swap(&arr[i], &arr[pivotIndex]);

        quicksort(arr, low, i - 1);
        quicksort(arr, i + 1, high);
    }
}

//it's my favorite method to sort the array))
void qsort_second(int arr[], int size) {
    for(int i=0; i< size; i++) {
        for(int y=0; y< size; y++) {
            if(compare(&arr[i], &arr[y]) < 0) {
                swap(&arr[i], &arr[y]);
            }
        }
    }
}

int main(){
    int arr[15];
    int size = sizeof(arr)/sizeof(arr[0]);

    fillArray(arr, size);
  
    printf("Original array: \n");
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }

    // quicksort(arr, 0, size-1);
    qsort_second(arr, size);
    
    printf("\nSorted array: \n");
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}