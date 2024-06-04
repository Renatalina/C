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


// #define MAX_LENGHT  100

// typedef struct stack_t {
//     char name[MAX_LENGHT+1];
//     char lastname[MAX_LENGHT+1];
//     struct stack_t *prev_elem;    
// } stack_t;

// stack_t *stack_new ( void ) {
//     stack_t* stk = calloc(1, sizeof(stack_t)); 
//     return stk;
// }

// bool stack_empty ( stack_t *stk ) {
//     return stk == NULL;
// }

// void stack_push ( stack_t **stk , stack_t *x) {
//     x->prev_elem = *stk;
//     *stk = x;
// }

// stack_t *stack_pop ( stack_t **stk ) {
//     if(stack_empty(*stk)) {
//         return NULL;
//     }
//     stack_t* top = *stk;
//     *stk = (*stk)->prev_elem;
//     free(stk);  
//     return top;
// }

// void stack_free ( stack_t *stk ) {
//     while(stk != NULL) {
//         stack_t* prev = stk->prev_elem;
//         free(stk);
//         stk = prev;
//     }
// }

// int main(){    
//     stack_t *stack = stack_new();
    
//     stack_t *new_elem = stack_new();
//     strcpy(new_elem->name, "Natalia");
//     strcpy(new_elem->lastname, "Viski");
    
//     stack_t *new_elem2 = stack_new();
//     strcpy(new_elem2->name, "Elen");
//     strcpy(new_elem2->lastname, "Viski");

//     stack_push(&stack, new_elem);
//     stack_push(&stack, new_elem2);

//     printf("Stack top: %s\n", stack->name);

//     stack_pop(&stack);  

//     if(stack != NULL) {
//         printf("Stack top after pop: %s\n", stack->name);
//     }

//     // stack_free(stack);
//     return 0;
// }


////work version
// #define MAX_LENGHT  100

// typedef struct stack_t {
//     char name[MAX_LENGHT+1];
//     char lastname[MAX_LENGHT+1];
//     struct stack_t *prev_elem;    
// } *stack_t;

// stack_t stack_new ( void ) {
//     stack_t stk = calloc(1, sizeof(struct stack_t)); 
//     return stk;
// }

// bool stack_empty ( stack_t stk ) {
//     return stk == NULL;
// }

// void stack_push ( stack_t stk , void *x) {
//     stk->prev_elem = x;
// }

// void *stack_pop ( stack_t stk ) {
//     if(stack_empty(stk)) {
//         return NULL;
//     }

//     stack_t top = stk;
//     free(stk);
//     stk = top->prev_elem;
// }

// void stack_free ( stack_t* stk ) {
//     while(stk != NULL) {
//         free(stk);
//     }
// }

// int main() {

//     stack_t stack = stack_new();
    
//     stack_t new_elem = stack_new();
//     strcpy(new_elem->name, "Natalia");
//     strcpy(new_elem->lastname, "Viski");
//     stack_push(stack, new_elem);
    
    
//     stack_t new_elem2 = stack_new();
//     strcpy(new_elem2->name, "Elen");
//     strcpy(new_elem2->lastname, "Viski");
//     stack_push(new_elem, new_elem2);

//     stack_t new_elem3 = stack_new();
//     strcpy(new_elem3->name, "Valent");
//     strcpy(new_elem3->lastname, "Viski");    
//     stack_push(new_elem2, new_elem3);

//     printf("Stack top: %s\n", stack->prev_elem->name);

//     stack = stack_pop(stack); 
//     stack = stack_pop(stack); 

//     if(stack != NULL) {
//         printf("Stack top after pop: %s\n", stack->name);
//         free(stack);
//     }

//     return 0;
// }


#define MAX_LENGHT  100

typedef struct stack_t {
    void* data;
    struct stack_t *prev_elem;
}stack_t;

bool stack_empty(stack_t* stk) {
    return stk==NULL;
}

stack_t* stack_push(stack_t* stk, void *new_data) {
    stack_t* new_elem = calloc(1,sizeof(stack_t));
    new_elem->data = new_data;
    new_elem->prev_elem = stk;
    return new_elem;    
}

stack_t* stack_pop(stack_t* stk) {
    if(stack_empty(stk)){
        return NULL;
    }
    stack_t *popped_elem = stk;
    stk = stk->prev_elem;
    return stk; 
}

void stack_free(stack_t* stk) {
    stack_t* current=stk;
    while(current != NULL){
        stack_t* next=current->prev_elem;
        free(current);
        current=next;
    }
}

int main() {
 
    stack_t* my_stack = NULL;

    for (int i = 0; i < 10; ++i) {
        int* data = (int*) malloc(sizeof(int));
        *data = i;
        my_stack = stack_push(my_stack, data);
    }

    while (!stack_empty(my_stack)) {
        int* data = (int*) my_stack->data;
        printf("%d\n", *data);
        stack_t* next_stack = stack_pop(my_stack);
        free(data);
        free(my_stack);
        my_stack = next_stack;
    }

    return 0;
}