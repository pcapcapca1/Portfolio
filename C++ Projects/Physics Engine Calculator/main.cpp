/******************************************************************************

Prajit Alexander
Pxa220044

*******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

#include "Stack.h"
int checkOperator(char operat)
{
    if (operat == '^')
    {
        return 3;
    }
    else if (operat == '*' || operat == '/')
    {
        return 2;
    }
    else if (operat == '+' || operat == '-')
    {
        return 1;
    }
    else if(operat == '(')
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
double solvePostfix(Stack& firstStack, string post)
{
    Node* rightPopPtr = new Node;
    Node* leftPopPtr = new Node;
    Node* digitPtr = new Node;
    Data opera2;
    double answer;
    string num = "";
    for (int i = 0; i < post.length(); i++)
    {
        if (isdigit(post[i]))
        {
            num += post[i];
            while (isdigit(post[i+1]) || post[i+1] == '.')
            {
                num += post[i+1];
                i++;
            }
            opera2.setOperand(stod(num));
            digitPtr->setPayload(opera2);
            firstStack<<digitPtr;
            num = "";
        }
        else if (post[i] == '+')
        {
            firstStack>>rightPopPtr;
            firstStack>>leftPopPtr;
            opera2.setOperand((leftPopPtr->getPayload()).getOperand() + (rightPopPtr->getPayload()).getOperand());
            digitPtr->setPayload(opera2);
            firstStack<<digitPtr;
        }
        else if (post[i] == '-')
        {
            firstStack>>rightPopPtr;
            firstStack>>leftPopPtr;
            opera2.setOperand((leftPopPtr->getPayload()).getOperand() - (rightPopPtr->getPayload()).getOperand());
            digitPtr->setPayload(opera2);
            firstStack<<digitPtr;
        }
        else if (post[i] == '*')
        {
            firstStack>>rightPopPtr;
            firstStack>>leftPopPtr;
            opera2.setOperand((leftPopPtr->getPayload()).getOperand() * (rightPopPtr->getPayload()).getOperand());
            digitPtr->setPayload(opera2);
            firstStack<<digitPtr;
        }
        else if (post[i] == '/')
        {
            firstStack>>rightPopPtr;
            firstStack>>leftPopPtr;
            opera2.setOperand((leftPopPtr->getPayload()).getOperand() / (rightPopPtr->getPayload()).getOperand());
            digitPtr->setPayload(opera2);
            firstStack<<digitPtr;
        }
        else if (post[i] == '^')
        {
            firstStack>>rightPopPtr;
            firstStack>>leftPopPtr;
            opera2.setOperand(pow((leftPopPtr->getPayload()).getOperand(), (rightPopPtr->getPayload()).getOperand()));
            digitPtr->setPayload(opera2);
            firstStack<<digitPtr;
        }
    }
    return (firstStack.getHead())->getPayload().getOperand();
}
void infixToPostfix(string readLine)
{
    bool trueOrFalse = false;
    string post;
    Stack firstStack;
    for (int i = 0; i < readLine.length()+1; i++)
    {
        if (isdigit(readLine[i]) || readLine[i] == '.')
        {
            if (trueOrFalse)
            {
                post += readLine[i];
            }
            else
            {
                post = post + " " + readLine[i];
            }
            trueOrFalse = true;
        }
        else if (checkOperator(readLine[i]) && readLine[i] != ')')
        {
            trueOrFalse = false;
            Data opera1; 
            opera1.setOperator(readLine[i]);
            if (readLine[i] == '(')
            {
                Node* punctPtr1 = new Node;
                punctPtr1->setPayload(opera1);
                firstStack<<punctPtr1;
                delete punctPtr1;
            }
            else if(firstStack.getHead() == nullptr){
                Node* punctPtr4 = new Node;
                punctPtr4->setPayload( opera1 );
                firstStack<<punctPtr4;
                delete punctPtr4;
            }
            else if (checkOperator(readLine[i]) > checkOperator(((firstStack.getHead())->getPayload()).getOperator()))
            {
                Node* punctPtr2 = new Node;
                punctPtr2->setPayload(opera1);
                firstStack<<punctPtr2;
                delete punctPtr2;
            }
            else if (firstStack.getHead() && checkOperator(readLine[i]) <= checkOperator(((firstStack.getHead())->getPayload()).getOperator()))
            {
                Node* popperPtr;
                while (firstStack.getHead() && checkOperator(readLine[i]) <= checkOperator(((firstStack.getHead())->getPayload()).getOperator()))
                {
                    firstStack>>popperPtr;
                    post = post + ' ' + (popperPtr->getPayload()).getOperator();
                }
                Node* punctPtr3 = new Node;
                punctPtr3->setPayload(opera1);
                firstStack<<punctPtr3;
                delete popperPtr;
                delete punctPtr3;
            }
        }
        else if (readLine[i] == ')')
        {
            Node* popperPtr2;
            while (firstStack.getHead() && '(' != ((firstStack.getHead())->getPayload().getOperator()))
            {
                firstStack>>popperPtr2;
                post += ' ';
                post += ((popperPtr2->getPayload()).getOperator());
            }
            if (((firstStack.getHead())->getPayload()).getOperator())
            {
                firstStack>>popperPtr2;
            }
            delete popperPtr2;
        }
    }
    if (firstStack.getHead())
    {
        Node* popperPtr3;
        while (firstStack.getHead())
        {
            firstStack>>popperPtr3;
            post += ' ';
            post += ((popperPtr3->getPayload()).getOperator());
        }
        delete popperPtr3;
    }
    post = post.substr(1, post.length());
    cout << post << '\t' << fixed << setprecision(3) << solvePostfix(firstStack,post) << endl;
}
int main() 
{
    string inputFileName;
    string readLine;
    cout << "Enter a file containing the expressions: ";
    cin >> inputFileName;
    
    ifstream inFile(inputFileName);
    
    if (inFile)
    {
        while (inFile.good())
        {
            getline(inFile, readLine);
            infixToPostfix(readLine);
        }
    }
}