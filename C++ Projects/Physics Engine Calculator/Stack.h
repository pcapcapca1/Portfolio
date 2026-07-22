#ifndef STACK_H
#define STACK_H
#include "Node.h"
class Stack
{
private:
    Node* Head;
    void destroyStackHelp(Node* deletePtr);
    {
        if (deletePtr == nullptr)
        {
            return;
        }
        else
        {
            Node* currentPtr = deletePtr->getNext();
            delete deletePtr;
            destroyStackHelp(currentPtr);
        }
    }
public:
    Stack();
    Stack(Node* node);
    Stack(const Stack  &s);//Copy constructor
    void destroyStack();//Destructor
    Node* getHead();
    void setHead(Node* head);//Mutator
    friend std::ostream& operator<<(std::ostream &printOut, const Stack& object);
    void operator<<(Node* pusher);
    void operator>>(Node *&popper);
};
#endif