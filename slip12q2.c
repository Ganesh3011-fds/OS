#include<stdio.h>
#include<stdlib.h>

int main()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0;
    int initial, move, temp;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &move);

    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(RQ[i] > RQ[j])
            {
                temp = RQ[i];
                RQ[i] = RQ[j];
                RQ[j] = temp;
            }
        }
    }

    printf("\nOrder of service:\n");

    if(move == 1) 
    {
        for(i = 0; i < n; i++)
        {
            if(RQ[i] >= initial)
            {
                printf("%d -> ", RQ[i]);
                TotalHeadMoment += abs(RQ[i] - initial);
                initial = RQ[i];
            }
        }

        TotalHeadMoment += abs(initial - RQ[0]);
        initial = RQ[0];

        for(i = 0; i < n; i++)
        {
            if(RQ[i] < initial)
            {
                printf("%d -> ", RQ[i]);
                TotalHeadMoment += abs(RQ[i] - initial);
                initial = RQ[i];
            }
        }
    }
    else 
    {
        for(i = n - 1; i >= 0; i--)
        {
            if(RQ[i] <= initial)
            {
                printf("%d -> ", RQ[i]);
                TotalHeadMoment += abs(RQ[i] - initial);
                initial = RQ[i];
            }
        }

        TotalHeadMoment += abs(initial - RQ[n - 1]);
        initial = RQ[n - 1];

        for(i = n - 1; i >= 0; i--)
        {
            if(RQ[i] > initial)
            {
                printf("%d -> ", RQ[i]);
                TotalHeadMoment += abs(RQ[i] - initial);
                initial = RQ[i];
            }
        }
    }

    printf("END\n");
    printf("Total head movement = %d\n", TotalHeadMoment);

    return 0;
}
