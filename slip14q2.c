#include<stdio.h>
#include<stdlib.h>

int main()
{
    int RQ[100], i, n, TotalHeadMoment = 0, initial;
    int count = 0;

    printf("Enter the number of Requests: ");
    scanf("%d", &n);

    printf("Enter the Requests sequence:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    printf("\nOrder of service:\n");

    // SSTF Logic
    while(count != n)
    {
        int min = 1000, d, index = -1;

        for(i = 0; i < n; i++)
        {
            if(RQ[i] != -1) // not yet served
            {
                d = abs(RQ[i] - initial);

                if(d < min)
                {
                    min = d;
                    index = i;
                }
            }
        }

        TotalHeadMoment += min;
        initial = RQ[index];

        printf("%d -> ", RQ[index]);

        RQ[index] = -1; // mark as served
        count++;
    }

    printf("END\n");
    printf("Total head movement is %d\n", TotalHeadMoment);

    return 0;
}
