#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H


struct node {
    int i;
    int j;
    struct node* next;
};

struct Stack {
    struct node* top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

void destroyStack(struct Stack* stack) {
    if (stack == NULL) {
        return;
    }

    struct node* temp;
    while (stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }

    free(stack);
}

void push(struct Stack* stack, struct node* loc) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    temp->i = loc->i;
    temp->j = loc->j;
    temp->next = stack->top;
    stack->top = temp;
}

void pop(struct Stack* stack, struct node loc) {
    if (stack->top == NULL) {
        fprintf(stderr, "Stack is empty.\n");
        //*letter = '\0';
        return;
    }

    struct node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

bool isEmpty(const struct Stack* stack) {
    return (stack->top == NULL);
}


#endif