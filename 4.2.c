/*
Consider a system with ânâ processes and âmâ resource types. Accept number of 
instances for every resource type. For each process accept the allocation and 
maximum requirement matrices. Write a program to display the contents of need 
matrix and to check if the given request of a process can be granted immediately 
or not.
*/
#include<stdio.h>
#define MAX 10

int i,j,m,n,total[MAX],avail[MAX],alloc[MAX][MAX],
max[MAX][MAX],need[MAX][MAX],work[MAX],finish[MAX],
seq[MAX],request[MAX];

    void accept()
    {
        
        printf("Enter no.of process:");
        scanf("%d",&n);

        printf("Enter no.of resource types:");
        scanf("%d",&m);

        printf("Enter total no.of resources of each resource type:\n");
        for(i=0;i<m;i++)
        {
            scanf("%d",&total[i]);
        }

        printf("Enter no.of allocated resources of each resource type by each process:\n");
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                scanf("%d",&alloc[i][j]);
            }
        }

        printf("Enter no.of maximum resources of each resource type by each process:\n"); 
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {          
                scanf("%d",&max[i][j]);
            }
        }
    }

    void calc_avail()
    {
        
        for(j=0;j<m;j++)
        {
           int s=0;
            for(i=0;i<n;i++)
            {
                s+=alloc[i][j];
            }
            avail[j] = total[j] - s;
        }
    }
    void calc_need()
    {
        
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                need[i][j]=max[i][j]-alloc[i][j];
            }
        }
    }
    void print()
    {
        printf("\tAllocation\tMax\tNeed\n\t");
        for(i=0;i<3;i++)
        {
            for(j=0;j<m;j++)
            {
                printf("%3c",65+j);
            }
            
            printf("\t");
        }
        printf("\n");

        for(i=0;i<n;i++)
        {
            printf("P%d\t",i);
            for(j=0;j<m;j++)
            {
                printf("%3d",alloc[i][j]);
            }
            printf("\t");

            for(j=0;j<m;j++)
            {
                printf("%3d",max[i][j]);
            }
            printf("\t");
            for(j=0;j<m;j++)
            {
                printf("%3d",need[i][j]);
            }
            printf("\n");
        }
        printf("Available\n");

        for(j=0;j<m;j++)
        {
            printf("%3c",65+j);
        }
        printf("\n");

        for(j=0;j<m;j++)
        {
            printf("%3d",avail[j]);
        }
       
        printf("\n");
    }

    int check(int s)
    {
    
        i = s;
        do
        {
            if(!finish[i])
            {
                for(j=0;j<m;j++)
                {
                    if(need[i][j]>work[j])
                    break;
                }
                if(j==m) return i;
            }
            i=(i+1)%n;

        }while(i!=s);
        return -1;
    }
    void banker()
    {
        int k=0;
        for(i=0;i<n;i++)
        {
            finish[i]=0;
        }    
        for(j=0;j<m;j++)
        {
            work[j] = avail[j];
        }
        i=0;

        while((i=check(i))!=-1)
        {
            printf("Process P%d resource granted.\n",i);
            finish[i] = 1;
            for(j=0;j<m;j++)
            {
                work[j] += alloc[i][j];
            }
    
            printf("finish(");
            for(j=0;j<n;j++)
            {
                printf("%d,",finish[j]);
            }
            printf("\b)\nwork(");
            for(j=0;j<m;j++)
            {
                printf("%d,",work[j]);
            }
            printf("\b)\n");
            seq[k++]=i;
            i=(i+1)%n;
        }
        if(k==n)
        {
            printf("System is in safe state.\n");
            printf("Safe sequence:");
            for(j=0;j<n;j++)
            {
                printf("P%d ",seq[j]);
            }
        }
        else
        {
            printf("System is not in safe state.");
        }
        printf("\n");
    }
    int main()
    {
        int pno;
        accept();
        calc_avail();
        calc_need();
        print();
        banker();
        printf("Enter process no:");
        scanf("%d",&pno);
        printf("Enter resource request of process P%d\n",pno);
        for(j=0;j<m;j++)
        {
            printf("%c:",65+j);
            scanf("%d",&request[j]);
        }
        for(j=0;j<m;j++)
        {
            if(request[j]>need[pno][j])
            break;
        }
        if(j==m)
        {
            for(j=0;j<m;j++)
            {
                if(request[j]>avail[j])
                break;
            }
            if(j==m)
            {
                for(j=0;j<m;j++)
                {
                    avail[j]-=request[j];
                    alloc[pno][j]+=request[j];
                    need[pno][j]-=request[j];
                    print();
                    banker();
                }
            }
            else
            {
                printf("Process P%d must wait.\n",pno);
            }

        }
        else
        {
            printf("Process P%d has exceeded its maximum claim\n",pno);
        }

        return 0;
    }
