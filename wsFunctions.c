#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H


struct node { // storage for i and j location
    int i;
    int j;
    struct node* next;
};

struct Stack { // storage for locations
    struct node* top;
    int nodeCount;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); // allocate memory for stack
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL; // initialize variables in empty stack
    stack->nodeCount = -1;
    return stack;
}

void destroyStack(struct Stack* stack) {
    if (stack == NULL) { // quit if nothing to destroy
        return;
    }

    struct node* temp;
    while (stack->top != NULL) { // loop through stack until empty, free each node
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }

    free(stack);
}

void push(struct Stack* stack, struct node* loc) {
    stack->nodeCount++; // increase node count by one
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        return;
    }

    temp->i = loc->i; // add node to top
    temp->j = loc->j;
    temp->next = stack->top;
    stack->top = temp;
}

void pop(struct Stack* stack) {
    if (stack->top == NULL) { // quit if empty
        return;
    }

    struct node* temp = stack->top; // remove top most node
    stack->top = stack->top->next;
    stack->nodeCount--; // decrease node count by one
    free(temp);
}

bool isEmpty(const struct Stack* stack) {
    return (stack->top == NULL);
}


#endif