#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int m, n;
int avail[MAX], alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];

void accept()
{
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

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
                printf("Error: Max cannot be less than Allocation!\n");
                exit(1);
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

    for (j = 0; j < m; j++)
        printf("%3c", 65 + j);
    printf("\t");

    for (j = 0; j < m; j++)
        printf("%3c", 65 + j);
    printf("\t");

    for (j = 0; j < m; j++)
        printf("%3c", 65 + j);
    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for (j = 0; j < m; j++)
            printf("%3d", alloc[i][j]);
        printf("\t");

        for (j = 0; j < m; j++)
            printf("%3d", max[i][j]);
        printf("\t");

        for (j = 0; j < m; j++)
            printf("%3d", need[i][j]);

        printf("\n");
    }
}

void display_available()
{
    int j;
    printf("\nAvailable Resources:\n");
    for (j = 0; j < m; j++)
        printf("%3d", avail[j]);
    printf("\n");
}

int main()
{
    int i, choice;

    accept();

    do
    {
        printf("\nMENU");
        printf("\n1. Enter Available Resources");
        printf("\n2. Display Allocation, Max and Need");
        printf("\n3. Display Available Resources");
        printf("\n4. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Available Resources:\n");
            for (i = 0; i < m; i++)
                scanf("%d", &avail[i]);
            break;

        case 2:
            calc_need();
            display();
            break;

        case 3:
            display_available();
            break;

        case 4:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
