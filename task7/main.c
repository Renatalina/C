#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int arr[], size_t size) {

    if(size > 0) {
        srand(time(NULL));
        for(int i=0; i<size; i++) {
            arr[i]= rand() % size*2 + 10 % size - 20;
        }
    }
}

int compare (const void * a, const void * b) { 
  return ( *(int*)a - *(int*)b );
}

int duplicate_sum(int arr[], size_t size) {
    qsort(arr, size, sizeof(int), compare); 

    int sum = 0;
    int prev = arr[0];
    int count = 1;
    for (int i = 1; i < size; i++) { 
        if (arr[i] == prev) { 
            if (count == 1) { 
                sum += arr[i]*2;
                count++;
            } else { 
                sum += arr[i];
            }
        } else {
            prev = arr[i];
            count = 1;
        }
    }
    return sum;
}

int max_digit(int arr[], size_t size) {

    if (size > 0) { 
        int max=arr[0];
        for(int i=1; i<size; i++) {
            max = (arr[i] > max) ? arr[i] : max;
        }
        return max;
    }

    return 0;    
}

int min_digit(int arr[], size_t size) {
    
    if (size > 0) {
        int min=arr[0];
        for(int i=1; i<size; i++) {
            min = *(arr+i) < min ? *(arr+i) : min;
        }
        return min;
    }

    return 0;    
}

void merged_two_array(int first_arr[], size_t size_one, int second_arr[], size_t size_two, int *new_arr, size_t size) {

    int index_first=0;
    int index_second=0;

    if(size_one && size_two) {
        for ( int i=0; i<size; i++) {
            if((index_first < size_one) && (index_second < size_two)) {
                if(first_arr[index_first] < second_arr[index_second]) {
                   new_arr[i] = first_arr[index_first];
                   index_first++;
                } else {
                   new_arr[i] = second_arr[index_second];
                   index_second++;
               } 
            } else if (index_first < size_one) {
                new_arr[i] = first_arr[index_first];
                index_first++;
            } else if (index_second < size_two) {
                new_arr[i] = second_arr[index_second];
                index_second++;
            }        
        }

    } else if (size_one) {
        for ( int i=0; i<size; i++) {
            new_arr[i] = first_arr[i];
        }

    } else if (size_two) {
        for ( int i=0; i<size; i++) {
            new_arr[i] = second_arr[i];
        }  

    }   
}

int main(){

    int arr [5];
    size_t size = sizeof(arr)/sizeof(arr[0]);
    fillArray(arr, size);

    int second_arr[5];
    size_t size_second = sizeof(second_arr)/sizeof(second_arr[0]);
    fillArray(second_arr, size_second);
  
    printf("First array: \n");
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }

    int sum = duplicate_sum(arr, size);
    printf("\nTotal of duplicate sum is: %d\n", sum);

    printf("\nSecond array: \n");
    for(int i = 0; i<size_second; i++){
        printf("%d ", second_arr[i]);
    }


    int max = max_digit(arr, size);
    int max_second = max_digit(second_arr, size_second);
    printf("\n First max: %d", max);
    printf("\n Second max: %d", max_second);

    int min = min_digit(arr, size);
    int min_second = min_digit(second_arr, size_second);

    printf("\n First min digit: %d", min);
    printf("\n Second min digit: %d", min_second);

    int arr_one [] = {1,5,8,9};
    int arr_two [] = {2,5,7,15};
    size_t size_one = sizeof(arr_one)/sizeof(arr_one[0]);
    size_t size_two = sizeof(arr_two)/sizeof(arr_two[0]);

    size_t new_size_arr = size_one + size_two;
    int *arr_merge = malloc(new_size_arr * sizeof (int));
    merged_two_array(arr_one, size_one, arr_two, size_two, arr_merge, new_size_arr);

    printf("\nResult after merged: \n");
    for(int i = 0; i < new_size_arr; i++){
        printf("%d ", arr_merge[i]);
    }


    return 0;
}