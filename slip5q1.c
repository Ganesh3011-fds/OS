#include <stdio.h>

#define MAX 10

int n, m;
int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
int avail[MAX], work[MAX], finish[MAX], seq[MAX];

void accept()
{
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d:\n", i);
        for (j = 0; j < m; j++)
        {
            printf("%c: ", 65 + j);
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d:\n", i);
        for (j = 0; j < m; j++)
        {
            printf("%c: ", 65 + j);
            scanf("%d", &max[i][j]);

            if (max[i][j] < alloc[i][j])
            {
                printf("Error: Max < Allocation!\n");
                return;
            }
        }
    }
}

void calc_need()
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

void display()
{
    int i, j;

    printf("\n\tAllocation\tMax\t\tNeed\n\t");

    for (j = 0; j < m; j++) printf("%3c", 65 + j);
    printf("\t");
    for (j = 0; j < m; j++) printf("%3c", 65 + j);
    printf("\t");
    for (j = 0; j < m; j++) printf("%3c", 65 + j);

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for (j = 0; j < m; j++) printf("%3d", alloc[i][j]);
        printf("\t");

        for (j = 0; j < m; j++) printf("%3d", max[i][j]);
        printf("\t");

        for (j = 0; j < m; j++) printf("%3d", need[i][j]);

        printf("\n");
    }

    printf("\nAvailable:\n");
    for (j = 0; j < m; j++)
        printf("%3d", avail[j]);
    printf("\n");
}

void banker()
{
    int i, j, count = 0;

    for (i = 0; i < n; i++)
        finish[i] = 0;

    for (j = 0; j < m; j++)
        work[j] = avail[j];

    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) 
                {
                    printf("P%d executed\n", i);

                    for (j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    finish[i] = 1;
                    seq[count++] = i;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            printf("\nSystem is NOT in safe state!\n");
            return;
        }
    }

    printf("\nSystem is in SAFE state\n");
    printf("Safe sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", seq[i]);
    printf("\n");
}

int main()
{
    accept();
    calc_need();
    display();
    banker();

    return 0;
}
