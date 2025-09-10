#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char c)
{
stack[++top] = c;
}
char pop() 
{
if (top == -1) 
{
return '\0';
    }
return stack[top--];
}
char peek() 
{
if (top == -1) 
{
return '\0';
    }
return stack[top];
}
int precedence(char c) 
{
if (c == '^') return 3;
if (c=='*' || c=='/') return 2;
if (c=='+' || c=='-') return 1;
return 0;
}
int isOperator(char c) 
{
return (c=='^' || c=='*' || c=='/' || c=='+' || c == '-');
}
void infixtopostfix(char infix[], char postfix[]) 
{
int i = 0, j = 0;
char c;
while ((c = infix[i]) != '\0') 
{
if (isalnum(c)) 
{  
postfix[j++] = c;
        } else if (c == '(') 
        {  
push(c);
        } else if (c == ')') 
        {  
while (top != -1 && peek() != '(') 
{
postfix[j++] = pop();
            }
pop();  
        } 
        else if (isOperator(c)) 
        {  
while (top != -1 && isOperator(peek()) && precedence(peek()) >= precedence(c)) 
{
postfix[j++] = pop();
            }
push(c);
        }
i++;
    }
while (top != -1) 
{
postfix[j++] = pop();
    }
postfix[j] = '\0';  
}
int evaluatePostfix(char postfix[]) 
{
int i = 0;
int operand1, operand2, result;
char c;
top = -1;  
while ((c = postfix[i]) != '\0') 
{
if (isdigit(c)) 
{  
push(c - '0'); 
        } else if (isOperator(c)) 
        {  
operand2 = pop();
operand1 = pop();
switch (c) 
{
case '+':
result = operand1 + operand2;
break;
case '-':
result = operand1 - operand2;
break;
case '*':
result = operand1 * operand2;
break;
case '/':
result = operand1 / operand2;
break;
case '^':
result = 1;
for (int j = 0; j < operand2; j++) 
{
result *= operand1;
                    }
break;
default:
printf("Invalid operator encountered.\n");
return -1;
            }
push(result);  
        }
i++;
    }
return pop();  
}
int main() 
{
char infix[MAX], postfix[MAX];
printf("Enter the infix expression: ");
fgets(infix, MAX, stdin);
infix[strcspn(infix, "\n")] = '\0';
infixtopostfix(infix, postfix);
printf("The postfix expression is: %s\n", postfix);
int result = evaluatePostfix(postfix);
printf("The result of the postfix evaluation is: %d\n", result);
return 0;
}