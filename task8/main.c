#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vadefs.h>

//Implement Linked list and insert and delete operations for it.
typedef struct tag_obj {
    int x;
    struct tag_obj *prev_elem;
}VECTOR;

bool list_empty(VECTOR* stk) {
    return stk==NULL;
}

VECTOR* list_push(VECTOR* stk, int new_data) {
    VECTOR* new_elem = malloc(sizeof(VECTOR));
    new_elem->x = new_data;
    new_elem->prev_elem = stk;
    return new_elem;    
}

VECTOR* list_pop(VECTOR* stk, int find_data) {
    if(list_empty(stk)){
        return stk;
    }

    VECTOR *prev = stk;
    if(stk->x != find_data) {
        while (prev->prev_elem->prev_elem && prev->prev_elem->x != find_data)
        {
            prev = prev->prev_elem;
        }
        if(prev->prev_elem->x == find_data) {
            VECTOR *popped_elem = prev->prev_elem;
            prev->prev_elem= popped_elem->prev_elem ? popped_elem->prev_elem : NULL;
            free(popped_elem);
        }
        
        return stk; 

    } else {
        VECTOR *top = stk->prev_elem;
        free(stk);
        return top;
    }   
}
//Implement a function to compare the structure variables
bool compare_stk(VECTOR* first, VECTOR* second) {
    if(first->x > second->x) {
        printf("The frist X is higher than second X");
    } else {
        printf("The frist X is lower than second X");
    }

    return first-> x > second -> x;
}

//Implement a program to extract and print individual bytes from an unsigned int using the following union:
union tagname
{
 unsigned a;
 unsigned char s[4];
} bin = {0x01020304};

bool check_big_little_endian() {

   return bin.s[0] == 1;
}


int main ( void) {

    VECTOR *top = NULL;
    top = list_push(top, 56);
    top = list_push(top, 74);
    top = list_push(top, 89);
    top = list_push(top, 32);

    top = list_pop(top, 22);    
    printf("After removed elem list has: %d\n", top->x);
    printf("%d\n", top->prev_elem->x);
    printf("%d\n", top->prev_elem->prev_elem->x);
    if(top->prev_elem->prev_elem->prev_elem != NULL)
    printf("%d\n", top->prev_elem->prev_elem->prev_elem->x);

    union tagname example;
    example.a = 0x01020304;  
    for(int i = 0; i < 4; i++) {
        printf("%d байт: %2x\n", i + 1, example.s[i]);
    }

    int camparing = compare_stk(top, top->prev_elem);
    printf("\nCamparing: %d\n", camparing);

    if(check_big_little_endian()) {
        printf("This is BigEndian system");
    } else {
        printf("This is a LittleEndian system");
    }

    return 0;
}