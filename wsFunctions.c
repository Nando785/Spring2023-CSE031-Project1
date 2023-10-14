#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

using namespace std;




struct letters{
    char letter;
    letters* next;
};


class Stack{
private:  
    letters* top;
public:     

    Stack()
    {
        top = nullptr;
    }

    ~Stack()
    {
        letters* temp;

        while(top != nullptr)
        {
            temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(char letter)
    {
        letters* temp = new letters;

        temp->letter = letter;

        temp->next = top;
        top = temp;
    }

    void pop(char& letter)
    {
        if (top == nullptr)
        {
            cout << "Stack is empty." << endl;
            letter = '\0';
            return;
        }   
        
        letters* temp = top;

        letter = top->letter;

        top = top->next;

        delete temp;
    }

    bool isEmpty()
    {
        return (top == nullptr);
    }

    bool isFull()
    {
        letters* temp;

        try
        {
            temp = new letters;
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