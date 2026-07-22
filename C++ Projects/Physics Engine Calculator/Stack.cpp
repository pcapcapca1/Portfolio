#include <iostream>
#include "Stack.h"

Stack::Stack()
{
    Head = nullptr; 
}
Stack::Stack(Node *node)
{
    Node* traversePtr = node;
    Node* A = new Node(traversePtr->getPayload());
    Head = A;
    Node* temporary = Head;
    traversePtr = traversePtr->getNext();
    while(traversePtr)
    {
        Node *B = new Node(traversePtr->getPayload());
        temporary->setNext(B);
        temporary = temporary->getNext();
        traversePtr = traversePtr->getNext();
    }
}
Stack::Stack(const Stack &s)//Copy Constructor
{
    if (s.Head == nullptr)
    {
        Head = nullptr;
        return;
    }
    Node* temporary = s.Head;
    Node* A = new Node(temporary->getPayload());
    Head = A;
    Node *ptr2 = Head;
    temporary = temporary->getNext();
    while(temporary)
    {
        A = new Node(temporary->getPayload());
        ptr2->setNext(A);
        ptr2 = A;
        temporary = temporary->getNext();
    }
}
void Stack::destroyStack()//Destructor for the Stack class
{
    destroyStackHelp(Head);
    Head == nullptr;
}
Node* Stack::getHead()
{
    if (Head == nullptr)
    {
        //Ptr->setNext(nullptr);
        return nullptr;
    }
    Node* Ptr = new Node;
    Ptr->setPayload(Head->getPayload());
    Ptr->setNext(nullptr);
    return Ptr;
}//Accessor
void Stack::setHead(Node* head)
{
    if (head == nullptr)
    {
        Head == nullptr;
        return;
    }
    Head = new Node;
    Node* temporary = head;
    Node* traversePtr = Head;
    Head->setPayload(temporary->getPayload());
    temporary = temporary->getNext();
    
    while (temporary != nullptr)
    {
        traversePtr->setNext(new Node);
        traversePtr = traversePtr->getNext();
        traversePtr->setPayload(traversePtr->getPayload());
        temporary = temporary->getNext();
    }
}
std::ostream& operator<<(std::ostream& printOut, const Stack &object)
{
    if(object.Head == nullptr)
    {
        printOut<<"empty";
        return printOut;
    }
    else if(((object.Head)->getPayload()).getOperator() == ' ')
    {
        Node *ptr = object.Head;
        printOut << (ptr->getPayload()).getOperand();
        ptr = ptr->getNext();
        while(ptr)
        {
            printOut << ", " << (ptr->getPayload()).getOperand();
            ptr = ptr->getNext();
        }
    }
    else
    {
        Node *ptr = object.Head;
        printOut << static_cast<char>((ptr->getPayload()).getOperator());
        ptr = ptr->getNext();
        while(ptr)
        {
            printOut << ", " << static_cast<char>((ptr->getPayload()).getOperator());
            ptr = ptr->getNext();
        }
    }
    
    return printOut;
}
void Stack::operator<<(Node *pusher)
{
    Node *ptr = new Node(pusher->getPayload());
    ptr->setNext(Head);
    Head = ptr;
}

void Stack::operator>>(Node *&popper)
{
    if (Head == nullptr)
    {
        popper = nullptr;
        return;
    }
    Node *temporary = Head;
    Head = temporary->getNext();
    temporary->setNext(nullptr);
    popper = temporary;
}