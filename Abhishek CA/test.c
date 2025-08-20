#include<stdio.h>
struct matri
{
    int n[10][10];    
    int s[100][3];    
    int c[100][3];    
};
int main()
{
    int r, c, i, j, k, l;
    struct matri m[2];
    for (i = 0; i < 2; i++)
    {
        printf("Enter the number of rows and columns of matrix %d: ", i + 1);
        scanf("%d %d", &r, &c);
        printf("Enter the elements:\n");
        for (k = 0; k < r; k++)
        {
            for (l = 0; l < c; l++)
            {
                scanf("%d", &m[i].n[k][l]);
            }
        }
        printf("Matrix %d:\n", i + 1);
        for (k = 0; k < r; k++)
        {
            for (l = 0; l < c; l++)
            {
                printf("%d  ", m[i].n[k][l]);
            }
            printf("\n");
        }
        m[i].s[0][0] = r;
        m[i].s[0][1] = c;
        int idx = 1;
        for (k = 0; k < r; k++)
        {
            for (l = 0; l < c; l++)
            {
                if (m[i].n[k][l] != 0)
                {
                    m[i].s[idx][0] = k;
                    m[i].s[idx][1] = l;
                    m[i].s[idx][2] = m[i].n[k][l];
                    idx++;
                }
            }
        }
        m[i].s[0][2] = idx - 1;
        printf("\nSparse Matrix %d:\n", i + 1);
        printf("Row\tColumn\tValue\n");
        for (k = 0; k < idx; k++)
        {
            printf("%d\t%d\t%d\n", m[i].s[k][0], m[i].s[k][1], m[i].s[k][2]);
        }
        printf("\n");
    }
    int r1 = m[0].s[0][0], c1 = m[0].s[0][1];
    int r2 = m[1].s[0][0], c2 = m[1].s[0][1];
    if (r1 != r2 || c1 != c2)
    {
        printf("Incompatible matrix sizes for addition.\n");
        return 1;
    }
    m[0].c[0][0] = r1;
    m[0].c[0][1] = c1;
    int x = 1, y = 1, z = 1;
    int total1 = m[0].s[0][2];
    int total2 = m[1].s[0][2];
    for (; x <= total1 && y <= total2; )
    {
        int r1 = m[0].s[x][0], c1 = m[0].s[x][1];
        int r2 = m[1].s[y][0], c2 = m[1].s[y][1];

        if (r1 == r2 && c1 == c2)
        {
            m[0].c[z][0] = r1;
            m[0].c[z][1] = c1;
            m[0].c[z][2] = m[0].s[x][2] + m[1].s[y][2];
            x++; y++; z++;
        }
        else if (r1 < r2 || (r1 == r2 && c1 < c2))
        {
            m[0].c[z][0] = r1;
            m[0].c[z][1] = c1;
            m[0].c[z][2] = m[0].s[x][2];
            x++; z++;
        }
        else
        {
            m[0].c[z][0] = r2;
            m[0].c[z][1] = c2;
            m[0].c[z][2] = m[1].s[y][2];
            y++; z++;
        }
    }
    for (; x <= total1; x++, z++)
    {
        m[0].c[z][0] = m[0].s[x][0];
        m[0].c[z][1] = m[0].s[x][1];
        m[0].c[z][2] = m[0].s[x][2];
    }
    for (; y <= total2; y++, z++)
    {
        m[0].c[z][0] = m[1].s[y][0];
        m[0].c[z][1] = m[1].s[y][1];
        m[0].c[z][2] = m[1].s[y][2];
    }
    m[0].c[0][2] = z - 1;
    printf("\nSparse Matrix After Addition:\n");
    printf("Row\tColumn\tValue\n");
    for (i = 0; i < z; i++)
    {
        printf("%d\t%d\t%d\n", m[0].c[i][0], m[0].c[i][1], m[0].c[i][2]);
    }
    m[1].c[0][0] = m[0].c[0][1];
    m[1].c[0][1] = m[0].c[0][0];
    m[1].c[0][2] = m[0].c[0][2];
    k = 1;
    int cols = m[0].c[0][1];
    int terms = m[0].c[0][2];
    for (i = 0; i < cols; i++)
    {
        for (j = 1; j <= terms; j++)
        {
            if (m[0].c[j][1] == i)
            {
                m[1].c[k][0] = m[0].c[j][1];
                m[1].c[k][1] = m[0].c[j][0];
                m[1].c[k][2] = m[0].c[j][2];
                k++;
            }
        }
    }
    printf("\nTranspose of Sparse Matrix:\n");
    printf("Row\tColumn\tValue\n");
    for (i = 0; i < k; i++)
    {
        printf("%d\t%d\t%d\n", m[1].c[i][0], m[1].c[i][1], m[1].c[i][2]);
    }
    return 0;
}