#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

struct node{
    char letter;
    struct node* next;
};


struct Stack{

    struct node* top;

    
    
    // struct Stack()
    // {
    //     top = nullptr;
    // }

    ~Stack()
    {
        Node* temp;

        while (top != nullptr)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(int id)
    {
        Node* temp = new Node;

        temp->id = id;

        temp->next = top;
        top = temp;
    }
    
    void pop(int& id)
    {
        Node* temp = top;


        id = top->id;

        top = top->next;

        delete temp;
    }

    bool isEmpty()
    {
        return (top == nullptr);
    }

    bool Stack::isFull()
    {
        Node* temp;

        try
        {
            temp = new Node;
            delete temp;
            return false;
        }
        catch(bad_alloc)
        {
            return true;
        }
    }
        
};



#endif