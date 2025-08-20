#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char ch) 
{
    stack[++top] = ch;
}
char pop() 
{
    if (top == -1)
        return -1;
    return stack[top--];
}
char peek() 
{
    if (top == -1)
        return -1;
    return stack[top];
}
int precedence(char op) 
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}
int main() 
{
    char infix[MAX], postfix[MAX];
    int i, j = 0;
    printf("Enter the infix expression: ");
    scanf("%s", infix);
    for (i = 0; infix[i] != '\0'; i++) 
    {
        char ch = infix[i];
        if (isalpha(ch)) 
        {
            postfix[j++] = ch;
        } 
        else if (ch == '(') 
        {
            push(ch);
        } 
        else if (ch == ')') 
        {
            while (peek() != '(' && top != -1) 
            {
                postfix[j++] = pop();
            }
            pop();
        } 
        else 
        { 
            while (top != -1 && precedence(peek()) >= precedence(ch)) 
            {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }
    while (top != -1) 
    {
        postfix[j++] = pop();
    }
    postfix[j] = '\0'; 
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
