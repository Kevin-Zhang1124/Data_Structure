// use array to create an Abstract Data Type (ADT) - Stack

#include "stack.h"
#include <stdio.h>

// provide struct definition of stack
// using dymanic array
struct stack {
    int len;        // number of elements in arr
    int cap;        // capacity of arr
    int* arr;
};


// stack_create() creates a struct stack in heap memory
// Effects: allocate memory
// requires: caller must call stack_destroy
struct stack* create_stack(void) {
    // allocate memory in heap
    struct stack* stk = malloc(sizeof(struct stack));
    // field initialization
    stk->len = 0;
    stk->cap = 1;
    stk->arr = malloc(sizeof(int) * stk->cap);
    // return the pointer
    return stk;
}


// stack_destroy(stk) de-allocates stk in heap memory, stk becomes invalid
// Effects: deallocates memory
void stack_destroy(struct stack* stk) {
    if (stk != NULL) {
        // free field first if they point to heap memory
        free(stk->arr);
        free(stk);
    }
}


// stack_empty(stk) returns true if stk contains no data, false otherwise
// requires: stk is not NULL
bool stack_empty(const struct stack* stk) {
    return stk->len == 0;
}


// stack_push(stk, data) pushes data onto stack
// effects: mutates stk
// requires: stk is not NULL
void stack_push(struct stack* stk, int data) {
    assert(stk);
    // check if stk is full
    if (stk->len == stk->cap) {
        stk->cap *= 2;
        stk->arr = realloc(stk->arr, sizeof(int) * stk->cap);
    }
    stk->arr[stk->len] = data;
    stk->len += 1;
}


// stack_pop(stk) removes the data from the top of stk, and returns the data
// effects: mutates stk
// requires: stk is not NULL
//           stk is not empty
int stack_pop(struct stack* stk) {
    assert(stk);
    assert(!stack_empty(stk));

    int retval = stk->arr[stk->len - 1];
    stk->len -= 1;
    return retval;
}


// stack_top(stk) returns the top data of the stk
// requires: stk is not NULL
//           stk is not empty
int stack_top(const struct stack* stk) {
    assert(stk);
    assert(!stack_empty(stk));

    return stk->arr[stk->len - 1];
}
