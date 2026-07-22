#ifndef NODE_H
#define NODE_H
#include "Data.h"
class Node 
{
private:   
   Data Payload;
   Node* Next;
public:
    Node()
    {
        Next = nullptr;
    }
    Node(Data payload)
    {
        Payload = payload;
        Next = nullptr;
    }
    Data getPayload()
    {
        return Payload;
    }  
    Node* getNext()
    {
        return Next;
    }
    void setPayload(Data payload)
    {
        Payload = payload;
    }
    void setNext(Node* next)
    {
        Next = next;
    }
};
#endif