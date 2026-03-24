#include<stdio.h>
#include<stdlib.h>

int main()
{
    int RQ[100], i, n, TotalHeadMoment = 0, initial;

    printf("Enter the number of Requests: ");
    scanf("%d", &n);

    printf("Enter the Requests sequence:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &RQ[i]);

    printf("Enter initial head position: ");
    scanf("%d", &initial);

    printf("\nOrder of service:\n");

    // FCFS Logic
    for(i = 0; i < n; i++)
    {
        printf("%d -> ", RQ[i]);
        TotalHeadMoment += abs(RQ[i] - initial);
        initial = RQ[i];
    }

    printf("END\n");

    printf("Total head movement is %d\n", TotalHeadMoment);

    return 0;
}
