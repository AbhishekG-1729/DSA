#include <stdio.h>
#include <stdlib.h>
typedef struct Node 
{
    int coeff;
    int exp;
    struct Node* next;
} Node;
Node* createNode(int coeff, int exp) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}
void insertTerm(Node** poly, int coeff, int exp) 
{
    Node* newNode = createNode(coeff, exp);
    if (*poly == NULL || (*poly)->exp < exp) 
    {
        newNode->next = *poly;
        *poly = newNode;
        return;
    }
    Node* temp = *poly;
    Node* prev = NULL;
    while (temp != NULL && temp->exp > exp)
     {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL && temp->exp == exp) 
    {
        temp->coeff += coeff;
        free(newNode);
        if (temp->coeff == 0) 
        {
            if (prev == NULL) 
            {
                *poly = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
        }
    } else 
    {
        newNode->next = temp;
        if (prev != NULL)
            prev->next = newNode;
    }
}
void printPoly(Node* poly) 
{
    if (poly == NULL) 
    {
        printf("0");
        return;
    }
    while (poly != NULL) 
    {
        if (poly->coeff > 0 && poly != poly)
            printf("+");
        if (poly->exp == 0)
            printf("%d", poly->coeff);
        else if (poly->exp == 1)
            printf("%dx ", poly->coeff);
        else
            printf("%dx^%d ", poly->coeff, poly->exp);

        poly = poly->next;
    }
    printf("\n");
}
Node* addPoly(Node* poly1, Node* poly2) 
{
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) 
    {
        if (poly1->exp > poly2->exp) 
        {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) 
        {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else 
        {
            int sum = poly1->coeff + poly2->coeff;
            if (sum != 0)
                insertTerm(&result, sum, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) 
    {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) 
    {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}
Node* createPoly() 
{
    int n, coeff, exp;
    Node* poly = NULL;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
    {
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        scanf("%d%d", &coeff, &exp);
        insertTerm(&poly, coeff, exp);
    }
    return poly;
}
int main() 
{
    printf("Enter first polynomial:\n");
    Node* poly1 = createPoly();
    printf("Enter second polynomial:\n");
    Node* poly2 = createPoly();
    printf("First Polynomial: ");
    printPoly(poly1);
    printf("Second Polynomial: ");
    printPoly(poly2);
    Node* sum = addPoly(poly1, poly2);
    printf("Sum of polynomials: ");
    printPoly(sum);
    return 0;
}