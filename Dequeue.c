#include<stdio.h>
int front = -1;
int rear = -1;
int Q[10];
int isFull() 
{
    return (front == 0 && rear == 9) || (front == rear + 1);
}
int isEmpty() 
{
    return front == -1;
}
void enr() 
{
    if (isFull()) 
    {
        printf("Deque is full.\n");
        return;
    }
    int n;
    printf("Enter the element to insert at rear: ");
    scanf("%d", &n);
    if (isEmpty()) 
    {
        front = rear = 0;
    } else if (rear == 9) 
    {
        rear = 0;
    } else 
    {
        rear++;
    }
    Q[rear] = n;
}
void enf() 
{
    if (isFull()) 
    {
        printf("Deque is full.\n");
        return;
    }
    int n;
    printf("Enter the element to insert at front: ");
    scanf("%d", &n);
    if (isEmpty()) 
    {
        front = rear = 0;
    } else if (front == 0) 
    {
        front = 9;
    } else 
    {
        front--;
    }
    Q[front] = n;
}
void defr() {
    if (isEmpty()) 
    {
        printf("Deque is empty.\n");
        return;
    }
    int n = Q[front];
    printf("Deleted element from front: %d\n", n);

    if (front == rear) 
    {
        front = rear = -1;
    } else if (front == 9) 
    {
        front = 0;
    } else {
        front++;
    }
}
void derr() {
    if (isEmpty()) 
    {
        printf("Deque is empty.\n");
        return;
    }
    int n = Q[rear];
    printf("Deleted element from rear: %d\n", n);
    if (front == rear) 
    {
        front = rear = -1;
    } else if (rear == 0) 
    {
        rear = 9;
    } else 
    {
        rear--;
    }
}
void display() 
{
    if (isEmpty()) 
    {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque elements: ");
    int i = front;
    while (1) 
    {
        printf("%d ", Q[i]);
        if (i == rear)
            break;
        i = (i + 1) % 10;
    }
    printf("\n");
}
void peekFront() 
{
    if (isEmpty()) 
    {
        printf("Deque is empty.\n");
    } else 
    {
        printf("Front element: %d\n", Q[front]);
    }
}
void peekRear() 
{
    if (isEmpty()) 
    {
        printf("Deque is empty.\n");
    } else 
    {
        printf("Rear element: %d\n", Q[rear]);
    }
}
int main() 
{
    int choice;
    printf("\nMenu:\n");
    printf("Enqueue at rear =1\nEnqueue at front =2\nDequeue from front =3\nDequeue from rear =4\nDisplay deque =5\nPeek front =6\nPeek rear =7\nExit =8\n");
    printf("\nMenu:\n");
    printf("1. Enqueue at rear\n");
    printf("2. Enqueue at front\n");
    printf("3. Dequeue from front\n");
    printf("4. Dequeue from rear\n");
    printf("5. Display deque\n");
    printf("6. Peek front\n");
    printf("7. Peek rear\n");
    printf("8. Exit\n");
    while(1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
            enr(); 
            break;
            case 2: 
            enf(); 
            break;
            case 3: 
            defr(); 
            break;
            case 4: 
            derr(); 
            break;
            case 5: 
            display(); 
            break;
            case 6: 
            peekFront(); 
            break;
            case 7: 
            peekRear(); 
            break;
            case 8: 
            return 0;
            default: 
            printf("Invalid choice.\n"); 
            break;
        }
    }
    return 0;
}