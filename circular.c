#include <stdio.h>
int Q[10];
int front = -1;
int rear = -1;
void en() 
{
    int n;
    if ((rear + 1) % 10 == front) 
    {
        printf("The Queue is full.\n");
    } 
    else 
    {
        printf("Enter the element = ");
        scanf("%d", &n);
        if (front == -1 && rear == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % 10;
        }
        Q[rear] = n;
        printf("Enqueued: %d\n", n);
    }
    printf("\n");
}
void de() 
{
    if (front == -1) 
    {
        printf("The Queue is empty.\n");
    } 
    else 
    {
        int n = Q[front];
        printf("The deleted element is = %d\n", n);

        if (front == rear) 
        {
            front = rear = -1;
        } 
        else 
        {
            front = (front + 1) % 10;
        }
    }
    printf("\n");
}
void di() 
{
    if (front == -1) 
    {
        printf("The Queue is empty.\n");
        return;
    }
    printf("Elements = ");
    int i = front;
    while (1) 
    {
        printf("%d  ", Q[i]);
        if (i == rear)
            break;
        i = (i + 1) % 10;
    }
    printf("\n\n");
}
void pe() 
{
    if (front == -1) 
    {
        printf("The Queue is empty.\n");
    } else {
        printf("Element at the peek = %d\n", Q[front]);
    }
    printf("\n");
}

int main() 
{
    int w, n = 1;
    printf("Enqueue =1\nDequeue =2\nDisplay =3\nPeek =4\nExit =5\n");

    while (n) 
    {
        printf("Enter the process no = ");
        scanf("%d", &w);
        switch (w) 
        {
            case 1:
            en();
            break;
            case 2:
            de();
            break;
            case 3:
            di();
            break;
            case 4:
            pe();
            break;
            case 5:
            n = 0;
            break;
            default:
            printf("Invalid choice.\n\n");
            break;
        }
    }
    return 0;
}
