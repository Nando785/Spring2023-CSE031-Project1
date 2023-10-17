#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H


struct letters {
    char letter;
    struct letters* next;
};

struct Stack {
    struct letters* top;
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

    struct letters* temp;
    while (stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }

    free(stack);
}

void push(struct Stack* stack, char letter) {
    struct letters* temp = (struct letters*)malloc(sizeof(struct letters));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    temp->letter = letter;
    temp->next = stack->top;
    stack->top = temp;
}

void pop(struct Stack* stack, char* letter) {
    if (stack->top == NULL) {
        fprintf(stderr, "Stack is empty.\n");
        *letter = '\0';
        return;
    }

    struct letters* temp = stack->top;
    *letter = stack->top->letter;
    stack->top = stack->top->next;
    free(temp);
}

bool isEmpty(const struct Stack* stack) {
    return (stack->top == NULL);
}


#endif