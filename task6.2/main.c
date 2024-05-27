#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <vadefs.h>

// #define MAX_LENGHT  100

// typedef struct stack_t {
//     char name[MAX_LENGHT];
//     char lastname[MAX_LENGHT];
//     struct stack_t *prev_elem;    
// } stack_t;

// stack_t stack_new ( void ) {
//     return (stack_t){};
// }

// bool stack_empty ( stack_t stk ) {
//     return stk.name != NULL ? 1 : 0;
// }

// void stack_push ( stack_t *stk , void *x) {
//     stk->prev_elem=x;
// }

// void *stack_pop ( stack_t stk) {
    
// }

// void stack_free ( stack_t *stk ) {
//     free(stk);
// }

// int main(){    
//     stack_t stack=stack_new();

//     stack_t new_elem={"Natalia", "Viski"};
//     stack_t new_elem2={"Elen", "Viski"};
//     stack_t new_elem3={"Valent", "Viski"};

//     stack_push(&new_elem, &stack);
//     stack_push(&new_elem2, &new_elem);
//     stack_push(&new_elem3, &new_elem3);
//     printf("%s\n", new_elem2.prev_elem->name);



//     stack_free(&new_elem3);
//     stack_free(&new_elem);

//     return 0;
// }


#define MAX_LENGHT  100

typedef struct stack_t {
    char name[MAX_LENGHT];
    char lastname[MAX_LENGHT];
    struct stack_t *prev_elem;    
} stack_t;

stack_t *stack_new ( void ) {
    stack_t* stk = calloc(1, sizeof(stack_t)); 
    return stk;
}

bool stack_empty ( stack_t *stk ) {
    return stk == NULL;
}

void stack_push ( stack_t **stk , stack_t *x) {
    x->prev_elem = *stk;
    *stk = x;
}

stack_t *stack_pop ( stack_t **stk ) {
    if(stack_empty(*stk)) {
        return NULL;
    }
    stack_t* top = *stk;
    *stk = (*stk)->prev_elem;  
    return top;
}

void stack_free ( stack_t *stk ) {
    while(stk != NULL) {
        stack_t* prev = stk->prev_elem;
        free(stk);
        stk = prev;
    }
}

int main(){    
    stack_t *stack = stack_new();
    
    stack_t *new_elem = stack_new();
    strcpy(new_elem->name, "Natalia");
    strcpy(new_elem->lastname, "Viski");
    
    stack_t *new_elem2 = stack_new();
    strcpy(new_elem2->name, "Elen");
    strcpy(new_elem2->lastname, "Viski");

    stack_push(&stack, new_elem);
    stack_push(&stack, new_elem2);

    printf("Stack top: %s\n", stack->name);

    stack_pop(&stack);  

    if(stack != NULL) {
        printf("Stack top after pop: %s\n", stack->name);
    }

    stack_free(stack);
    return 0;
}