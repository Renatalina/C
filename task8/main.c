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

VECTOR* list_pop(VECTOR* stk) {
    if(list_empty(stk)){
        return stk;
    }
    VECTOR *popped_elem = stk->prev_elem;
    free(stk);
    return popped_elem; 
}
//Implement a function to compare the structure variables
void compare_stk(VECTOR* first, VECTOR* second) {
    if(first->x > second->x) {
        printf("The frist X is higher second X");
    } else {
        printf("The frist X is lower second X");
    }
}
//Implement a program to extract and print individual bytes from an unsigned int using the following union:
union tagname
{
 unsigned a;
 unsigned char s[4];
};

int main ( void) {

    VECTOR* top=NULL;
    top = list_push(top, 80);
    top = list_push(top, 8);
    top = list_push(top, 50);
    printf("%d\n", top);
    
    top = list_pop(top);
    printf("%d\n", top);

    union tagname example;
    example.a = 123456;  
    for(int i = 0; i < 4; i++) {
        printf("%d байт: %u\n", i + 1, example.s[i]);
    }


    return 0;
}