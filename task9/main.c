#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50
#define BYTE_SIZE 8

//Take two strings as arguments. 
//If the first exists in the second as a substring, return a pointer to the first occurrence, otherwise zero.
char *find_substring(char *str1, char *str2)
{
    return strstr(str2, str1);    
}

//Write function that determine endianness at run time.
void check_endian() {
    int num = 1;
    if(*(char *)&num == 1) {
        printf("Little-Endian\n");
    } else {
        printf("Big-Endian\n");
    }
}

//Write function for reversing the byte order (swap endianness).
unsigned int swap_endianness(unsigned int x) {

    unsigned int size = sizeof(x);
    unsigned int reversed = 0;

    for (int i = 0; i < size; i++) {
        unsigned int tmp = (x >> (BYTE_SIZE * i)) & 0xff;
        reversed |= tmp << (BYTE_SIZE * (size - 1 - i));
    }

    return reversed;
}

//Write function that find the largest and smallest word in a string.
//Function takes three strings as arguments and has the following prototype:
//void find_max_min_str(const char * input_str, char * max_str, char * min_str)
//Example:  
//If input_str is "It is a string with smallest and largest word" then max_str is "smallest" and min_str is "a".
void find_max_min_str(const char *input_str, char *max_str, char *min_str){
    int len = strlen(input_str);
    char word[len];
    int j = 0, max = 0, min = len;

    for(int i = 0; i <= len; i++){
        if(!isspace(input_str[i]) && input_str[i] != '\0'){
            word[j++] = input_str[i];
        } else if(j != 0){
            word[j] = '\0';
            if(j > max){
                max = j;
                strncpy(max_str, word, MAX_LEN-1);
                max_str[MAX_LEN-1] = '\0'; 
            }
            if(j < min){
                min = j;
                strncpy(min_str, word, MAX_LEN-1);
                min_str[MAX_LEN-1] = '\0';
            }
            j = 0;
        }
    }
}


int main()
{
    char str1[] = "world";
    char str2[] = "Hello, world!";
    char *substr_ptr;

    substr_ptr = find_substring(str1, str2);
    if(substr_ptr != NULL)
    {
        printf("Substring found at index %ld in '%s'\n", substr_ptr - str2, str2);
    }
    else
    {
        printf("Substring not found\n");
    }

    check_endian();

    unsigned int x = 0x12345678;
    printf("Before swap: 0x%X\n", x);
    x = swap_endianness(x);
    printf("After swap: 0x%X\n", x);



    char str[] = "It    is a string with     smallest and largest word";
    char min[MAX_LEN], max[MAX_LEN];
    find_max_min_str(str, max, min);
    printf("The smallest word is: %s\n", min);
    printf("The largest word is: %s", max);


    return 0;
}