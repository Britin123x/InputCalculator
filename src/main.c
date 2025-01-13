#include <ctype.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT_STRING 50

int formulaParser(char inputString[]);
bool checkMatch(char c1, char c2);
bool balancedParentheses(char inputString[]);

int main(void)
{
    bool userDone = false;
    int returnValue = 0;
    char inputString[MAX_INPUT_STRING];
    char exitCommand[] = "quit";
    printf("Version 0.1\n");

    while (userDone == false)
    {
        printf("Please insert expression to solve:");
        fgets(inputString, MAX_INPUT_STRING, stdin);
        if (strcmp(exitCommand, inputString) == 0)
        {
            userDone = true;
            break;
        }
        returnValue = formulaParser(inputString);
        if (returnValue != 0)
        {
            printf("The return code given is %d\n", returnValue);
            return returnValue;
        }
    }

    printf("Thank you for using Britin's Input Calculator. Exiting...\n");

    return 0;
}

int formulaParser(char inputString[])
{
    int inputStringLength = strlen(inputString);
    char outputString[inputStringLength];
    int currentOutputPosition = 0;
    for (int i = 0; i < inputStringLength; i++)
    {
        if (!(isspace(inputString[i])))
        {
            outputString[currentOutputPosition] = inputString[i];
            currentOutputPosition++;
        }
    }

    if (strcmp(outputString, "") == 0)
    {
        return 1;
    }
    if (balancedParentheses(outputString) == false)
    {
        printf("Error: Parentheses are unbalanced.\n");
        return 2;
    }
    printf("Here is the unspaced output string:\n");
    printf("%s\n", outputString);

    return 0;
}

bool checkMatch(char c1, char c2)
{
    if (c1 == '(' && c2 == ')')
        return true;
    if (c1 == '{' && c2 == '}')
        return true;
    if (c1 == '[' && c2 == ']')
        return true;
    return false;
}

bool balancedParentheses(char inputString[])
{
    int top = -1;
    char s[MAX_INPUT_STRING];
    int parenthesesLength = 0;
    int inputLength = strlen(inputString);
    for (int i = 0; i < inputLength; ++i)
    {
        if (inputString[i] == '{' || inputString[i] == '}' || inputString[i] == '(' || inputString[i] == ')' ||
            inputString[i] == '[' || inputString[i] == ']')
        {
            s[parenthesesLength] = inputString[i];
            parenthesesLength++;
        }
    }

    for (int i = 0; i < parenthesesLength; ++i)
    {
        if (top < 0 || !checkMatch(s[top], s[i]))
        {
            ++top;
            s[top] = s[i];
        }
        else // If there is a match found, then we can decrement the count of top.
            --top;
    }

    if (top == -1)
        return true;
    else
        return false;
}
