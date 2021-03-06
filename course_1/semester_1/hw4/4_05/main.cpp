#include <iostream>
#include "Stack.h"
#include "InfixToPostfix.h"

using namespace std;

int getCharLength(char str[], int maxLength)
{
    int length = 0;
    for (int i = 0; i < maxLength; i++)
        if (str[i] != '\0')
            length++;
        else
            return length;
    return length;
}

int convertToNumber(char number)
{
    int result = number - '0';
    return result;
}

int performOperation(char operation, int number1, int number2)
{
    //number2 stays before number1 in infix notation

    switch (operation) {
    case '-':
        return number2 - number1;
        break;
    case '+':
        return number1 + number2;
        break;
    case '*':
        return number1 * number2;
        break;
    case '/':
        return number2 / number1;
        break;
    default:
        return INT_MIN;
    }
}

int main()
{
    int const maxLength = 1024;
    char infixExpression[maxLength] = {' '};
    inputInfixExpression(infixExpression, maxLength);

    char postfixExpression[maxLength] = {' '};
    convertToPostfix(infixExpression, postfixExpression, maxLength);

    Stack *operands = createStack();
    int length = getCharLength(postfixExpression, maxLength);

    for (int i = 0; i < length; i++)
    {
        char token = postfixExpression[i];
        if (isdigit(token))
        {
            int value = convertToNumber(token);
            push(operands, value);
        }
        else
        {
            int number1 = pop(operands);
            int number2 = pop(operands);
            int result = performOperation(token, number1, number2);
            push(operands, result);
        }
    }

    int result = pop(operands);
    cout << "Result: " << result << endl;

    clearStack(operands);
    delete operands;

    return 0;
}
