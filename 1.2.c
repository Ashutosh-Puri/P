/*
Add the following functionalities in your program 
a) Accept Available
b) Display Allocation, Max 
c) Display the contents of need matrix 
d) Display Available
Process     Allocation   MAX
            A B C       A B C
P0          0 1 0       7 5 3
P1          2 0 0       3 2 2
P2          3 0 2       9 0 2
P3          2 1 1       2 2 2
P4          0 0 2       4 3 3
*/
#include<stdio.h>
void main()
{
    int avail[10],need[10][10];
    int i,j, n=5,m=3;
    int alloc[5][3]= {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[5][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int total[3]= {10,5,7};

    //Calculate Need Matrix
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    //Calculate Available
    for(j=0;j<m;j++)
    {
        int s=0;
        for(i=0;i<n;i++)
        {
            s+=alloc[i][j];
        }
    
        avail[j] = total[j] - s;
    }

    printf("\tAllocation\tMax\t\tNeed\n\t");

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
        printf("%3d",avail[j]);
    } 
    printf("\n");
}
