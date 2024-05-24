#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <vadefs.h>

#define MAX_LENGHT  100

typedef struct stack_t {
    char name[MAX_LENGHT];
    char lastname[MAX_LENGHT];
    struct stack_t *prev_elem;    
} stack_t;

stack_t stack_new ( void ) {
    return (stack_t){"Natalia", "Viski"};
}

bool stack_empty ( stack_t stk ) {
    return stk.name == "Natalia" && stk.lastname == "Viski" ? 1 : 0;
}

void stack_push ( stack_t stk , void *x) {
    stk.prev_elem=x;
}

void *stack_pop ( stack_t stk, stack_t next ) {
    next.prev_elem = stk.prev_elem;
}

void stack_free ( stack_t *stk ) {
    free(stk);
}

int main(){
    
    return 0;
}