#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200

typedef struct file
{
    char fname[20];
    int start;
    struct file *next;
}NODE;

NODE *first=NULL,*last=NULL;

int n, bit[MAX], fb;

void init()
{
    int i;
    printf("Enter number of disk blocks: ");
    scanf("%d",&n);

    fb = n;

    for(i=0;i<n;i++)
        bit[i]=0;
}

void show_bitvector()
{
    int i;
    printf("Bit Vector:\n");
    for(i=0;i<n;i++)
        printf("%d ",bit[i]);
    printf("\n");
}

void create()
{
    char fname[20];
    int nob,i,j,k;

    printf("Enter file name: ");
    scanf("%s",fname);

    printf("Enter number of blocks: ");
    scanf("%d",&nob);

    if(nob > fb)
    {
        printf("Not enough space\n");
        return;
    }

    NODE *p = (NODE*)malloc(sizeof(NODE));
    strcpy(p->fname,fname);
    p->next=NULL;

    for(i=0;i<n;i++)
        if(bit[i]==0) break;

    p->start=i;
    bit[i]=-1;
    fb--;

    int prev = i;

    for(j=1;j<nob;j++)
    {
        for(k=0;k<n;k++)
            if(bit[k]==0) break;

        bit[prev]=k;
        prev = k;
        bit[k]=-1;
        fb--;
    }

    bit[prev] = -1;

    if(first==NULL)
        first=p;
    else
        last->next=p;

    last=p;

    printf("File created successfully\n");
}

void show_dir()
{
    NODE *p=first;
    int i;

    printf("File\tChain\n");

    while(p!=NULL)
    {
        printf("%s\t",p->fname);
        i = p->start;

        while(i!=-1)
        {
            printf("%d->",i);
            i = bit[i];
        }
        printf("NULL\n");

        p=p->next;
    }
}

void delete_file()
{
    char fname[20];
    NODE *p,*q;
    int i,j;

    printf("Enter file name: ");
    scanf("%s",fname);

    p=q=first;

    while(p!=NULL)
    {
        if(strcmp(p->fname,fname)==0)
            break;
        q=p;
        p=p->next;
    }

    if(p==NULL)
    {
        printf("File not found\n");
        return;
    }

    i = p->start;

    while(i!=-1)
    {
        j = i;
        i = bit[i];
        bit[j]=0;
        fb++;
    }

    if(p==first)
        first=first->next;
    else if(p==last)
    {
        last=q;
        last->next=NULL;
    }
    else
        q->next=p->next;

    free(p);

    printf("File deleted successfully\n");
}

int main()
{
    int ch;
    init();

    while(1)
    {
        printf("\n1.Bit Vector\n2.Create\n3.Directory\n4.Delete\n5.Exit\n");
        printf("Enter choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: show_bitvector(); break;
            case 2: create(); break;
            case 3: show_dir(); break;
            case 4: delete_file(); break;
            case 5: exit(0);
        }
    }
}
