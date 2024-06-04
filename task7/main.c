#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int arr[], size_t size) {
    srand(time(NULL));

    for(int i=0; i<size; i++) {
        arr[i]= rand() % size*2 + 10 % size - 20;
    }
}

int duplicate_sum(int first_arr[], size_t size_first, int second_arr[], size_t size_second) {
    int sum=0;

    for (int i=0; i <size_first; i++) {
        for(int y=0; y < size_second; y++) {
            sum += first_arr[i] == second_arr[y] ? first_arr[i] : 0;
        }
    }

    return sum;
}

int max_digit(int arr[], size_t size) {
    int max=arr[0];
    for(int i=1; i<size; i++) {
        max = (arr[i] > max) ? arr[i] : max;        
    }

    return max;
}

int min_digit(int arr[], size_t size) {
    int min=arr[0];
    for(int i=1; i<size; i++) {
        min = *(arr+i) < min ? *(arr+i) : min;
    }

    return min;
}

void merged_two_array(int first_arr[], int second_arr[], int *new_arr, size_t size) {

    int index_first = 0;
    int index_second = 0;

    for ( int i=0; i<size; i++) {
        if (first_arr[index_first] < second_arr[index_second]) {
            new_arr[i] = first_arr[index_first];
            index_first++;
        } else {
            new_arr[i] = second_arr[index_second];
            index_second++;
        }              
    }   
}

int main(){

    int arr [22];
    size_t size = sizeof(arr)/sizeof(arr[0]);
    fillArray(arr, size);

    int second_arr[35];
    size_t size_second = sizeof(second_arr)/sizeof(second_arr[0]);
    fillArray(second_arr, size_second);
  
    printf("First array: \n");
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }

    printf("\nSecond array: \n");
    for(int i = 0; i<size_second; i++){
        printf("%d ", second_arr[i]);
    }


    int sum = duplicate_sum(arr, size, second_arr, size_second);
    printf("\nTotal of duplicate sume is: %d\n", sum);

    int max = max_digit(arr, size);
    int max_second = max_digit(second_arr, size_second);
    printf("\n First max: %d", max);
    printf("\n Second max: %d", max_second);

    int min = min_digit(arr, size);
    int min_second = min_digit(second_arr, size_second);

    printf("\n First min digit: %d", min);
    printf("\n Second min digit: %d", min_second);

    int arr_one [] = {1,3,5,7};
    int arr_two [] = {2,4,6,8};
    size_t size_one = sizeof(arr_one)/sizeof(arr_one[0]);
    size_t size_two = sizeof(arr_two)/sizeof(arr_two[0]);

    size_t new_size_arr = size_one + size_two;
    int *arr_merge = malloc(new_size_arr * sizeof (int));
    merged_two_array(arr_one, arr_two, arr_merge, new_size_arr);

    printf("\nResult after merged: \n");
    for(int i = 0; i<new_size_arr; i++){
        printf("%d ", arr_merge[i]);
    }


    return 0;
}