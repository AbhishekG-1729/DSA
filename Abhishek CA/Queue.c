#include<stdio.h>
int front=0;
int rear=-1;
int Q[10];
void de()
{
    if(rear==-1)
    {
        printf("The Queue is empty.");
    }
    else
    {
        int n=Q[front];
        printf("The deleted element is =%d",n);
        front++;
    }
    printf("\n");
}
void en()
{
    if(rear==9)
    {
        printf("The Queue is full.");
    }
    else
    {
        front=0;
        rear++;
        int n1;
        printf("Enter the element =");
        scanf("%d",&n1);
        Q[rear]=n1;
    }
    printf("\n");
}
void di()
{
    printf("Elements =");
    for(int i=front;i<=rear;i++)
    {
        printf("%d  ",Q[i]);
    }
    printf("\n");

}
void pe()
{
    printf("Element at the peek = %d",Q[front]);
    printf("\n");
}
int main()
{
    int w,n=1;
    printf("Enque =1\nDeque =2\nDisplay =3\nPeek =4\nExit =5\n");
    while(n)
    {
       printf("Enter the process no =");
       scanf("%d",&w);
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
           n=0;
           break;
           default:
           printf("Invalid");
           break;
       }
    }
return 0;
}