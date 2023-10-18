#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wsFunctions.c"


int main()
{
    struct Stack* stack = createStack();
    struct node one;
    struct node two;
    
    one.i = 0;
    one.j = 5;
    
    two.i = 10;
    two.j = 20;
    

    push(stack,&one);
    push(stack,&two);
    


   printf("(%d, %d)\n", stack->top[0].i, stack->top[0].j);
   printf("\n");
   printf("(%d, %d)\n", stack->top[-1].i, stack->top[-1].j);
    
    
}