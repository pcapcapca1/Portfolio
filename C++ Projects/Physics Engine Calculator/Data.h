#ifndef DATA_H
#define DATA_H

class Data
{
private:
    double Operand;
    char Operator;
public:
    Data()
    {
        Operand = -1;
        Operator = ' ';
    }
    Data(double number)
    {
        Operand = number;
        Operator = ' ';
    }
    Data(double number, char oper)
    {
        Operand = number;
        Operator = oper;
    }
    double getOperand()
    {
        return Operand;
    }
    char getOperator()
    {
        return Operator;
    }
    void setOperand(double number)
    {
        Operand = number;
    }
    void setOperator(char character)
    {
        Operator = character;
    }
};

#endif