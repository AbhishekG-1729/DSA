#include <stdio.h>
#include <stdlib.h>
typedef struct Node 
{
    int coeff;
    int expo;
    struct Node* next;
} Node;
Node* createNode(int coeff, int expo) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;
    return newNode;
}
void insertTerm(Node** poly, int coeff, int expo) 
{
    Node* newNode = createNode(coeff, expo);
    if (*poly == NULL) 
    {
        *poly = newNode;
        return;
    }
    Node* temp = *poly;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}
void displayPoly(Node* poly) 
{
    if (poly == NULL) 
    {
        printf("0");
        return;
    }
    while (poly != NULL) 
    {
        printf("%dx^%d", poly->coeff, poly->expo);
        poly = poly->next;
        if (poly != NULL)
            printf(" + ");
    }
    printf("\n");
}
Node* addPolynomials(Node* poly1, Node* poly2) 
{
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) 
    {
        if (poly1->expo > poly2->expo) {
            insertTerm(&result, poly1->coeff, poly1->expo);
            poly1 = poly1->next;
        } else if (poly1->expo < poly2->expo) {
            insertTerm(&result, poly2->coeff, poly2->expo);
            poly2 = poly2->next;
        } else {
            int sumCoeff = poly1->coeff + poly2->coeff;
            if (sumCoeff != 0) {
                insertTerm(&result, sumCoeff, poly1->expo);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->expo);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->expo);
        poly2 = poly2->next;
    }

    return result;
}
int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    Node* sum = NULL;
    int n1,n2,n3,n4,i;
    printf("Enter the number of elements :");
    scanf("%d",&n1);
    for (i=0;i<n1;i++)
    {
        scanf("%d %d",&n2,&n3);
        insertTerm(&poly1, n2, n3);
    }
    printf("Enter the number of elements :");
    scanf("%d",&n4);
    for (i=0;i<n4;i++)
    {
        scanf("%d %d",&n2,&n3);
        insertTerm(&poly2, n2, n3);
    }
    displayPoly(poly1);
    displayPoly(poly2);

    sum = addPolynomials(poly1, poly2);

    printf("Sum: ");
    displayPoly(sum);

    return 0;
}