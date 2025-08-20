#include<stdio.h>
int main()
{
    char a[20],b[20],c[20];
    int i,j=0,k=0,x,y,z;
    printf("Enter the infix =");
    scanf("%s",a);
    for(i=0;i!='\0';i++)
    {
        if((90>=a[i])||(65<=a[i]))
        {
            b[j]=a[i];
            j++;
        }
        else if((a[i]=="(")||(a[i]=="+")||(a[i]=="-")||(a[i]=="*")||(a[i]=="/")||(a[i]==")"))
        {
            c[k]=a[i];
            k++;
            if(c[k]==")")
            {
                x=k;
                while(x>=0)
                {
                    if (c[x]=="(")
                    {
                        break;
                    }
                    else
                    {
                        x--;
                    }
                }
            }
            for(y=x+1;y<i;y++)
            {
                b[j]=c[y];
                j++;
            }
        }
    }
    for (z=0;z!="\0";z++)
    {
        printf("%c",b[z]);
    }
    
}