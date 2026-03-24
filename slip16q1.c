#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200

typedef struct dir
{
    char fname[20];
    int start;
    int length;
    struct dir *next;
}NODE;

NODE *first = NULL, *last = NULL;
int n, fb, bit[MAX];

void init()
{
    int i;
    printf("Enter total no. of disk blocks: ");
    scanf("%d", &n);

    fb = n;

    for(i = 0; i < n; i++)
        bit[i] = 0;

    for(i = 0; i < 10; i++)
    {
        int k = rand() % n;
        if(bit[k] == 0)
        {
            bit[k] = 1;
            fb--;
        }
    }
}

void show_bitvector()
{
    int i;
    printf("Bit Vector:\n");
    for(i = 0; i < n; i++)
        printf("%d ", bit[i]);
    printf("\n");
}

void show_dir()
{
    NODE *p = first;

    printf("File\tStart\tLength\n");
    while(p != NULL)
    {
        printf("%s\t%d\t%d\n", p->fname, p->start, p->length);
        p = p->next;
    }
}

void create()
{
    NODE *p;
    char fname[20];
    int nob, i, j, count;

    printf("Enter file name: ");
    scanf("%s", fname);

    printf("Enter number of blocks: ");
    scanf("%d", &nob);

    if(nob > fb)
    {
        printf("Not enough space.\n");
        return;
    }

    for(i = 0; i <= n - nob; i++)
    {
        count = 0;
        for(j = 0; j < nob; j++)
        {
            if(bit[i + j] == 0)
                count++;
            else
                break;
        }

        if(count == nob)
            break;
    }

    if(count != nob)
    {
        printf("Contiguous blocks not available.\n");
        return;
    }

    for(j = 0; j < nob; j++)
        bit[i + j] = 1;

    fb -= nob;

    p = (NODE*)malloc(sizeof(NODE));
    strcpy(p->fname, fname);
    p->start = i;
    p->length = nob;
    p->next = NULL;

    if(first == NULL)
        first = p;
    else
        last->next = p;

    last = p;

    printf("File %s created successfully.\n", fname);
}

void delete_file()
{
    char fname[20];
    NODE *p, *q;
    int i;

    printf("Enter file name to delete: ");
    scanf("%s", fname);

    p = q = first;

    while(p != NULL)
    {
        if(strcmp(p->fname, fname) == 0)
            break;
        q = p;
        p = p->next;
    }

    if(p == NULL)
    {
        printf("File not found.\n");
        return;
    }

    for(i = 0; i < p->length; i++)
        bit[p->start + i] = 0;

    fb += p->length;

    if(p == first)
        first = first->next;
    else if(p == last)
    {
        last = q;
        last->next = NULL;
    }
    else
        q->next = p->next;

    free(p);

    printf("File %s deleted successfully.\n", fname);
}

int main()
{
    int ch;

    init();

    while(1)
    {
        printf("\n1. Show Bit Vector\n");
        printf("2. Create File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1: show_bitvector(); break;
            case 2: create(); break;
            case 3: show_dir(); break;
            case 4: delete_file(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}
